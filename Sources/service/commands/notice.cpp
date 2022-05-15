#include "../UsersService.hpp"

/*
 * Отправляет личное сообщение, игнорируя автоматический ответ
 *
 * @Command: NOTICE
 * @Parameters: <nickname> :<message>
 */
void UsersService::notice(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()) {
        _postman->sendReply(client_socket, ERR_NOTREGISTERED(_users[client_socket]->get_nickname().empty() ?
                                                             "*" : _users[client_socket]->get_nickname()));

    } else if (args.size() != 3){
        if (args.size() == 2){
            if (args[1].find(':') != std::string::npos){
                _postman->sendReply(client_socket, ERR_NORECIPIENT(_users[client_socket]->get_nickname(), args[0]));
            } else {
                _postman->sendReply(client_socket, ERR_NOTEXTTOSEND(_users[client_socket]->get_nickname()));
            }
        } else {
            _postman->sendReply(client_socket, ERR_TOOMANYTARGETS(_users[client_socket]->get_nickname(), args[1])));
        }

    } else if (findUserByNickname(args[1]) == nullptr && findChannelByName(args[1]) == nullptr){
        if (findUserByNickname(args[1]) == nullptr)
            _postman->sendReply(client_socket, ERR_NOSUCHNICK(_users[client_socket]->get_nickname(), args[1]));
        else
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(_users[client_socket]->get_nickname(), args[1]));

    } else if (findChannelByName(args[1]) != nullptr) {
        Channel *channel = findChannelByName(args[1]);
        channel->sendAll(RPL_PRIVMSG(_users[client_socket]->get_nickname(), channel->get_channelname(), args[2]), _users[client_socket]);

    } else {
        int replySocket = findUserByNickname(args[1])->get_socket();
        _postman->sendReply(replySocket, RPL_PRIVMSG(_users[client_socket]->get_nickname(),
                                                     _users[replySocket]->get_nickname(),
                                                     args[2]));
    }
}