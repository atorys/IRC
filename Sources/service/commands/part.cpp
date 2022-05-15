#include "../UsersService.hpp"

void UsersService::part(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() == 3 || args.size() == 2) {
        Channel *channel = nullptr;
        std::vector<std::string> splitedStr = ut::split(args[1], ",");
        for (std::vector<std::string>::iterator start = splitedStr.begin(); start != splitedStr.end(); start++){
            if ((channel = findChannelByName(*start)) == nullptr)
                _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), *start));
            else if (!channel->is_in_channel(_users[client_socket]))
                _postman->sendReply(client_socket, ERR_NOTONCHANNEL(_users[client_socket]->get_nickname(), *start));
            else {
                channel->sendAll(RPL_PART(_users[client_socket]->get_nickname(), channel->get_channelname(),
                                                args.size() == 3 ? args[2] : "silently"), nullptr);
                channel->removeUserFromChannel(_users[client_socket]);
            }
        }

    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));
    }
}