
#include <iostream>
#include "Bot.hpp"
int main(int argc, char *argv[]){
    if (argc != 4){
        std::cerr << "Usage: <" << argv[0] << "> <hostname> <port> <pass>\n";
        return (1);
    }
    Bot newBot(argv[1], argv[2], argv[3]);
    try{
        newBot.run();
    } catch (...){}
    return (0);
}