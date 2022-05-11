
#pragma once

#include "iostream"
#include "User.hpp"
#include <map>
#include <set>
class User;

class Channel {
    private:
        uint32_t _maxUsersLimit;
        std::string                             _channelName;
        std::string                             _topic;
        std::set<User *>                        _userList;
        std::set<User *>                        _inviteList;
        std::set<std::string>                        _banList;

    public:
        Channel(std::string const & channelName,
                User *admin);

        ~Channel(){}

        void addUser(User *user){
            _userList.insert(user);
        }

        std::string const &get_topic()const{
            return _topic;
        }

        void    set_topic(const std::string &topic);

        std::set<User *> get_userlist(){
            return _userList;
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
        bool is_banned(const std::string &nickname);
        User * get_user_by_username(std::string nickname);
        bool is_invited(User * user);
};