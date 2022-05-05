//
// Created by Achiote Tory on 5/2/22.
//

#include "Postman.hpp"
#include "sys/socket.h"

void Postman::sendReply(int user, std::string reply) {
    reply += "\r\n";
    if (send(user, reply.c_str(), reply.size(), 0) == -1) {
        std::cerr << "send message to client failure\n";
        exit(EXIT_FAILURE);
    }
}
