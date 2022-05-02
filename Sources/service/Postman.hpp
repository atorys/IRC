//
// Created by Achiote Tory on 5/2/22.
//

#pragma once
#include <map>
#include "../models/User.hpp"

class Postman {
    std::map<int, std::string> _replies;
    std::map<int, std::string> _errors;

public:
    Postman();
    void sendReply(User* user, int code) const;
    void sendError(User* user, int code) const;
};