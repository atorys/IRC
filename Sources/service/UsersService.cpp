//
// Created by Achiote Tory on 5/2/22.
//

#include "UsersService.hpp"

UsersService::UsersService(const std::string& password, Postman* postman)
                        :
                        _password(password),
                        _postman(postman) {
    _commands["PASS"] = &UsersService::pass;
    _commands["USER"] = &UsersService::user;
    _commands["NICK"] = &UsersService::nick;
    _commands["JOIN"] = &UsersService::join;
    _commands["KICK"] = &UsersService::kick;
    _commands["PRIVMSG"] = &UsersService::privmsg;//kekis(не совершенная команда)
    _commands["NOTICE"] = &UsersService::notice;
    _commands["AWAY"] = &UsersService::away;
    _commands["PING"] = &UsersService::ping;
    _commands["PONG"] = &UsersService::pong;
    _commands["QUIT"] = &UsersService::quit;
    _commands["ISON"] = &UsersService::ison;
    _commands["LIST"] = &UsersService::list;
    _commands["NAMES"] = &UsersService::names;
    _commands["TOPIC"] = &UsersService::topic;
    _commands["PART"] = &UsersService::part;
    _commands["WHO"] = &UsersService::who;
    _commands["BOT"] = &UsersService::bot;
}

void UsersService::addUser(int client_socket) {
    _users[client_socket] = new User(client_socket);
    std::cout << "[CONNECTION #" << client_socket << "]\n";
}

void UsersService::addChannel(Channel *channel) {
    _channels.push_back(channel);
    std::cout << "[CHANNEL " << channel->get_channelname() << "]\n";
}

void UsersService::removeEmptyChannels() {
    for (std::vector<Channel *>::iterator start = _channels.begin(); start != _channels.end(); ) {

        if ((*start)->get_count_of_users() == 0) {
            std::cout << "\033[37m[CHANNEL " << (*start)->get_channelname() << " ERASED]\033[0m\n";
            delete (*start);
            start = _channels.erase(start);

        } else {
            start++;
        }
    }
}

void UsersService::removeUser(int client_socket) {
    std::cout << "\033[37m///////////////\nerasing " + _users[client_socket]->get_nickname() + '\n';

    for (std::vector<Channel *>::iterator start = _channels.begin(); start != _channels.end(); start++) {
        if ((*start)->is_in_channel(_users[client_socket])) {
            (*start)->removeUserFromChannel(_users[client_socket]);
            (*start)->sendAll(RPL_PART(_users[client_socket]->get_nickname(), (*start)->get_channelname(), "QUITED"), nullptr);
        }
    }
    removeEmptyChannels();

    std::cout << "\033[37m";
    if (_users[client_socket]->get_nickname().empty())
        std::cout << "user " << client_socket << " just left\n";
    else
        std::cout << _users[client_socket]->get_nickname() << " just left\n";
    std::cout << "///////////////\n\033[0m";

    delete _users.at(client_socket);
    _users.erase(client_socket);
}

bool UsersService::isConnected(int client_socket) {
    return _users[client_socket]->is_connected();
}

User *UsersService::findUserByNickname(const std::string& nickname) {
    std::map<int, User*>::iterator start;
    for (start = _users.begin(); start != _users.end(); start++) {
        if (start->second->get_nickname() == nickname) {
            return start->second;
        }
    }
    return nullptr;
}

Channel *UsersService::findChannelByName(const std::string &name){
    std::vector<Channel *>::iterator start;
    for (start = _channels.begin(); start != _channels.end(); start++){
        if ((*start)->get_channelname() == name){
            return *start;
        }
    }
    return nullptr;
}

void UsersService::processRequest(std::string request, int client_socket) {
    if (_users[client_socket]->get_nickname().empty())
        std::cout << "user " << client_socket << ": " << request;
    else
        std::cout << _users[client_socket]->get_nickname() << ":" << request;
    std::vector<std::string> arguments = ut::splitForCmd(request);
    if (_commands.find(arguments[0]) != _commands.end()) {
        (this->*_commands[arguments[0]])(arguments, client_socket);
    } else {
        _postman->sendReply(client_socket, ERR_UNKNOWNCOMMAND(_users[client_socket]->get_nickname(), arguments[0]));
    }
    removeEmptyChannels();
}

void UsersService::welcomeUser(int client_socket) {
    _postman->sendReply(client_socket, RPL_MOTDSTART(_users[client_socket]->get_nickname()));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), " .              +   .                .   . .     .  ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "                   .                    .       .     *"));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "  .       *                        . . . .  .   .  + ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "            \"You Are Here\"            .   .  +  . . ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), ".                 |             .  .   .    .    . ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "                  |           .     .     . +.    +  ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "                 \\|/            .       .   . ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "        . .       V          .    * . . .  .  +   ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "           +      .           .   .      +"));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "                            .       . +  .+. ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "  .                      .     . + .  . .     .      ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "           .      .    .     . .   . . .        ! /"));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "      *             .    . .  +    .  .       - O -"));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "          .     .    .  +   . .  *  .       . / |"));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "               . + .  .  .  .. +  ."));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), ".      .  .  .  *   .  *  . +..  .            *"));
    _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), " .      .   . .   .   .   . .  +   .    .            +"));
    _postman->sendReply(client_socket, RPL_ENDOFMOTD(_users[client_socket]->get_nickname()));
    _postman->sendReply(client_socket, RPL_WELCOME(_users[client_socket]->get_nickname(), _users[client_socket]->get_username(), "kzn.21-school.ru"));
}
