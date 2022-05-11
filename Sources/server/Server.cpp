//
// Created by Achiote Tory on 4/12/22.
//

#include "Server.hpp"
#include "netinet/in.h"
#include "sys/socket.h"
#include "unistd.h"
#include "fcntl.h"
#include <cstring>
#include <cstdio>
#include <arpa/inet.h>
#include "../service/UsersService.hpp"

const int buffSize = 128;
const int maxConnections = 128;

Server::Server(const std::string &port, const std::string &password)
				:
				_port(port),
				_socket(-1),
                _postman(Postman()),
				_service(new UsersService(password, &_postman)) {}

Server::~Server() { stop(); }

void Server::start() {

	init();

	_polls.push_back((pollfd){_socket, POLLIN, 0});
	std::vector<pollfd>::iterator iter;
	for (;;)
	{
		if (poll(_polls.data(), _polls.size(), -1) == -1) {
			std::cerr << "poll failure" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (_polls[0].revents & POLLIN)
		    add();

        for (iter = _polls.begin() + 1; iter != _polls.end(); ++iter) {
            if (iter->revents & POLLHUP) {
                remove(iter);
                break;
            }
            if (iter->revents & POLLOUT) {
                sendback(iter->fd);
            }
            if (iter->revents & POLLIN) {
                receive(iter->fd);
            }
        }
	}
}

void Server::stop() {
	std::vector<pollfd>::iterator iter;
	for (iter = _polls.begin(); iter != _polls.end(); ++iter) {
		remove(iter);
	}
	delete _service;
}

void Server::init() {
	char buff[buffSize];

	createSocket();
	gethostname(&buff[0], buffSize);
	printf("server started as:\033[32m%s\033[0m:\033[32m%s\033[0m\n\n", buff, _port.c_str());

	// marks socket as PASSIVE to accept the connections
	if (listen(_socket, maxConnections) < 0) {
		std::cerr << "listen socket failure" << std::endl;
		exit(EXIT_FAILURE);
	}
    if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0) {
        std::cerr << "fcntl nonblock failure" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*
 * Создаем потоковый сокет - дескриптор файла для системных вызовов
 * и общения через него с помощью send() и recv()
 */
void Server::createSocket() {
    struct sockaddr_in  address = {};
    int 				restrict = 1;

    bzero(&address, sizeof address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(strtol(_port.c_str(), nullptr, 10));

    if ((_socket = socket(address.sin_family, SOCK_STREAM, 0)) == -1 ||
    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof(int)) == -1 ||
    bind(_socket, (struct sockaddr*)&address, sizeof(address)) == -1) {
        std::cerr << "socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "server init IPv4 ";
    std::cout << inet_ntoa(address.sin_addr) << " \033[32m[SUCCESS]\033[0m\n";
}

void Server::add() {
    struct sockaddr_in	clientaddr = {};
    socklen_t			len = sizeof(clientaddr);
    int					client_socket = accept(_socket, (struct sockaddr *) &clientaddr, &len);

    if (fcntl(client_socket, F_SETFL, O_NONBLOCK) < 0) {
		std::cerr << "fcntl nonblock failure" << std::endl;
		exit(EXIT_FAILURE);
	}

    _polls.push_back((pollfd){client_socket, POLLIN | POLLOUT | POLLHUP, 0});
    _service->addUser(client_socket);
}

void Server::remove(std::vector<pollfd>::iterator pollsIter) {
    close(pollsIter->fd);
    _service->removeUser(pollsIter->fd);
    _postman.clearReplies(pollsIter->fd);
    _postman.clearRequests(pollsIter->fd);
    _polls.erase(pollsIter);
}

void Server::receive(int client_socket) {
    char msg[buffSize];

    bzero(&msg, sizeof(msg));
    if (recv(client_socket, &msg, buffSize, 0) < 0) {
        std::cerr << "recv() failure" << std::endl;
        exit(EXIT_FAILURE);
    }

    _postman.sendRequest(client_socket, msg);
    while (_postman.hasRequest(client_socket)) {
	    _service->processRequest(_postman.getRequest(client_socket), client_socket);
	}
}

void Server::sendback(int client_socket) {
    if (_postman.hasReply(client_socket)) {
        std::string reply = _postman.getReply(client_socket);
        if (send(client_socket, reply.c_str(), reply.size(), 0) == -1) {
            std::cerr << "send message to client failure\n";
            exit(EXIT_FAILURE);
        }
        std::cout << "server: " << reply;
    }
}
