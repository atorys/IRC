#include "../UsersService.hpp"

/*
 * Сессия пользователя заканчивается с QUIT-сообщением.
 *
 * @Command: QUIT
 * @Parameters: <message>
 */
void UsersService::quit(std::vector<std::string> args, int client_socket) {
    _postman->sendReply(client_socket, RPL_QUIT(_users[client_socket]->get_nickname().empty() ?
                                                "*" : _users[client_socket]->get_nickname(),
                                                args.size() > 1 ? args[1] : "silently"));
    _users[client_socket]->set_connected(false);
}