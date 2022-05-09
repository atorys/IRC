#include "Channel.hpp"
#include "algorithm"

Channel::Channel(std::string const & channelName,
                std::string const & channelPass,
                User *admin): _channelName(channelName),
                _channelPass(channelPass) {
                _userList.insert(admin);
                }

bool Channel::is_invited(User * user){
    if (_inviteList.find(user) != _inviteList.end()){
        _inviteList.erase(user);
        return true;
    }
    return false;
}

User * Channel::get_user_by_username(std::string nickname){
    std::set<User *> ::iterator start = _userList.begin();
    std::set<User *> ::iterator end = _userList.end();
    std::transform(nickname.begin(), nickname.end(), nickname.begin(), ::tolower);
    while (start != end) {
        if (nickname == (*start)->get_username())
            return *start;
        start++;
    }
    return NULL;
}

bool Channel::is_banned(const std::string const &nickname){
    std::set<User *>::iterator start = _banList.begin();
    std::set<User *>::iterator end = _banList.end();
    while (start != end) {
        if (nickname == (*start)->get_username())
            return true;
    }
    return false;
}