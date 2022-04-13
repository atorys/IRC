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

Server::Server(const std::string &port, const std::string &password)
				:
				_port(port),
				_password(password),
				_socket(-1) {
	_commands["PASS"] = &Server::pass;
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
	printf("server started as:\033[32m%s\033[0m:\033[32m%s\033[0m\n", buff, _port.c_str());

}

int Server::max_socket() const {
	int tmp = std::max_element(_users.begin(), _users.end())->first;
	return (_socket < tmp ? tmp : _socket);
}

void Server::start() {
	Init();
	if (listen(_socket, 10) < 0) // marks socket as PASSIVE to accept the connections
		throw std::runtime_error("listen socket failure\n");

	fd_set	master, readers, writers;
	FD_ZERO(&master);
	FD_ZERO(&readers);
	FD_ZERO(&writers);
	FD_SET(_socket, &master);

	char msg[42];

	for (;;) {
		readers = writers = master;
		if (select(max_socket() + 1, &readers, &writers, nullptr, nullptr) < 0)
			continue ;

		for (int i = 0; i <= max_socket(); i++) {
			if (FD_ISSET(i, &readers)) {
				if (i == _socket)
				{
					struct sockaddr_in clientaddr;
					socklen_t len = sizeof(clientaddr);
					bzero(&msg, sizeof(msg));
					int fd = accept(_socket, (struct sockaddr *)&clientaddr, &len);
					_users[fd] = new User(fd);
					FD_SET(fd, &master);
					std::cout << "new client : " << fd << "\n";
					break;
				}
				else
				{
					int return_recv = 10;
					while (return_recv == 10 || msg[strlen(msg) - 1] != '\n')
					{
						return_recv = recv(i, msg+ strlen(msg), 10, 0);
						if (return_recv <= 0)
							break;
					}
					if (return_recv <= 0)
					{
						bzero(&msg, sizeof(msg));
						std::cout << "client " << i << "just left\n";
						_users.erase(i);
						FD_CLR(i, &master);
						close(i);
						break ;
					}
					else {
						std::cout << "user " << i << ": " << msg;
						bzero(&msg, sizeof(msg));
					}
				}
			}
		}
	}
}


void Server::pass() {
 
}