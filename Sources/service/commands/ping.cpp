#include "../UsersService.hpp"

/*
 * Проверка активности клиента/сервера на другой стороне соединения.
 *
 * @Command: PING
 * @Parameters: <server>
 */
void UsersService::ping(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else if (args.size() < 2) {
        _postman->sendReply(client_socket, ERR_NOORIGIN);

    } else {
        _postman->sendReply(client_socket, "PONG " + args[1] + " " + _users[client_socket]->get_nickname());
    }
}
