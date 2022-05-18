//
// Created by Achiote Tory on 4/13/22.
//

#include "User.hpp"

User::User(int socket, const std::string& host) :
			_socket(socket), _registred(false), _connected(true), _host(host) {}

User::~User() {}


const std::string	&User::get_nickname() const { return this->_nickname; }
const std::string	&User::get_username() const { return this->_username; }
const std::string	&User::get_realname() const { return this->_realname; }
const int			&User::get_socket()	const	{ return this->_socket; }
const bool 			&User::get_registred() const {return this->_registred;}
const std::string	&User::get_awayMessage() const { return this->_awayMessage; }

bool                User::is_away() const { return (!this->_awayMessage.empty()); }
bool                User::is_connected() const { return this->_connected; }
bool                User::is_authenticated() const { return this->_registred && !this->_nickname.empty() && !this->_username.empty(); }

void User::set_nickname(const std::string &nickname) { this->_nickname = nickname; }
void User::set_username(const std::string &username) { this->_username = username; }
void User::set_realname(const std::string &realname) { this->_realname = realname; }
void User::set_registred(bool value) {this->_registred = value;}
void User::set_connected(bool connected) { this->_connected = connected; }
void User::set_awayMessage(const std::string &awayMsg) { this->_awayMessage = awayMsg; }

std::string User::get_fullname() const {
    return (_nickname + '!' + _username + '@' + _host);
}

void User::set_mode(UserMode flag) {
    _modes |= flag;
}

void User::unset_mode(UserMode flag) {
    _modes &= (~flag);
}

bool User::has_mode(UserMode flag) const {
    return ((_modes & flag) == flag);
}

// {[+|-]i|s|o|w}
std::string User::show_mode() const {
    std::string show;
    if (has_mode(UserOper))
        show += 'o';
    if (has_mode(wallopsOff))
        show += 'w';
    if (has_mode(silence))
        show += 's';
    if (has_mode(invisibility))
        show += 'i';
    return show.empty() ? "" : '+' + show;
}