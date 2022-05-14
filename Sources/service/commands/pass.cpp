#include "../UsersService.hpp"

/*
 * Регистрирует соединение клиента с сервером
 */
void UsersService::pass(std::vector<std::string> args, int client_socket) {
    if (_users[client_socket]->get_registred()) {
        _postman->sendReply(client_socket, ERR_ALREADYREGISTRED(_users[client_socket]->get_nickname().empty() ?
                                                                "*" : _users[client_socket]->get_nickname()));
    } else if (args.size() < 2) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname().empty() ?
                                                              "*" : _users[client_socket]->get_nickname(), "PASS"));
    } else if (std::equal(_password.begin(), _password.end(), args[1].begin())) {
        _users[client_socket]->set_registred(true);
    } else {
        _postman->sendReply(client_socket, ERR_PASSWDMISMATCH(_users[client_socket]->get_nickname().empty() ?
                                                              "*" : _users[client_socket]->get_nickname()));
    }
}
