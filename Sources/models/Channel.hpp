
#pragma once

#include "iostream"
#include "User.hpp"
#include "../service/Postman.hpp"
#include <vector>

class User;
class Postman;

class Channel {
    private:
        Postman*                                _postman;
        std::string                             _channelName;
        std::string                             _topic;
        std::vector<User *>                     _userList;

    public:
        Channel(std::string const &, User *, Postman *);
        ~Channel(){};

        void                            addUser(User *user);
        void                            removeUserFromChannel(User *user, std::string msg);
        void                            set_topic(const std::string &topic);
        std::string const               &get_topic() const;
        std::string const               &get_channelname() const;
        std::vector<User *>             &get_userlist();
        int                             get_count_of_users();
        User*                           get_user_by_nickname(std::string nickname);
        void                            sendAll(const std::string& msg, bool skipLastUser);
        bool                            is_in_channel(User *user);
        // bool is_invited(User * user);
};