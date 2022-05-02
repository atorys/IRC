//
// Created by Achiote Tory on 4/13/22.
//

#include "User.hpp"
#include "sys/socket.h"

User::User(int socket) :
			_socket(socket) {}

User::~User() {}


const std::string	&User::get_nickname() const { return this->_nickname; }
const std::string	&User::get_username() const { return this->_username; }
const int			&User::get_socket()	const	{ return this->_socket; }

void User::set_nickname(const std::string &nickname) { this->_nickname = nickname; }
void User::set_username(const std::string &username) { this->_username = username; }

void User::send_massage_to(const std::string &message) const {
	if (send(_socket, message.c_str(), message.size(), 0) == -1)
		throw std::runtime_error("send message to client failure\n");
}