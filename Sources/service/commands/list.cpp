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
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else {
        _postman->sendReply(client_socket, RPL_LISTSTART(_users[client_socket]->get_nickname()));
        if (args.size() == 1) {
            for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
                _postman->sendReply(client_socket, RPL_LIST(_users[client_socket]->get_nickname(), (*it)->get_channelname(), (*it)->get_topic()));

        } else {
            std::vector<std::string> channelNames = ut::split(args[1], ",");
            Channel* channel;
            for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it) {
                if ((channel = findChannelByName(*it)) != nullptr)
                    _postman->sendReply(client_socket, RPL_LIST(_users[client_socket]->get_nickname(), channel->get_channelname(), channel->get_topic()));
            }
        }
        _postman->sendReply(client_socket, RPL_LISTEND(_users[client_socket]->get_nickname()));
    }
}
