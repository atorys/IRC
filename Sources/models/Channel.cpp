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

User * Channel::get_user_by_nickname(std::string nickname){
    std::set<User *> ::iterator start = _userList.begin();
    std::set<User *> ::iterator end = _userList.end();
    nickname = ut::to_lower(nickname);
    while (start != end) {
        if (nickname == (*start)->get_nickname())
            return *start;
        start++;
    }
    return NULL;
}

bool Channel::is_banned(const std::string const &nickname){
    for (std::set<std::string>::iterator castMask = _banList.begin();
        castMask != _banList.end(); ++castMask){
            if (ut::wildcard(*castMask, nickname)){
                return true;
            }
    }
    return false;
}

void Channel::remove_from_banList(std::string const &ban){
    check:
        std::set<std::string>::iterator castMaskInList = _banList.begin();
        while (castMaskInList != _banList.end()) {
            if (ut::wildcard(*castMaskInList, ban)) {
                _banList.erase(castMaskInList);
                goto check;
            }
            ++castMaskInList;
        }
}

