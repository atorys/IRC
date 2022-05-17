
#pragma once

#include "iostream"
#include "User.hpp"
#include "../service/Postman.hpp"
#include <vector>

class User;
class Postman;

enum Mode {
    none = 0,               // 0000000000
    oper = 1 << 0,          // 0000000001
    priv = 1 << 1,          // 0000000010
    invite_only = 1 << 2,   // 0000000100
    limited = 1 << 3,       // 0000001000
    topic = 1 << 4,         // 0000010000
};

class Channel {
    private:
        Postman*                                _postman;
        std::string                             _channelName;
        std::string                             _topic;
        std::vector<User *>                     _userList;
        std::vector<User *>                     _operList;
        int                                     _modes;
        int                                     _maxUserCount;

    public:
        Channel(std::string const &, Postman *);
        ~Channel(){};

        void                            addUser(User *user);
        void                            removeUserFromChannel(User *user);
        void                            set_topic(const std::string &topic);

        std::string const               &get_topic() const;
        std::string const               &get_channelname() const;
        const std::vector<User *>       &get_userlist() const;
        const std::vector<User *>       &get_operList() const;

        int                             get_count_of_users();
        User*                           get_user_by_nickname(std::string nickname);
        void                            sendAll(const std::string& msg, User*);

        bool                            is_in_channel(User *user) const;
        bool                            is_operator(User *user) const;

        void                            set_mode(Mode);
        void                            unset_mode(Mode);
        bool                            has_mode(Mode) const;
        std::string                     show_mode() const;
        // bool is_invited(User * user);
};