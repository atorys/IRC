
#pragma once

#include "iostream"
#include "User.hpp"
#include "../service/Postman.hpp"
#include <map>
#include <set>

class User;
class Postman;

class Channel {
    private:
        uint32_t _maxUsersLimit;
        Postman                                 _postman;
        std::string                             _channelName;
        std::string                             _topic;
        std::vector<User *>                     _userList;

    public:
        Channel(std::string const & channelName, User *admin);
        ~Channel(){};

        void                            addUser(User *user);
        void                            removeUser(User *user);
        void                            set_topic(const std::string &topic);
        std::string const               &get_topic() const;
        std::string const               &get_channelname() const;
        std::vector<User *>             get_userlist();
        std::vector<User *>::size_type  get_count_of_users();
        User*                           get_user_by_nickname(std::string nickname);
        void                            sendAll(std::string msg);
        // bool is_in_channel(User *user) const;
        // bool is_invited(User * user);
};