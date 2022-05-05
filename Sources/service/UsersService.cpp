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
    if (_users[client_socket]->get_username() == "")
        std::cout << "user " << client_socket << " just left\n";
    else
        std::cout << _users[client_socket]->get_username() << " just left\n";
    _users.erase(client_socket);
    
}

void UsersService::processRequest(std::string request, int client_socket) {
    if (_users[client_socket]->get_username() == "")
        std::cout << "user " << client_socket << ": " << request;
    else
        std::cout << _users[client_socket]->get_username() << ": " << request;
    std::vector<std::string> arguments;
    if (request.find("\n") != std::string::npos) {
        request.erase(request.find("\n"));
    }
    if (request.find(" ") == std::string::npos){
        arguments.push_back(request);
        request.clear();
    } else {
        arguments.push_back(request.substr(0, request.find(" ")));
        request.erase(0, request.find(" ") + 1);
        if (request.find(" ") == std::string::npos)
            arguments.push_back(request);
        else {
            while (request.find(" ") != std::string::npos) {
                arguments.push_back(request.substr(0, request.find(" ")));
                request.erase(0, request.find(" ") + 1);
                if ((request.find(" ") == std::string::npos) || (request.find(":") < request.find(" "))) {
                    arguments.push_back(request);
                    break;
                }
            }
        }
    }
    if (_commands.find(arguments[0]) != _commands.end()) {
        (this->*_commands[arguments[0]])(arguments, client_socket);
    }
}

void UsersService::user(std::vector<std::string> args, int client_socket) {
    if (_users[client_socket]->get_registred() == false){
        _postman.sendReply(_users[client_socket], ERR_ALREADYREGISTRED);
        return;
    }
    if (args.size() == 5){
        args[4].erase(0, args[4].find(":") + 1);
        for (std::map<int, User*> :: iterator start = _users.begin(); start != _users.end(); start++){
            if (start->second->get_username() == args[1]){
                _postman.sendReply(_users[client_socket], ERR_ALREADYREGISTRED);
                return;
            }
        }
        _users[client_socket]->set_realname(args[4]);
        _users[client_socket]->set_username(args[1]);
    } else {
        _postman.sendReply(_users[client_socket], ERR_NEEDMOREPARAMS);
    }
}

void UsersService::pass(std::vector<std::string> args, int client_socket) {
    // removeUser(client_socket);
}

