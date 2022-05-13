#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "../../utility/utility.hpp"
#include <vector>

class Bot{
    private:
        std::string _name;
        std::string _hostname;
        std::string _port;
        std::string _pass;
        std::string _incomeBuff;

        int _BotSocket;
        std::string _replymessage;
    public:
        Bot(std::string, std::string, std::string);
        ~Bot(){
            std::cout << "bye\n";
            close(_BotSocket);
        };
        void run();
        void reply();
        void getMessage();
        void parse();
};