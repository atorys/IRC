#include "../UsersService.hpp"

bool    isValidChannel(const std::string& channel) {
    if (channel[0] != '#')
        return false;

    for (unsigned long i = 1; i < channel.length(); ++i) {
        if (!std::isalnum(channel[i]))
            return false;
    }
    return true;
}

/*
 * Добавляет юзера в канал, а если такого канала не существует, создает его
 *
 * @Command: JOIN
 * @Parameters: <channel> {,<channels>}
 */
void UsersService::join(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() != 2) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), args[0]));

    } else {
        std::vector<std::string> channelNames = ut::split(args[1], ",");
        Channel *channel = nullptr;

        for (unsigned long i = 0; i < channelNames.size(); i++) {

            if (!isValidChannel(channelNames[i])) {
                _postman->sendReply(client_socket,
                                    ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), channelNames[i]));
                continue;
            }

            if ((channel = findChannelByName(channelNames[i])) == nullptr) {
                channel = new Channel(channelNames[i], _postman);
                addChannel(channel);
            }

            if (channel->is_in_channel(_users.at(client_socket))) {
                _postman->sendReply(client_socket, ERR_USERONCHANNEL(_users[client_socket]->get_nickname(),
                                                                     _users[client_socket]->get_nickname(),
                                                                     channel->get_channelname()));
                continue;
            }

            if (channel->has_mode(limited) && channel->get_count_of_users() == channel->get_limit()) {
                _postman->sendReply(client_socket, ERR_CHANNELISFULL(_users[client_socket]->get_nickname(), channel->get_channelname()));
                continue;

            }

            if (channel->has_mode(invite_only)) {
                _postman->sendReply(client_socket, ERR_INVITEONLYCHAN(_users[client_socket]->get_nickname(), channel->get_channelname()));
                continue;

            }

            channel->addUser(_users.at(client_socket));
            channel->sendAll(RPL_JOIN(_users[client_socket]->get_fullname(), channel->get_channelname()), nullptr);
            _postman->sendReply(client_socket, RPL_TOPIC(_users[client_socket]->get_nickname(),
                                                         channel->get_channelname(),
                                                         channel->get_topic()));

            std::vector<std::string> arg;
            for (std::vector<User *>::const_iterator it = channel->get_userlist().begin(); it != channel->get_userlist().end(); ++it) {
                arg.clear();
                arg.push_back("NAMES");
                arg.push_back(channel->get_channelname());
                UsersService::names(arg, (*it)->get_socket());
            }
        }
    }
}