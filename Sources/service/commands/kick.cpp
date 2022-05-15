#include "../UsersService.hpp"

void UsersService::kick(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));
    } else if (args.size() == 4 || args.size() == 3) {
        Channel *channel = nullptr;
        User    *user = nullptr;

        if ((channel = findChannelByName(args[1])) == nullptr) {
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[1]));

        } else if ((user = findUserByNickname(args[2])) == nullptr) {
            _postman->sendReply(client_socket, ERR_NOSUCHNICK(_users[client_socket]->get_nickname(), args[2]));
        }
        else if (!channel->is_in_channel(user)) {
            _postman->sendReply(client_socket, ERR_USERNOTINCHANNEL(_users[client_socket]->get_nickname(), user->get_nickname(), args[1]));

        } else if (channel->get_userlist()[0]->get_socket() != client_socket) {
            _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(_users[client_socket]->get_nickname(), args[1]));

        } else {
            channel->sendAll(RPL_KICK(_users[client_socket]->get_nickname(), channel->get_channelname(), user->get_nickname(),
                                      (args.size() == 4 ? args[3] : "KICKED")), nullptr);
            channel->removeUserFromChannel(user);
        }

    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));
    }
}