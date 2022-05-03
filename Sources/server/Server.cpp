//
// Created by Achiote Tory on 4/12/22.
//

#include "Server.hpp"
#include "netinet/in.h"
#include <arpa/inet.h>
#include "sys/socket.h"
#include "sys/types.h"
#include "unistd.h"
#include "fcntl.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <cstring>
#include <cstdio>
#include "../service/UsersService.hpp"

Server::Server(const std::string &port, const std::string &password)
				:
				_port(port),
				_socket(-1),
				_service(new UsersService(password)) {}

Server::~Server() {}

void Server::Init() {

	struct addrinfo		base, *addr_info, *ptr;
	int 				restrict = 1;

	memset((char *)&base, 0, sizeof(base));
	base.ai_family = AF_UNSPEC;			// IPv4 or IPv6
	base.ai_socktype = SOCK_STREAM;		// TCP
	base.ai_flags = AI_PASSIVE;			// For wildcard IP address

	// getter returns a list of address structures
	// we might try each address until successful bind()
	if (getaddrinfo(nullptr, _port.c_str(), &base, &addr_info))
		throw std::runtime_error("get addrinfo failure\n");

	for (ptr = addr_info; ptr != nullptr; ptr = ptr->ai_next) {

		// try to create file descriptor for communication
		if ((_socket = socket(ptr->ai_family, ptr->ai_socktype, 0)) == -1)
			continue ;

		// deactivation of "address already in use"
		setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof(int));

		// assign IP address and port to the socket
		if (bind(_socket, ptr->ai_addr, ptr->ai_addrlen) < 0) {
			close(_socket);
			continue ;
		}
		break ;
	}

	(ptr == nullptr) ? throw std::runtime_error("socket bind failure\n") : freeaddrinfo(addr_info);

	std::cout << "server init \033[32m[SUCCESS]\033[0m\n";
	char buff[50];
	gethostname(&buff[0], 50);
	printf("server started as:\033[32m%s\033[0m:\033[32m%s\033[0m\n\n", buff, _port.c_str());

}

void Server::start() {

	Init();

	if (listen(_socket, 10) < 0) // marks socket as PASSIVE to accept the connections
		throw std::runtime_error("listen socket failure\n");

	if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("fcntl nonblock failure\n");

	std::vector<pollfd>::iterator		iter;

	_polls.push_back((pollfd){_socket, POLLIN, 0});
	for (;;)
	{
		if (poll(&(*(_polls.begin())), _polls.size(), -1) == -1)
            throw std::runtime_error("poll failure\n");

		if (_polls[0].revents & POLLIN)
		    Add();

        for (iter = _polls.begin() + 1; iter != _polls.end(); ++iter) {
            if (iter->revents & POLLHUP) {
                Remove(iter);
                break;
            } else if (iter->revents & POLLIN) {
                Receive(iter->fd);
            }
        }
	}
}

void Server::Add() {
    struct sockaddr_in	clientaddr;
    socklen_t			len = sizeof(clientaddr);
    int					client_socket = accept(_socket, (struct sockaddr *) &clientaddr, &len);

    if (fcntl(client_socket, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("fcntl nonblock failure\n");

    _polls.push_back((pollfd){client_socket, POLLIN, 0});
    _service->addUser(client_socket);
}

void Server::Remove(std::vector<pollfd>::iterator pollsIter) {
    _polls.erase(pollsIter);
    _service->removeUser(pollsIter->fd);
    close(pollsIter->fd);
}

void Server::Receive(int client_socket) {
    std::string             request;

	char msg[11];
	int return_recv = 10;
	while (return_recv == 10 || request.find("\n") != std::string::npos) {
		bzero(&msg, sizeof(msg));
		return_recv = recv(client_socket, &msg, 10, 0);
		if (return_recv <= 0)
			break;
		request += msg;
	}
	_service->processRequest(request, client_socket);
}

void Server::stop() {
    for (std::vector<pollfd>::iterator iter = _polls.begin(); iter != _polls.end(); ++iter) {
        Remove(iter);
    }
    delete _service;
}
