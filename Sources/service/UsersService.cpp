//
// Created by Achiote Tory on 5/2/22.
//

#include "UsersService.hpp"

UsersService::UsersService(const std::string& password)
                        :
                        _password(password) {
    _commands["PASS"] = &UsersService::pass;
    _commands["USER"] = &UsersService::user;
    _commands["NICK"] = &UsersService::nick;
    _commands["JOIN"] = &UsersService::join;
    _commands["KICK"] = &UsersService::kick;
}

void UsersService::addUser(int client_socket) {
    _users[client_socket] = new User(client_socket);
    _postman.sendReply(_users[client_socket], RPL_MOTDSTART);
    _postman.sendReply(_users[client_socket], RPL_MOTD);
    _postman.sendReply(_users[client_socket], RPL_ENDOFMOTD);
    std::cout << "[CONNECTION #" << client_socket << "]\n";
}

void UsersService::removeUser(int client_socket) {
    // delete from channels +
    _users.erase(client_socket);
    std::cout << "client " << client_socket << " just left\n";
}

void UsersService::processRequest(std::string request) {
    std::vector<std::string> arguments;

    if (request.find("\n") != std::string::npos) {
        request.erase(request.find("\n"));
    }
    while (request.find(" ") != std::string::npos) {
//        arguments.push_back(request.copy(request.begin(), request.find(" ")));
//        request.erase(request.begin(), request.find(" "));
    }
    arguments.push_back(request);
    if (_commands.find(arguments[0]) != _commands.end()) {
        (this->*_commands[arguments[0]])(arguments);
    }
}

void UsersService::user(std::vector<std::string> args) {
    std::cout << "user called\n";
}

void UsersService::pass(std::vector<std::string> args) {
    std::cout << "pass called\n";
}