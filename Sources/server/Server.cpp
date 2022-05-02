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

Server::Server(const std::string &port, const std::string &password)
				:
				_port(port),
				_password(password),
				_socket(-1) {
	_commands["PASS"] = &Server::pass;
//	_commands["USER"] = &Server::user;
//	_commands["NICK"] = &Server::nick;
}

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

	std::vector<pollfd>					polls;
	std::vector<pollfd>::iterator		iter;

	polls.push_back((pollfd){_socket, POLLIN, 0});
	for (;;)
	{
		if (poll(&(*(polls.begin())), polls.size(), -1) == -1)
			throw std::runtime_error("poll failure\n");

		if (polls[0].revents & POLLIN)
		{
			struct sockaddr_in	clientaddr;
			socklen_t			len = sizeof(clientaddr);
			int					client_socket = accept(_socket, (struct sockaddr *) &clientaddr, &len);

			if (fcntl(client_socket, F_SETFL, O_NONBLOCK) < 0)
				throw std::runtime_error("fcntl nonblock failure\n");

			polls.push_back((pollfd){client_socket, POLLIN, 0});
			Add(client_socket);
		}

		for (iter = polls.begin() + 1; iter != polls.end(); ++iter)
		{
			if (iter->revents & POLLHUP) {
				polls.erase(iter);
				Remove(iter->fd);
				break ;
			}
			if (iter->revents & POLLIN)
				Receive(iter->fd);
		}
	}
}



void Server::pass() {

}

void Server::Add(int client_socket) {
	_users[client_socket] = new User(client_socket);
	_users[client_socket]->send_massage_to( "NICK: ");
	std::cout << "new client : " << client_socket << "\n";
}

void Server::Remove(int client_socket) {
	// delete from channels +
	_users.erase(client_socket);
	std::cout << "client " << client_socket << " just left\n";
	close(client_socket);
}

void Server::Receive(int client_socket) {
	std::pair<std::string, std::string>		request;
	std::string::iterator 					iter;

	char msg[42];
	int return_recv = 10;
	while (return_recv == 10 || request.second.find("\n") != std::string::npos) {
		bzero(&msg, sizeof(msg));
		return_recv = recv(client_socket, &msg, 10, 0);
		if (return_recv <= 0)
			break;
		request.second += msg;
	}
	iter = request.second.begin();
	if (request.second.find(" ") != std::string::npos)
		request.first.insert(request.first.begin(), iter, iter + request.second.find(" "));
	request.second.erase(iter, iter + request.first.size());

	std::cout << "user " << client_socket << ": " << request.first << " : " << request.second;

//	(this->*commandPtr))();
}