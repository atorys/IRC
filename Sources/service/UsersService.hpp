//
// Created by Achiote Tory on 5/2/22.
//

#pragma once

#include "Service.hpp"
#include "Postman.hpp"
#include "../models/User.hpp"
#include <map>
#include <vector>

#define RPL_MOTDSTART   375
#define RPL_MOTD        372
#define RPL_ENDOFMOTD   376
#define MISSING_CHARACTER_IN_STRING 18446744073709551615
#define ERR_NEEDMOREPARAMS 461

class User;

class UsersService : public Service {

    typedef	void (UsersService::*commandPtr)(std::vector<std::string>, int);

    const std::string&					_password;
    std::map<int, User*>				_users;
    std::map<std::string, commandPtr>   _commands;
    Postman                             _postman;

public:

    UsersService(const std::string&);
    virtual ~UsersService() {};

    void    addUser(int);
    void    removeUser(int);
    void    processRequest(std::string request, int client_socket);


protected:

    void	pass(std::vector<std::string>, int);
    void	user(std::vector<std::string>, int);
    void	nick(std::vector<std::string>, int){};
    void	join(std::vector<std::string>, int){};
    void	kick(std::vector<std::string>, int){};
};
