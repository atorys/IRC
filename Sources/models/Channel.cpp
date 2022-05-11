#include "Channel.hpp"
#include "algorithm"
#include "../utility/utility.hpp"

Channel::Channel(std::string const & channelName,
                User *admin):
                _maxUsersLimit(2000),
                _channelName(channelName) {
                _userList.push_back(admin);
                }

void Channel::addUser(User *user){
    sendAll(user->get_nickname() + " join to channel " + _channelName + " eZ clap!");
    _userList.push_back(user);
}

const std::string &Channel::get_topic() const{ return _topic; }
const std::string &Channel::get_channelname() const { return _channelName; }
std::vector<User *> Channel::get_userlist(){ return _userList; }
std::vector<User *>::size_type Channel::get_count_of_users(){ return _userList.size(); }

// bool Channel::is_invited(User * user){
//     if (_inviteList.find(user) != _inviteList.end()){
//         _inviteList.erase(user);
//         return true;
//     }
//     return false;
// }

User * Channel::get_user_by_nickname(std::string nickname){
    std::vector<User *> ::iterator start = _userList.begin();
    std::vector<User *> ::iterator end = _userList.end();
    nickname = ut::to_lower(nickname);
    while (start != end) {
        if (nickname == (*start)->get_nickname())
            return *start;
        start++;
    }
    return nullptr;
}

// bool Channel::is_banned(const std::string &nickname){
//     for (std::set<std::string>::iterator castMask = _banList.begin();
//         castMask != _banList.end(); ++castMask){
//             if (ut::wildcard(*castMask, nickname)){
//                 return true;
//             }
//     }
//     return false;
// }

// void Channel::remove_from_banList(std::string const &ban){
//     check:
//         std::set<std::string>::iterator castMaskInList = _banList.begin();
//         while (castMaskInList != _banList.end()) {
//             if (ut::wildcard(*castMaskInList, ban)) {
//                 _banList.erase(castMaskInList);
//                 goto check;
//             }
//             ++castMaskInList;
//         }
// }

void Channel::removeUser(User *user){
    std::vector<User *>::iterator start = _userList.begin();
    std::vector<User *>::iterator end = _userList.end();
    while (start != end) {
        if ((*start)->get_socket() == user->get_socket()){
            _userList.erase(start);
            sendAll((*start)->get_nickname() + " left out cute " + _channelName + " :'(");
            break;
        }
    }
    if (get_count_of_users() == 0){
        delete(this);//здесь нужно в uservices почистить вектор каналов иначе он будет обращаться к участку памяти который зафришен->сега
    }
}

void Channel::sendAll(std::string msg){
    for (std::vector<User *>::iterator start = _userList.begin(); start != _userList.end(); start++){
        _postman.sendReply((*start)->get_socket(), msg);
    }
}

void Channel::set_topic(const std::string &topic) {
    this->_topic = topic;
}
