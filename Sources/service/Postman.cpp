//
// Created by Achiote Tory on 5/2/22.
//

#include "Postman.hpp"
#include "sys/socket.h"


Postman::Postman() {}

void Postman::sendReply(int user, std::string reply, const std::string& argument1, const std::string& argument2) {
    int index;

    if ((index = reply.find(INSERTER)) != std::string::npos) {
        reply.replace(index, strlen(INSERTER), argument1);
    } else if ((index = reply.find(INSERTER)) != std::string::npos) {
        reply.replace(index, strlen(INSERTER), argument2);
    }
    reply += "\r\n";
    if (send(user, reply.c_str(), reply.size(), 0) == -1)
        throw std::runtime_error("send message to client failure\n");
}
