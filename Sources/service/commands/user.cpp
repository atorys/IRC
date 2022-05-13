#include "../UsersService.hpp"

void UsersService::user(std::vector<std::string> args, int client_socket) {
    if (_users[client_socket]->get_registred() == false) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));
        return;
    }
    if (args.size() == 5){
        args[4].erase(0, args[4].find(':') + 1);
        for (std::map<int, User*> :: iterator start = _users.begin(); start != _users.end(); start++){
            if (start->second->get_username() == args[1]){
                _postman->sendReply(client_socket, ERR_ALREADYREGISTRED);
                return;
            }
        }
        _users[client_socket]->set_realname(args[4]);
        _users[client_socket]->set_username(args[1]);
        if (_users[client_socket]->is_authenticated()) {
            _postman->sendReply(client_socket, RPL_MOTDSTART(_users[client_socket]->get_nickname()));
            _postman->sendReply(client_socket, RPL_MOTD(_users[client_socket]->get_nickname(), "MESSAGE OF THE DAY HERE"));
            _postman->sendReply(client_socket, RPL_ENDOFMOTD(_users[client_socket]->get_nickname()));
            _postman->sendReply(client_socket, RPL_WELCOME(_users[client_socket]->get_nickname(), _users[client_socket]->get_username(), "kzn.21-school.ru"));
        }
    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "USER"));
    }
}