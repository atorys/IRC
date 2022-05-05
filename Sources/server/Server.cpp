//
// Created by Achiote Tory on 4/12/22.
//

#include "Server.hpp"
#include "netinet/in.h"
#include "sys/socket.h"
#include "unistd.h"
#include "fcntl.h"
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

Server::~Server() { stop(); }

void Server::start() {

	Init();

	_polls.push_back((pollfd){_socket, POLLIN, 0});
	std::vector<pollfd>::iterator iter;
	for (;;)
	{
		if (poll(_polls.data(), _polls.size(), -1) == -1) {
			std::cerr << "poll failure" << std::endl;
			exit(EXIT_FAILURE);
		}

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

void Server::stop() {
	std::vector<pollfd>::iterator iter;
	for (iter = _polls.begin(); iter != _polls.end(); ++iter) {
		Remove(iter);
	}
	delete _service;
}

void Server::Init() {
	char buff[50];

	CreateSocket();
	gethostname(&buff[0], 50);
	printf("server started as:\033[32m%s\033[0m:\033[32m%s\033[0m\n\n", buff, _port.c_str());

	// marks socket as PASSIVE to accept the connections
	if (listen(_socket, 10) < 0) {
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
void Server::CreateSocket() {
	struct addrinfo		base{}, *addressesList, *address;
	char				buf[INET6_ADDRSTRLEN];
	int 				restrict = 1, status;

	memset(&base, 0, sizeof base);
	base.ai_flags = AI_PASSIVE; // собственный ip заполнит сама функция getaddrinfo()
	base.ai_family = AF_UNSPEC; // рассматриваем ipv4 и ipv6
	base.ai_socktype = SOCK_STREAM; // протокол tcp

	if ((status = getaddrinfo(nullptr, _port.c_str(), &base, &addressesList)) != 0) {
		std::cerr << "getaddrinfo:" << gai_strerror(status) << std::endl;
		exit(EXIT_FAILURE);
	}

	// пытаемся получить сокет с параметрами из данных листа, потом ассоциировать его с портом на нашей машине
	// если данные не валидны, переходим к следующей структуре листа
	for (address = addressesList; address != nullptr; address = address->ai_next) {

		// чуть больше информации о доступном адресе для визуализации
		getnameinfo(address->ai_addr, address->ai_addrlen, buf, sizeof(buf), NULL, 0, NI_NUMERICHOST);

		// создаем сокет с параметрами текущего адреса
		// setsockopt позволяет после отключения сервера сразу же переиспользовать порт
		if ((_socket = socket(address->ai_family, address->ai_socktype, 0)) != -1 &&
		setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof(int)) != -1 &&
		bind(_socket, address->ai_addr, address->ai_addrlen) != -1)
		{
			std::cout << "server init " << (address->ai_family == AF_INET ? "IPv4 " : "IPv6 ");
			std::cout << buf << " \033[32m[SUCCESS]\033[0m\n";
			break ;
		}
		std::cerr << "socket creation failed IP: " << buf << std::endl;
	}

	freeaddrinfo(addressesList);
	if (address == nullptr)
		exit(EXIT_FAILURE);
}

void Server::Add() {
    struct sockaddr_in	clientaddr{};
    socklen_t			len = sizeof(clientaddr);
    int					client_socket = accept(_socket, (struct sockaddr *) &clientaddr, &len);

    if (fcntl(client_socket, F_SETFL, O_NONBLOCK) < 0) {
		std::cerr << "fcntl nonblock failure" << std::endl;
		exit(EXIT_FAILURE);
	}

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
	size_t return_recv = 10;
	while (return_recv == 10 || request.find('\n') != std::string::npos) {
		bzero(&msg, sizeof(msg));
		return_recv = recv(client_socket, &msg, 10, 0);
		if (return_recv <= 0)
			break;
		request += msg;
	}
	_service->processRequest(request, client_socket);
}
