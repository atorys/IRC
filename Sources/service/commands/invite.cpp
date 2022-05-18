#include "../UsersService.hpp"

        // ERR_NEEDMOREPARAMS(+)         ERR_NOSUCHNICK(+)
        // ERR_NOTONCHANNEL(+)            ERR_USERONCHANNEL(+)
        // ERR_CHANOPRIVSNEEDED - хз, расскажу, лень писать(+)
        // RPL_INVITING(+)                RPL_AWAY(+)

void    UsersService::invite(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));
    }
    if (args.size() != 3) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));

    } else if (findUserByNickname(args[1]) == nullptr) {
        _postman->sendReply(client_socket, ERR_NOSUCHNICK(_users[client_socket]->get_nickname(), args[1]));

    } else if (findChannelByName(args[2]) == nullptr) {
        _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[2]));

    } else {
        if (findChannelByName(args[2])->is_in_channel(findUserByNickname(args[1]))) {
            _postman->sendReply(client_socket, ERR_USERONCHANNEL(_users[client_socket]->get_nickname(), args[1], args[2]));

        } else if (!findChannelByName(args[2])->is_in_channel(_users[client_socket])) {
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(_users[client_socket]->get_nickname(), args[2]));

        } else if (findChannelByName(args[2])->has_mode(invite_only) && !findChannelByName(args[2])->is_operator(_users[client_socket])) {
            _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(_users[client_socket]->get_nickname(), args[2]));

        } else {
            if (findUserByNickname(args[1])->is_away()) {
                _postman->sendReply(client_socket, RPL_AWAY(findUserByNickname(args[1])->get_nickname(),
                     _users[client_socket]->get_nickname(), findUserByNickname(args[1])->get_awayMessage()));
                findChannelByName(args[2])->addUser(findUserByNickname(args[1]));
            } else {
                _postman->sendReply(findUserByNickname(args[1])->get_socket(), RPL_INVITING(_users[client_socket]->get_fullname(), findUserByNickname(args[1])->get_nickname(), args[2]));
                _postman->sendReply(client_socket, RPL_INVITE(_users[client_socket]->get_fullname(), findUserByNickname(args[1])->get_nickname(), args[2]));
            }
        }
    } 
}