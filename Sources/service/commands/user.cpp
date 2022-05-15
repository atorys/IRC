#include "../UsersService.hpp"

/*
 * Устанавливает юзернейм и реальное имя пользователя для регистрации
 *
 * @Command: USER
 * @Parameters: <username> <host> <server> :<realname>
 */
void UsersService::user(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->get_registred()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() == 5) {
        args[4].erase(0, args[4].find(':') + 1);
        for (std::map<int, User*> :: iterator start = _users.begin(); start != _users.end(); start++){
            if (start->second->get_username() == args[1]) {
                _postman->sendReply(client_socket, ERR_ALREADYREGISTRED(_users[client_socket]->get_nickname().empty() ?
                                                                        "*" : _users[client_socket]->get_nickname()));
                return;
            }
        }
        _users[client_socket]->set_realname(args[4]);
        _users[client_socket]->set_username(args[1]);
        if (_users[client_socket]->is_authenticated())
            welcomeUser(client_socket);

    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "USER"));
    }
}