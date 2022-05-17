#include "../UsersService.hpp"

void    changeChannelMode() {

}

void    changeUserMode() {

}

/*
 * Используется для изменения или просмотра топика канала.
 *
 * @Command: MODE
 * @Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]}
 *              <nickname> {[+|-]|i|w|s|o}
 */
void UsersService::mode(std::vector<std::string> args, int client_socket) {
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() > 1 && args.size() < 4) {
        Channel *channel = nullptr;
        User    *user = nullptr;

        if ((channel = findChannelByName(args[1])) == nullptr && (user = findUserByNickname(args[1])) == nullptr) {
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[1]));

        } else if (channel) {
            changeChannelMode();
            _postman->sendReply(client_socket, RPL_CHANNELMODEIS(_users[client_socket]->get_nickname(), channel->get_channelname(), channel->show_mode()));

        } else if (user) {
            changeUserMode();
            _postman->sendReply(client_socket, RPL_UMODEIS(_users[client_socket]->get_nickname(), user->get_nickname()));

        } else {
            _postman->sendReply(client_socket, ERR_NOSUCHNICK(_users[client_socket]->get_nickname(), args[1]));
        }

    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "MODE"));
    }
}