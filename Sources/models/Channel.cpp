#include "Channel.hpp"

Channel::Channel(User* admin,const std::string& channelPass) : _channelPass(channelPass){
    this->_usersChannel.emplace(admin->get_socket(), admin);
}