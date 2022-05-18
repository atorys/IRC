#include "../UsersService.hpp"

/*
 * Возвращает список юзеров канала
 * Если вызывается без аргументов, показывает все каналы
 *
 * @Command: NAMES
 * @Parameters: <channel> {...}
 */
void UsersService::names(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else {
        std::vector<User *> userList;

        if (args.size() == 1) {
            for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
                userList = (*it)->get_userlist();
                for (std::vector<User *>::iterator i = userList.begin(); i != userList.end(); ++i) {
                    _postman->sendReply(client_socket, RPL_NAMREPLY(_users[client_socket]->get_nickname(), (*it)->get_channelname(), (*i)->get_fullname()));
                }
                _postman->sendReply(client_socket, RPL_ENDOFNAMES(_users[client_socket]->get_nickname(), (*it)->get_channelname()));
            }
        } else {
            std::vector<std::string> channelNames = ut::split(args[1], ",");
            Channel* channel;
            for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it) {
                if ((channel = findChannelByName(*it)) != nullptr) {
                    userList = channel->get_userlist();
                    for (std::vector<User *>::iterator i = userList.begin(); i != userList.end(); ++i) {
                        _postman->sendReply(client_socket, RPL_NAMREPLY(_users[client_socket]->get_nickname(), channel->get_channelname(), (*i)->get_fullname()));
                    }
                    _postman->sendReply(client_socket, RPL_ENDOFNAMES(_users[client_socket]->get_nickname(), channel->get_channelname()));
                } else {
                    _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), *it));
                }
            }
        }
    }
}
