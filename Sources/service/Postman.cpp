//
// Created by Achiote Tory on 5/2/22.
//

#include "Postman.hpp"
#include "sys/socket.h"

#define RPL_MOTDSTART   ":- <server> Message of the day - "
#define RPL_MOTD        ":- <Have a nice day and log in to connect!>"
#define RPL_ENDOFMOTD   ":End of /MOTD command"
#define ERR_NEEDMOREPARAMS "<USER> :Not enough parameters"
#define ERR_ALREADYREGISTRED "You may not reregister"

Postman::Postman() {
    _replies[375] = RPL_MOTDSTART;
    _replies[372] = RPL_MOTD;
    _replies[461] = ERR_NEEDMOREPARAMS;
    _replies[376] = RPL_ENDOFMOTD;
    _replies[462] = ERR_ALREADYREGISTRED;
}

void Postman::sendReply(User* user, int n) const {
    std::string message = std::to_string(n) + " " + _replies.at(n) + "\r\n";
    if (send(user->get_socket(), message.c_str(), message.size(), 0) == -1)
        throw std::runtime_error("send message to client failure\n");
}
