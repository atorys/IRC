//
// Created by Achiote Tory on 5/2/22.
//

#include "Postman.hpp"

std::string Postman::getReply(int user) {
    std::string reply = _replies.at(user);
    clearReplies(user);
    return reply;
}

std::string Postman::getRequest(int user) {
    std::string::size_type index = _requests.at(user).find('\n') + 1;
    std::string request = _requests.at(user).substr(0, index);
    _requests[user].erase(0, index);
    return request;
}

void Postman::sendReply(int user, const std::string& reply) {
    _replies[user] += reply;
    _replies[user] += "\r\n";
}

void Postman::sendRequest(int user, const std::string& request) {
    _requests[user] += request;
}

bool Postman::hasRequest(int user) const {
    return (_requests.find(user) != _requests.end() &&
            !_requests.at(user).empty() &&
            _requests.at(user).find('\n') != std::string::npos);
}

bool Postman::hasReply(int user) const {
    return (_replies.find(user) != _replies.end() && !_replies.at(user).empty());
}

void Postman::clearRequests(int user) {
    _requests[user].clear();
}

void Postman::clearReplies(int user) {
    _replies[user].clear();
}
