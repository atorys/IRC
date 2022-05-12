#include "../UsersService.hpp"

/*
 * Устанавливает автоматический ответ на сообщение PRIVMSG
 * Если вызывается без аргументов, отменяет его
 *
 * @Command: AWAY
 * @Parameters: <message>
 */
void UsersService::away(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else if (_users[client_socket]->is_away() && args.size() == 1) {
        _postman->sendReply(client_socket, RPL_UNAWAY(_users[client_socket]->get_nickname()));
        _users[client_socket]->set_awayMessage("");

    } else if (args.size() > 1) {
        _postman->sendReply(client_socket, RPL_NOWAWAY(_users[client_socket]->get_nickname()));
        _users[client_socket]->set_awayMessage(args[1]);
    }
}