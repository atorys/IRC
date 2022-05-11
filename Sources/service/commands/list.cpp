#include "../UsersService.hpp"

/*
 * Возвращает список каналов и их топиков из списка
 * Если вызывается без аргументов, показывает все каналы
 *
 * @Command: LIST
 * @Parameters: <channel>
 */
void UsersService::list(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));

    } else {
        _postman->sendReply(client_socket, RPL_LISTSTART);
        if (args.size() == 1) {
            for (std::set<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
                _postman->sendReply(client_socket, RPL_LIST((*it)->get_channelname(), (*it)->get_topic()));

        } else {
            std::vector<std::string> channelNames = ut::split(args[1], ",");
            Channel* channel;
            for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it) {
                if ((channel = findChannelByName(*it)) != nullptr)
                    _postman->sendReply(client_socket, RPL_LIST(channel->get_channelname(), channel->get_topic()));
            }
        }
        _postman->sendReply(client_socket, RPL_LISTEND);
    }
}
