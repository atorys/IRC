//
// Created by Achiote Tory on 5/2/22.
//

#pragma once

#include "Service.hpp"
#include "Postman.hpp"
#include "../models/User.hpp"
#include "../models/Channel.hpp"
#include "../utility/utility.hpp"
#include <map>
#include <set>
#include <vector>

class UsersService : public Service {

    typedef	void (UsersService::*commandPtr)(std::vector<std::string>, int);

    const std::string&					_password;
    Postman*                            _postman;

    std::map<int, User*>				_users;
    std::map<std::string, commandPtr>   _commands;
    std::vector<Channel *>              _channels;

public:

    UsersService(const std::string&, Postman*);
    virtual ~UsersService() {};

    void        addUser(int);
    void        removeUser(int);
    bool        isConnected(int);
    void        welcomeUser(int);
    User*       findUserByNickname(const std::string&);

    void        addChannel(Channel *);
    void        removeEmptyChannels();
    Channel*    findChannelByName(const std::string&);

    void        processRequest(std::string request, int client_socket);

protected:

    void	pass(std::vector<std::string>, int);
    void	user(std::vector<std::string>, int);
    void	nick(std::vector<std::string>, int);
    void	join(std::vector<std::string>, int);
    void	kick(std::vector<std::string>, int);
    void	privmsg(std::vector<std::string>, int);
    void	notice(std::vector<std::string>, int);
    void	away(std::vector<std::string>, int);
    void	ping(std::vector<std::string>, int);
    void	pong(std::vector<std::string>, int){};
    void	quit(std::vector<std::string>, int);
    void	ison(std::vector<std::string>, int);
    void	list(std::vector<std::string>, int);
    void	names(std::vector<std::string>, int);
    void	topic(std::vector<std::string>, int);
    void    part(std::vector<std::string>, int);
    void    who(std::vector<std::string>, int){};
    void    bot(std::vector<std::string>, int){};
};
