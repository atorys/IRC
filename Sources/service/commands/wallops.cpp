#include "../UsersService.hpp"

void    UsersService::wallops(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));
    }
    if (args.size() != 2){
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));
    } else {
        if (_users[client_socket]->has_mode(UserOper)){
            std::map<int ,User *>::iterator start = _users.begin();
            while (start != _users.end()){
                if (start->second->has_mode(UserOper)){
                    if (!start->second->has_mode(wallopsOff)){
                        _postman->sendReply((start)->second->get_socket(), RPL_PRIVMSG(_users[client_socket]->get_nickname(), start->second->get_nickname(), args[1]));
                    }
                }
                start++;
            }
        }
    }
}