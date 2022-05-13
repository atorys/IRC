#include "../UsersService.hpp"

void UsersService::join(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else if (args.size() != 2) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));

    } else {
        std::vector<std::string> channelNames = ut::split(args[1], ",");
        Channel *channel = nullptr;

        for (int i = 0; i < channelNames.size(); i++) {

            if ((channel = findChannelByName(channelNames[i])) == nullptr) {
                channel = new Channel(channelNames[i], _users[client_socket], _postman);
                addChannel(channel);

            } else {
                channel->addUser(_users[client_socket]);
            }

            channel->sendAll(RPL_JOIN(_users[client_socket]->get_nickname(), channel->get_channelname()));
            _postman->sendReply(client_socket, RPL_TOPIC(_users[client_socket]->get_nickname(),
                                                         channel->get_channelname(),
                                                         channel->get_topic()));

            std::vector<std::string> arg;
            arg.push_back("NAMES");
            arg.push_back(channel->get_channelname());
            this->names(arg, client_socket);
        }
    }
}