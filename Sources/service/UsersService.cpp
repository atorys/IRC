//
// Created by Achiote Tory on 5/2/22.
//

#include "UsersService.hpp"

UsersService::UsersService(const std::string& password, Postman* postman)
                        :
                        _password(password),
                        _postman(postman) {
    _commands["PASS"] = &UsersService::pass;
    _commands["USER"] = &UsersService::user;
    _commands["NICK"] = &UsersService::nick;
    _commands["JOIN"] = &UsersService::join;
    _commands["KICK"] = &UsersService::kick;
    _commands["PRIVMSG"] = &UsersService::privmsg;//kekis(не совершенная команда)
    _commands["NOTICE"] = &UsersService::notice;
    _commands["AWAY"] = &UsersService::away;
    _commands["PING"] = &UsersService::ping;
    _commands["QUIT"] = &UsersService::quit;
}

void UsersService::addUser(int client_socket) {
    _users[client_socket] = new User(client_socket);
    std::cout << "[CONNECTION #" << client_socket << "]\n";
}

// void UsersService::addChannelToList(Channel *newChannel){
//     for (std::vector<Channel> :: iterator start = _channels.begin(); start != _channels.end(); start++){
//         if (start->get_name() == args[1]){
//                 Postman::sendReply(client_socket, ERR_ALREADYREGISTRED);
//                 return;
//             }
//         }
    
//     _channels.push_back(newChannel);
// };

void UsersService::removeUser(int client_socket) {
    // delete from channels +
    if (_users[client_socket]->get_nickname().empty())
        std::cout << "user " << client_socket << " just left\n";
    else
        std::cout << _users[client_socket]->get_nickname() << " just left\n";
    _users.erase(client_socket);
    
}

User *UsersService::findUserByNickname(const std::string& nickname) {
    std::map<int, User*>::iterator start;
    for (start = _users.begin(); start != _users.end(); start++) {
        if (start->second->get_nickname() == nickname) {
            return start->second;
        }
    }
    return nullptr;
}

Channel *UsersService::findChannelByName(const std::string &name){
    std::vector<Channel *>::iterator start;
    for (start = _channels.begin(); start != _channels.end(); start++){
        if ((*start)->get_channelname() == name){
            return *start;
        }
    }
    return nullptr;
}

void UsersService::processRequest(std::string request, int client_socket) {
    if (_users[client_socket]->get_nickname().empty())
        std::cout << "user " << client_socket << ": " << request;
    else
        std::cout << _users[client_socket]->get_nickname() << ":" << request;
    std::vector<std::string> arguments = ut::splitForCmd(request);
    if (_commands.find(arguments[0]) != _commands.end()) {
        (this->*_commands[arguments[0]])(arguments, client_socket);
    } else {
        _postman->sendReply(client_socket, ERR_UNKNOWNCOMMAND(arguments[0]));
    }
}
