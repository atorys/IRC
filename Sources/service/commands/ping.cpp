#include "../UsersService.hpp"

/*
 * Проверка активности клиента/сервера на другой стороне соединения.
 *
 * @Command: PING
 * @Parameters: <server>
 */
void UsersService::ping(std::vector<std::string> args, int client_socket) {
    if (args.size() < 2) {
        _postman->sendReply(client_socket, ERR_NOORIGIN(_users[client_socket]->get_nickname()));

    } else {
        _postman->sendReply(client_socket, "PONG " + args[1] + " " + _users[client_socket]->get_nickname());
    }
}
