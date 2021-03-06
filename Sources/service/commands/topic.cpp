#include "../UsersService.hpp"

/*
 * Используется для изменения или просмотра топика канала.
 *
 * @Command: TOPIC
 * @Parameters: <channel> {<topic>}
 */
void UsersService::topic(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() < 2 || args.size() > 3) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "TOPIC"));

    } else {
        Channel *channel;

        if ((channel = findChannelByName(args[1])) == nullptr) {
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(),args[1]));

        } else if (channel->get_user_by_nickname(_users[client_socket]->get_nickname()) == nullptr) { 
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(_users[client_socket]->get_nickname(), channel->get_channelname()));

        } else if (args.size() == 2) {
            if (channel->get_topic().empty())
                _postman->sendReply(client_socket, RPL_NOTOPIC(_users[client_socket]->get_nickname(),
                                                               channel->get_channelname()));
            else
                _postman->sendReply(client_socket, RPL_TOPIC(_users[client_socket]->get_nickname(),
                                                             channel->get_channelname(),
                                                             channel->get_topic()));

        } else {
            if (channel->has_mode(protectedTopic) && !channel->is_operator(_users[client_socket]))
                _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(_users[client_socket]->get_nickname(), channel->get_channelname()));
            else {
                channel->set_topic(args[2]);
                _postman->sendReply(client_socket, RPL_TOPIC(_users[client_socket]->get_nickname(),
                                                             channel->get_channelname(),
                                                             channel->get_topic()));
            }
        }
    }
}
