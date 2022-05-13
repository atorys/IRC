#include "../UsersService.hpp"

/*
 * Возвращает список активных пользователей из входящего списка
 *
 * @Command: ISON
 * @Parameters: {<nickname1> <nickname2>...}
 */
void UsersService::ison(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else if (args.size() == 1) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "ISON"));

    } else {
        std::string nicknames;
        for (int i = 1; i < args.size(); ++i) {
            if (findUserByNickname(args[i]) != nullptr)
                nicknames += ' ' + args[i];
        }
        _postman->sendReply(client_socket, RPL_ISON(_users[client_socket]->get_nickname(), nicknames));
    }
}