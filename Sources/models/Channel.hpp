
#pragma once

#include "iostream"
#include "User.hpp"
#include <map>
#include <set>
class User;

class Channel {
    private:
        uint32_t _maxUsersLimit = 2000;
        std::string                             _channelName;
        std::string                             _channelPass;
        std::string                             _topic;
        std::set<User *>                        _userList;
        std::set<User *>                        _inviteList;
        std::set<User *>                        _banList;

    public:
        Channel(std::string const & channelName,
                std::string const & channelPass,
                User *admin);

        ~Channel(){}

        std::string const &get_topic()const{
            return _topic;
        }

        std::string const &get_channelname() const {
            return _channelName;
        }

        void removeUser(User *user);
        bool is_in_channel(User *user) const;
        std::set<User *>::size_type get_count_of_users(){
            return _userList.size();
        }

        void sendAll(std::string msg, User * user);
        void add_to_banList(std::string ban);
        void remove_from_banList(std::string const &ban);
        bool is_banned(const std::string const &nickname);
        User * get_user_by_nickname(std::string nickname);
        bool is_invited(User * user);
};