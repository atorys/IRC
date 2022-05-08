//
// Created by Achiote Tory on 4/13/22.
//

#include "User.hpp"

User::User(int socket) :
			_socket(socket), _registred(false) {}

User::~User() {}


const std::string	&User::get_nickname() const { return this->_nickname; }
const std::string	&User::get_username() const { return this->_username; }
const std::string	&User::get_realname() const { return this->_realname; }
const int			&User::get_socket()	const	{ return this->_socket; }
const bool 			&User::get_registred() const {return this->_registred;}

void User::set_nickname(const std::string &nickname) { this->_nickname = nickname; }
void User::set_username(const std::string &username) { this->_username = username; }
void User::set_realname(const std::string &realname) { this->_realname = realname; }
void User::set_registred(bool value) {this->_registred = value;}