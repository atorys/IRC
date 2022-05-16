#include "Bot.hpp"

static void Error(std::string msg){
    std::cout << "Error: " << msg << "\n";
    exit(1);
}

static std::string Jokes[][2] = {
{"Почему неудобно спать в бетономешалке?."},
{"Кто ноет, тот говна не стоит"},
};

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
    _is_auth_confirmed = false;
}

void Bot::run(){
    _replymessage = "PASS " + _pass + "\r\n"\
    "NICK " + _name + "\r\n"\
    "USER BOT bot bot :work work \r\n";
    while (true){
        reply();
        getMessage();
        parse();
        execute();
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
    char buff[2048] = {0};
    if ((Bytes = recv(_BotSocket, buff, sizeof(buff) - 1, 0)) > 0){
        _incomeBuff += buff;
    } else {
        throw("error");
    }
}

std::string Bot::getRequest() {
    std::string::size_type index = _incomeBuff.find("\n\r");
    std::string request = _incomeBuff.substr(0, index);
    _incomeBuff.erase(0, index);
    return request;
}

void Bot::parse(){
    _request = getRequest();
    std::cout << _request << "\n";
    if (_request.find("PRIVMSG") != std::string::npos || _request.find("NOTICE") != std::string::npos){
        _currentType = "PRIVMSG";
    } else if (_request.find(":ircserv 375 BOT :- Message of the day -") != std::string::npos) {
        _is_auth_confirmed = true;
    } else if (_request.find(":ircserv 451 * :You have not registered") != std::string::npos || _request.find("You may not reregister") != std::string::npos || _incomeBuff.find(":ircserv 464 * :Password incorrect") != std::string::npos){
        _currentType = "AUTH";
    } else 
        _currentType = "SKIP";
}

void Bot::execute(){
    std::cout << _request << "\n";
    if (_currentType == "PRIVMSG"){
        _request.erase(0 , 1);
        std::string name = _request.substr(0, _request.find(" "));
        int positionInMsg = _request.find(':');
        if (positionInMsg != _request.npos && positionInMsg != _request.length() - 1){
            _request = _request.substr(positionInMsg + 1);
            if (_request.find("joke") != std::string::npos || _request.find("анекдот") != std::string::npos){
                std::srand(std::time(NULL));
                _replymessage = "PRIVMSG " + name + " :" + *Jokes[std::rand() % 2] + "\r\n";
            }
        }
    } else if (_currentType == "AUTH"){
        if (_is_auth_confirmed == true){
            sleep(3);
            return;
        }
        static int tries = 3;
        if (tries < 0){
            std::cout << "error: authentication failed.";
            throw("end");
        }
        std::cout << "You wrote a wrong password, try again.\n";
        std::cin >> _pass;
        std::cout << "You written a new password : " << _pass << ". Let's try it.\n";
        _replymessage = "PASS " + _pass + "\r\n"\
            "NICK " + _name + "\r\n"\
            "USER BOT bot bot :work work \r\n";
        tries--;
    } else if (_currentType == "SKIP"){
        return;
    }
}
