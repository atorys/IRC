#include "../UsersService.hpp"

void UsersService::kick(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));
    } else if (args.size() != 4 && args.size() != 3) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));

    } else if (args.size() == 3){
        if (findChannelByName(args[1]) == nullptr)
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[1]));
        else if (!findChannelByName(args[1])->is_in_channel(findUserByNickname(args[2])))
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(_users[client_socket]->get_nickname(), args[1]));
        else if (findChannelByName(args[1])->get_userlist()[0]->get_socket() != client_socket)
            _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(_users[client_socket]->get_nickname(), args[1]));
        else {
            findChannelByName(args[1])->removeUserFromChannel(findUserByNickname(args[2]), "");
        }

    } else {
        if (findChannelByName(args[1]) == nullptr)
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[1]));
        else if (!findChannelByName(args[1])->is_in_channel(findUserByNickname(args[2])))
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(_users[client_socket]->get_nickname(), args[1]));
        else if (findChannelByName(args[1])->get_userlist()[0]->get_socket() != client_socket)
            _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(_users[client_socket]->get_nickname(), args[1]));
        else
            findChannelByName(args[1])->removeUserFromChannel(findUserByNickname(args[2]), args[3]);
    }
}