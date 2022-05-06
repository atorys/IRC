
#pragma once

#include "iostream"
#include "User.hpp"
#include <map>

class Channel {
    private:
        const std::string&					_channelPass;
        std::map<int, User*>				_usersChannel;
    public:
        Channel(User *, const std::string& channelPass);
        ~Channel(){}
        void    addUser(User *);
        void    removeUser(User *);

};