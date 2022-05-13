#include "Channel.hpp"
#include "algorithm"
#include "../utility/utility.hpp"

Channel::Channel(std::string const & channelName,
                User *admin, Postman *postman):
                _postman(postman),
                _channelName(channelName) {
                _userList.push_back(admin);
                }

void Channel::addUser(User *user){
    _userList.push_back(user);
//    sendAll(user->get_nickname() + " join to channel " + _channelName + " eZ clap!");
}

const std::string &Channel::get_topic() const{ return _topic; }
const std::string &Channel::get_channelname() const { return _channelName; }
std::vector<User *> &Channel::get_userlist(){ return _userList; }
int Channel::get_count_of_users(){ return _userList.size(); }


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
        if (user->get_socket() == (*start)->get_socket())
            return true;
    }
    return false;
}

void Channel::removeUserFromChannel(User *user, std::string msg){
    std::vector<User *>::iterator start = _userList.begin();
    std::vector<User *>::iterator end = _userList.end();
    while (start != end) {
        if ((*start)->get_socket() == user->get_socket()){
            _userList.erase(start);
            if (msg.empty())
                sendAll((*start)->get_nickname() + " left our cute " + _channelName + " :'(");
            else
                sendAll((*start)->get_nickname() + " left our cute " + _channelName + " :'(" + " reason: " + msg);
            break; 
        }
        start++;
    }
    if (get_count_of_users() == 0){
        delete(this);//здесь нужно в uservices почистить вектор каналов иначе он будет обращаться к участку памяти который зафришен->сега
    }
}

void Channel::sendAll(const std::string& msg) {
    for (std::vector<User *>::iterator start = _userList.begin(); start != _userList.end(); start++){
        _postman->sendReply((*start)->get_socket(), msg);
    }
}

void Channel::set_topic(const std::string &topic) {
    this->_topic = topic;
}
