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
    _commands["PRIVMSG"] = &UsersService::privmsg;//kekis(не совершенная команда)
    _commands["NOTICE"] = &UsersService::notice;
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
    if (_users[client_socket]->get_username().empty())
        std::cout << "user " << client_socket << " just left\n";
    else
        std::cout << _users[client_socket]->get_username() << " just left\n";
    _users.erase(client_socket);
    
}

const std::map<int, User *> &UsersService::getUsers() const {
    return _users;
}

User *UsersService::findUserByNickname(const std::string& nickname) {
    std::map<int, User*>::iterator start;
    for (start = _users.begin(); start != _users.end(); start++) {
        if (start->second->get_username() == nickname) {
            return start->second;
        }
    }
    return nullptr;
}

void UsersService::processRequest(std::string request, int client_socket) {
    if (_users[client_socket]->get_username().empty())
        std::cout << "user " << client_socket << ": " << request;
    else
        std::cout << _users[client_socket]->get_username() << ":" << request;
    std::vector<std::string> arguments;
    if (request.find('\n') != std::string::npos) {
        request.erase(request.find('\n'));
    }
    if (request.find(' ') == std::string::npos){
        arguments.push_back(request);
    } else {
        arguments.push_back(request.substr(0, request.find(' ')));
        request.erase(0, request.find(' ') + 1);
        if (request.find(' ') == std::string::npos)
            arguments.push_back(request);
        else {
            while (request.find(' ') != std::string::npos) {
                arguments.push_back(request.substr(0, request.find(' ')));
                request.erase(0, request.find(' ') + 1);
                if ((request.find(' ') == std::string::npos) || (request.find(':') < request.find(' '))) {
                    arguments.push_back(request);
                    break;
                }
            }
        }
    }
    if (_commands.find(arguments[0]) != _commands.end()) {
        (this->*_commands[arguments[0]])(arguments, client_socket);
    } else {
        Postman::sendReply(client_socket, ERR_UNKNOWNCOMMAND(arguments[0]));
    }
}

void UsersService::user(std::vector<std::string> args, int client_socket) {
    if (_users[client_socket]->get_registred() == false) {
        Postman::sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));
        return;
    }
    if (args.size() == 5){
        args[4].erase(0, args[4].find(':') + 1);
        for (std::map<int, User*> :: iterator start = _users.begin(); start != _users.end(); start++){
            if (start->second->get_username() == args[1]){
                Postman::sendReply(client_socket, ERR_ALREADYREGISTRED);
                return;
            }
        }
        _users[client_socket]->set_realname(args[4]);
        _users[client_socket]->set_username(args[1]);
    } else {
        Postman::sendReply(client_socket, ERR_NEEDMOREPARAMS("USER"));
    }
}

void UsersService::pass(std::vector<std::string> args, int client_socket) {
    if (_users[client_socket]->get_registred()) {
        Postman::sendReply(client_socket, ERR_ALREADYREGISTRED);
    } else if (args.size() < 2) {
        Postman::sendReply(client_socket, ERR_NEEDMOREPARAMS("PASS"));
    } else if (std::equal(_password.begin(), _password.end(), args[1].begin())) {
        _users[client_socket]->set_registred(true);
    } else {
        Postman::sendReply(client_socket, ERR_PASSWDMISMATCH);
    }
}

void UsersService::nick(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->get_registred()) {
        Postman::sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));
    } else if (args.size() < 2) {
        Postman::sendReply(client_socket, ERR_NONICKNAMEGIVEN);
    } else if (findUserByNickname(args[1]) != nullptr) {
        Postman::sendReply(client_socket, ERR_NICKNAMEINUSE(args[1]));
    } else if (args[1].at(0) < 'a' || args[1].at(0) > 'z') {
        Postman::sendReply(client_socket, ERR_ERRONEUSNICKNAME(args[1]));
    } else {
        if (_users[client_socket]->get_nickname().empty()) {
            Postman::sendReply(client_socket, RPL_MOTDSTART);
            Postman::sendReply(client_socket, RPL_MOTD("MESSAGE OF THE DAY HERE"));
            Postman::sendReply(client_socket, RPL_ENDOFMOTD);
        }
        _users[client_socket]->set_nickname(args[1]);
    }
}

// void UsersService::join(std::vector<std::string> args, int client_socket){

// }

void UsersService::privmsg(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->get_registred()){
        Postman::sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));
    } else if (args.size() != 3){
        if (args.size() == 2){
            if (args[1].find(":") != std::string::npos){
                Postman::sendReply(client_socket, ERR_NORECIPIENT(args[0]));
            } else {
                Postman::sendReply(client_socket, ERR_NOTEXTTOSEND);
            }
        } else {
            Postman::sendReply(client_socket, ERR_TOOMANYTARGETS(args[1])));
        }
    } else if (findUserByNickname(args[1]) == nullptr){
        Postman::sendReply(client_socket, ERR_WASNOSUCHNICK(args[1]));
    } else {
        int replySocket = findUserByNickname(args[1])->get_socket();
        Postman::sendReply(replySocket, _users[client_socket]->get_username() + args[2]);
    }
}