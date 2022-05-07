//
// Created by Achiote Tory on 5/2/22.
//

#pragma once

#include "Service.hpp"
#include "Postman.hpp"
#include "../models/User.hpp"
#include "../models/Channel.hpp"
#include <map>
#include <vector>

class User;
class Channel;

class UsersService : public Service {

    typedef	void (UsersService::*commandPtr)(std::vector<std::string>, int);

    const std::string&					_password;
    std::map<int, User*>				_users;
    std::map<std::string, commandPtr>   _commands;
    std::vector<Channel *>              _channels;
public:

    UsersService(const std::string&);
    virtual ~UsersService() {};

    void    addChannelToList(Channel *){};
    void    addUser(int);
    void    removeUser(int);
    User*   findUserByNickname(const std::string&);
    void    processRequest(std::string request, int client_socket);

    const std::map<int, User*>&   getUsers() const;

protected:

    void	pass(std::vector<std::string>, int);
    void	user(std::vector<std::string>, int);
    void	nick(std::vector<std::string>, int);
    void	join(std::vector<std::string>, int){};
    void	kick(std::vector<std::string>, int){};
    void	privmsg(std::vector<std::string>, int);
    void	notice(std::vector<std::string>, int){};
};
