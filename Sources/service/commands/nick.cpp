#include "../UsersService.hpp"

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

/*
 * Устанавливает новый ник или изменяет старый
 *
 * @Command: NICK
 * @Parameters: <nickname>
 */
void UsersService::nick(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->get_registred()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() < 2) {
        _postman->sendReply(client_socket, ERR_NONICKNAMEGIVEN(_users[client_socket]->get_nickname().empty() ?
                                                               "*" : _users[client_socket]->get_nickname()));

    } else if (findUserByNickname(args[1]) != nullptr) {
        _postman->sendReply(client_socket, ERR_NICKNAMEINUSE(_users[client_socket]->get_nickname().empty() ?
                                                            "*" : _users[client_socket]->get_nickname(), args[1]));

    } else if (!isValidNickname(args[1])) {
        _postman->sendReply(client_socket, ERR_ERRONEUSNICKNAME(_users[client_socket]->get_nickname().empty() ?
                                                                "*" : _users[client_socket]->get_nickname(), args[1]));

    } else {
        if (!_users[client_socket]->is_authenticated() && !_users[client_socket]->get_username().empty()) {
            _postman->sendReply(client_socket, RPL_MOTDSTART(args[1]));
            _postman->sendReply(client_socket, RPL_MOTD(args[1], "MESSAGE OF THE DAY HERE"));
            _postman->sendReply(client_socket, RPL_ENDOFMOTD(args[1]));
            _postman->sendReply(client_socket, RPL_WELCOME(args[1], _users[client_socket]->get_username(), "kzn.21-school.ru"));
        }
        _users[client_socket]->set_nickname(args[1]);
    }
}
