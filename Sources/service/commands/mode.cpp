#include "../UsersService.hpp"

std::string     changeChannelMode(User *oper, Channel *channel, const std::string& modes, const std::string& args) {
    if (channel->is_operator(oper)) {
        if (modes.find('+') != std::string::npos){
            if (modes.find('l') != std::string::npos) {
                if (args.empty() || atoi(args.c_str()) <= 0)
                    return ERR_NEEDMOREPARAMS(oper->get_nickname(), "MODE");
                else {
                    channel->set_mode(limited);
                    channel->set_limit(atoi(args.c_str()));
                    channel->sendAll(RPL_MODE(oper->get_fullname(), channel->get_channelname(), "+l :" + args), nullptr);
                }
            }
            if (modes.find('i') != std::string::npos)
                channel->set_mode(invite_only);
            if (modes.find('t') != std::string::npos)
                channel->set_mode(topic);
            if (modes.find('o') != std::string::npos) {
                User *user = nullptr;
                if (args.empty()) {
                    return ERR_NEEDMOREPARAMS(oper->get_nickname(), "MODE");
                } else if ((user = channel->get_user_by_nickname(args)) == nullptr) {
                    return ERR_USERNOTINCHANNEL(oper->get_nickname(), args, channel->get_channelname());
                } else {
                    channel->addOper(user);
                    channel->sendAll(RPL_MODE(oper->get_fullname(), channel->get_channelname(), "+o :" + user->get_nickname()), nullptr);
                }

            }

        } else if (modes.find('-') != std::string::npos){
            if (modes.find('l') != std::string::npos) {
                channel->unset_mode(limited);
                channel->sendAll(RPL_MODE(oper->get_fullname(), channel->get_channelname(), "-l"), nullptr);
            }
            if (modes.find('i') != std::string::npos)
                channel->unset_mode(invite_only);
            if (modes.find('t') != std::string::npos)
                channel->unset_mode(topic);
            if (modes.find('o') != std::string::npos) {
                User *user = nullptr;
                if (args.empty()) {
                    return ERR_NEEDMOREPARAMS(oper->get_nickname(), "MODE");
                } else if ((user = channel->get_user_by_nickname(args)) == nullptr) {
                    ERR_USERNOTINCHANNEL(oper->get_nickname(), args, channel->get_channelname());
                } else {
                    channel->removeOper(user);
                    channel->sendAll(RPL_MODE(oper->get_fullname(), channel->get_channelname(), "-o :" + user->get_nickname()), nullptr);
                }

            }
        } else
            return ERR_UMODEUNKNOWNFLAG(oper->get_fullname());

        return RPL_MODE(oper->get_fullname(), channel->get_channelname(), modes);

    } else {
        return ERR_CHANOPRIVSNEEDED(oper->get_fullname(), channel->get_channelname());
    }
}

std::string     changeUserMode(User *oper, User *user, const std::string& modes) {
    if (oper->has_mode(UserOper) || user == oper) {
        if (modes.find('+') != std::string::npos) {
            if (modes.find('o') != std::string::npos && oper->has_mode(UserOper))
                user->set_mode(UserOper);
            if (modes.find('w') != std::string::npos)
                user->set_mode(wallopsOff);
            if (modes.find('i') != std::string::npos)
                user->set_mode(invisibility);
            if (modes.find('s') != std::string::npos)
                user->set_mode(silence);
        } else if (modes.find('-') != std::string::npos) {
            if (modes.find('o') != std::string::npos)
                user->unset_mode(UserOper);
            if (modes.find('w') != std::string::npos)
                user->unset_mode(wallopsOff);
            if (modes.find('i') != std::string::npos)
                user->unset_mode(invisibility);
            if (modes.find('s') != std::string::npos)
                user->unset_mode(silence);
        } else {
            return ERR_UMODEUNKNOWNFLAG(oper->get_fullname());
        }
        return RPL_MODE(oper->get_fullname(), user->get_nickname(), modes);

    } else {
        return ERR_USERSDONTMATCH(oper->get_nickname());
    }
}

/*
 * Используется для изменения или просмотра топика канала.
 *
 * @Command: MODE
 * @Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]}
 *              <nickname> {[+|-]|i|w|s|o}
 *              modes for <channel> i | o | l | t;
 *              modes for <user>    i | s | o | w
 *              <channel> : i - флаг канала invite-only;
 *                          o - брать/давать привилегии операторов канала;
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

    } else if (args.size() > 1 && args.size() < 5) {
        Channel *channel = nullptr;
        User    *user = nullptr;

        if ((channel = findChannelByName(args[1])) == nullptr && (user = findUserByNickname(args[1])) == nullptr) {
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[1]));

        } else if (channel) {
            if (!channel->is_in_channel(_users[client_socket]))
                _postman->sendReply(client_socket, ERR_NOTONCHANNEL(_users[client_socket]->get_nickname(), channel->get_channelname()));
            else if (args.size() > 2)
                _postman->sendReply(client_socket, changeChannelMode(_users[client_socket], channel, args[2], args.size() == 4 ? args[3] : ""));
            else
                _postman->sendReply(client_socket, RPL_CHANNELMODEIS(_users[client_socket]->get_nickname(), channel->get_channelname(), channel->show_mode()));

        } else if (user) {
            if (args.size() == 3)
                _postman->sendReply(client_socket, changeUserMode(_users.at(client_socket), user, args[2]));
            else
                _postman->sendReply(client_socket, RPL_UMODEIS(_users[client_socket]->get_nickname(), user->get_nickname(), user->show_mode()));

        } else {
            _postman->sendReply(client_socket, ERR_NOSUCHNICK(_users[client_socket]->get_nickname(), args[1]));
        }

    } else {
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(_users[client_socket]->get_nickname(), "MODE"));
    }
}