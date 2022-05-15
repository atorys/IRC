#include "Bot.hpp"

static void Error(std::string msg){
    std::cout << "Error: " << msg << "\n";
    exit(1);
}

Bot::Bot(std::string hostname, std::string port, std::string pass): 
        _name("BOT"), _hostname(hostname), _port(port), _pass(pass) {
    
    if (1024 > std::atoi(_port.c_str()) || std::atoi(_port.c_str()) > 65535)
        Error("wrong port number. Please enter the correct port number in range [1024, 65535]");
    hostent *host = NULL;
    host = gethostbyname(hostname.c_str());
    if (host == NULL)
        Error("incorrect hostname");
    std::vector<std::string> splittedaddres = ut::split(hostname, ".");
    sockaddr_in address = {std::atoi(splittedaddres[0].c_str()), 
                    std::atoi(splittedaddres[1].c_str()),
                    {std::atoi(splittedaddres[2].c_str())},
                    {std::atoi(splittedaddres[3].c_str())}};
    address.sin_family = AF_INET;
    address.sin_port = htons(std::atoi(_port.c_str()));
    if (inet_aton(host->h_name, &address.sin_addr) == 0)
        Error("Incorrect ip address has been passed");
    if ((_BotSocket = socket(address.sin_family, SOCK_STREAM, 0)) == -1){
        Error("Socket troubles");
    }
    if (connect(_BotSocket, (sockaddr*)&address, sizeof(address)) == -1){
        std::cout << errno << " ";
        Error("cannot connect to server");
    }
}

void Bot::run(){
    _replymessage = "PASS " + _pass + "\r\n"\
    "NICK " + _name + "\r\n"\
    "USER BOT bot bot :work work \r\n";
    while (true){
        reply();
        getMessage();
    }     
}

void Bot::reply(){
    if (!_replymessage.empty()){
        send(_BotSocket, _replymessage.c_str(), _replymessage.length(), 0);
        _replymessage.clear();
    }
}

void Bot::getMessage(){
    int Bytes;
    char buff[511] = {0};
    if ((Bytes = recv(_BotSocket, buff, sizeof(buff) - 1, 0)) > 0){
        _incomeBuff += buff;
    } else {
        throw("error");
    }
}

void Bot::parse(){
    if (_incomeBuff.rend()[1] != '\n')
        return;
    else
        
}