#include "../UsersService.hpp"

/*
 * Устанавливает новый ник или изменяет старый
 *
 * Command: NICK
 * Parameters: <nickname>
 */

bool    isValidNickname(const std::string& nick) {
    const std::string spec = "-[]^{}";
    if (nick.length() > 9)
        return false;
    for (int i = 0; i < nick.length(); ++i) {
        if (!std::isalnum(nick[i]) && spec.find(nick[i]) == std::string::npos)
            return false;
    }
    return true;
}

void UsersService::nick(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->get_registred()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else if (args.size() < 2) {
        _postman->sendReply(client_socket, ERR_NONICKNAMEGIVEN);

    } else if (findUserByNickname(args[1]) != nullptr) {
        _postman->sendReply(client_socket, ERR_NICKNAMEINUSE(args[1]));

    } else if (!isValidNickname(args[1])) {
        _postman->sendReply(client_socket, ERR_ERRONEUSNICKNAME(args[1]));

    } else {
        if (!_users[client_socket]->get_username().empty()
        && _users[client_socket]->get_nickname().empty()) {
            _postman->sendReply(client_socket, RPL_MOTDSTART);
            _postman->sendReply(client_socket, RPL_MOTD("MESSAGE OF THE DAY HERE"));
            _postman->sendReply(client_socket, RPL_ENDOFMOTD(args[1]));
            _postman->sendReply(client_socket, RPL_WELCOME(args[1]));
        }
        _users[client_socket]->set_nickname(args[1]);
    }
}
