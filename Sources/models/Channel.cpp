#include "Channel.hpp"
#include "algorithm"
#include "../utility/utility.hpp"

Channel::Channel(std::string const & channelName, Postman *postman):
                _postman(postman),
                _channelName(channelName) {}

void Channel::addUser(User *user){
    _userList.push_back(user);
//    sendAll(user->get_nickname() + " join to channel " + _channelName + " eZ clap!");
}

const std::string &Channel::get_topic() const{ return _topic; }
const std::string &Channel::get_channelname() const { return _channelName; }
std::vector<User *> &Channel::get_userlist(){ return _userList; }
int Channel::get_count_of_users(){ return _userList.empty() ? 0 : (int)_userList.size(); }


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

bool Channel::is_in_channel(User *user){
    for (std::vector<User *>::iterator start = _userList.begin(); start != _userList.end(); start++){
        if (user == (*start))
            return true;
    }
    return false;
}

void Channel::removeUserFromChannel(User *user, std::string msg){
    std::vector<User *>::iterator start = _userList.begin();
    while (start != _userList.end()) {
        if ((*start) == user) {
            sendAll(RPL_PART(user->get_nickname(), this->_channelName, msg), nullptr);
            _userList.erase(start);
            break;
        }
        start++;
    }
}

void Channel::sendAll(const std::string& msg, User *skippedUser) {
    for (std::vector<User *>::iterator start = _userList.begin(); start != _userList.end(); start++){
        if (*start != skippedUser)
            _postman->sendReply((*start)->get_socket(), msg);
    }
}

void Channel::set_topic(const std::string &topic) {
    this->_topic = topic;
}
