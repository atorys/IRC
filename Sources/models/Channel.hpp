
#pragma once

#include "iostream"
#include "User.hpp"
#include <map>

class Channel {
    private:
        const std::string&                      _name;
        const std::string&					    _channelPass;
        std::map<const int, User*>				_usersChannel;
    public:
        Channel(User *, const std::string& channelPass, const std::string& name);
        ~Channel(){}
        void    addUser(User *);
        void    removeUser(User *);

};