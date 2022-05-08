//
// Created by Achiote Tory on 5/2/22.
//

#include "Postman.hpp"

std::string Postman::getReply(int user) const {
    if (_replies.find(user) == _replies.end())
        return "";
    return _replies.at(user);
}

std::string Postman::getRequest(int user) const {
    if (_requests.find(user) == _replies.end())
        return "";
    return _requests.at(user);
}

void Postman::clearReply(int user) {
    _replies[user].clear();
}
void Postman::clearRequest(int user) {
    _requests[user].clear();
}

void Postman::sendReply(int user, const std::string& reply) {
    _replies[user] += reply;
    _replies[user] += "\r\n";
}

void Postman::sendRequest(int user, const std::string& request) {
    _requests[user] += request;
}
