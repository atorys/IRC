#include "Channel.hpp"
#include "algorithm"
#include "../utility/utility.hpp"

Channel::Channel(std::string const & channelName,
                User *admin):
                _maxUsersLimit(2000),
                _channelName(channelName) {
                    std::cout << channelName << ": created!" << "\n";
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
    nickname = ut::to_lower(nickname);
    while (start != end) {
        if (nickname == (*start)->get_username())
            return *start;
        start++;
    }
    return nullptr;
}

bool Channel::is_banned(const std::string &nickname){
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