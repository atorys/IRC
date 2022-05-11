#include "../UsersService.hpp"

/*
 * Используется для изменения или просмотра топика канала.
 *
 * @Command: TOPIC
 * @Parameters: <channel> {<topic>}
 */
void UsersService::topic(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else if (args.size() < 2 || args.size() > 3) {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS("TOPIC"));

    } else {
        Channel *channel;

        if ((channel = findChannelByName(args[1])) == nullptr) {
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(args[1]));

        } else if (channel->get_user_by_username(_users[client_socket]->get_username()) == nullptr) { // todo: USERNAME ? NICKNAME
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(channel->get_channelname()));

        } else if (args.size() == 2) {
            if (channel->get_topic().empty())
                _postman->sendReply(client_socket, RPL_NOTOPIC(channel->get_channelname()));
            else
                _postman->sendReply(client_socket, RPL_TOPIC(channel->get_channelname(), channel->get_topic()));

        } else {
            channel->set_topic(args[2]);
        }
    }
}
