#include "../UsersService.hpp"

/*
 * Устанавливает автоматический ответ на сообщение PRIVMSG
 * Если вызывается без аргументов, отменяет его
 */
void UsersService::away(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->get_registred()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_nickname()));
    } else if (_users[client_socket]->is_away() && args.size() < 2) {
        _postman->sendReply(client_socket, RPL_UNAWAY);
        _users[client_socket]->set_awayMessage("");
    } else if (args.size() > 1) {
        std::string message;
        std::vector<std::string>::iterator it;
        for (it = args.begin() + 1; it != args.end(); ++it)
            message += *it + " ";
        _postman->sendReply(client_socket, RPL_NOWAWAY);
        _users[client_socket]->set_awayMessage(message);
    }
    std::cout << _users[client_socket]->get_awayMessage();
}