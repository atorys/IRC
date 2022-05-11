//
// Created by atory on 02.05.22.
//

#pragma once
#include <iostream>

class Service {
public:
    virtual void    addUser(int) = 0;
    virtual void    removeUser(int) = 0;
    virtual bool    isConnected(int) = 0;
    virtual void    processRequest(std::string, int client_socket) = 0;

    virtual ~Service() {}
};


