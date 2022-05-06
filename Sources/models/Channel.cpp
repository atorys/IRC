#include "Channel.hpp"

Channel::Channel(User* admin,const std::string& channelPass, const std::string& name) :  _name(name), _channelPass(channelPass) {
    this->_usersChannel.insert(std::pair<const int, User*>(admin->get_socket(), admin));
}