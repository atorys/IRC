//
// Created by Achiote Tory on 4/13/22.
//

#include "User.hpp"

User::User(int socket) :
			_socket(socket) {}

User::~User() {}


const std::string &User::get_nickname() const {	return this->_nickname; }
const std::string &User::get_username() const { return this->_username; }

void User::set_nickname(const std::string &nickname) { this->_nickname = nickname; }
void User::set_username(const std::string &username) { this->_username = username; }