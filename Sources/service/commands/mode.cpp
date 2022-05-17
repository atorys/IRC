#include "../UsersService.hpp"

void    changeChannelMode() {

}

void    UsersService::changeUserMode(std::vector<std::string> args, int client_socket) {
    if (_users[client_socket]->has_mode(UserOper)){
        User    *user = nullptr;
        user = findUserByNickname(args[1]);
        if (args[2].find('+') != std::string::npos){
            if (args[2].find('o') != std::string::npos)
                user->set_mode(UserOper);
            if (args[2].find('w') != std::string::npos)
                user->set_mode(wallopsOff);
            if (args[2].find('i') != std::string::npos)
                user->set_mode(invisibility);
            if (args[2].find('s') != std::string::npos)
                user->set_mode(silence);
        } else if (args[2].find('-') != std::string::npos){
            if (args[2].find('o') != std::string::npos)
                user->unset_mode(UserOper);
            if (args[2].find('w') != std::string::npos)
                user->unset_mode(wallopsOff);
            if (args[2].find('i') != std::string::npos)
                user->unset_mode(invisibility);
            if (args[2].find('s') != std::string::npos)
                user->unset_mode(silence);
        }
    }
}

/*
 * Используется для изменения или просмотра топика канала.
 *
 * @Command: MODE
 * @Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]}
 *              <nickname> {[+|-]|i|w|s|o}
 *              modes for <channel> i | o | p | l | t;
 *              modes for <user>    i | s | o | w
 *              <channel> : i - флаг канала invite-only;
 *                          o - брать/давать привилегии операторов канала;
 *                          p - флаг приватности канала;
 *                          l - установка ограничения на количество пользователей;
 *                          t - при установке этого флага, менять топик могут только операторы;
 *              <user> :    i - делает пользователя невидимым;
 *                          s – пользователь (не)получает NOTICE сообщения;
 *                          o – флаг IRC-оператора;
 *                          w – пользователь (не)получает WALLOPS сообщения;
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
            changeUserMode(args, client_socket);
            _postman->sendReply(client_socket, RPL_UMODEIS(_users[client_socket]->get_nickname(), user->get_nickname()));

        } else {
            _postman->sendReply(client_socket, ERR_NOSUCHNICK(_users[client_socket]->get_nickname(), args[1]));
        }

    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "MODE"));
    }
}