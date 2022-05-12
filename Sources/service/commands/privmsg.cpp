#include "../UsersService.hpp"

void UsersService::privmsg(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->is_authenticated()){
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));
    } else if (args.size() != 3){
        if (args.size() == 2){
            if (args[1].find(':') != std::string::npos){
                _postman->sendReply(client_socket, ERR_NORECIPIENT(args[0]));
            } else {
                _postman->sendReply(client_socket, ERR_NOTEXTTOSEND);
            }
        } else {
            _postman->sendReply(client_socket, ERR_TOOMANYTARGETS(args[1])));
        }
    } else if (findUserByNickname(args[1]) == nullptr && findChannelByName(args[1]) == nullptr){
            if (findUserByNickname(args[1]) == nullptr)
                _postman->sendReply(client_socket, ERR_WASNOSUCHNICK(args[1]));
            else
                _postman->sendReply(client_socket, ERR_CANNOTSENDTOCHAN(args[1]));
    } else if (findChannelByName(args[1]) != nullptr) {
            Channel *channel = findChannelByName(args[1]);
            std::vector<User *> userList = channel->get_userlist();
            std::vector<User *> ::iterator start = userList.begin();
            std::vector<User *> ::iterator end = userList.end();
            while (start != end) {
                _postman->sendReply((*start)->get_socket(), RPL_PRIVMSG(_users[client_socket]->get_nickname() + "!" + _users[client_socket]->get_nickname() + "@1123",
                                                                        channel->get_channelname(),
                                                                        args[2]));
                start++;
            }
    } else {
        int replySocket = findUserByNickname(args[1])->get_socket();
        if (_users[replySocket]->is_away())
            _postman->sendReply(client_socket, RPL_AWAY(_users[client_socket]->get_nickname(),
                                                        _users[replySocket]->get_nickname(),
                                                        _users[replySocket]->get_awayMessage()));
        else
            _postman->sendReply(replySocket, RPL_PRIVMSG(_users[client_socket]->get_nickname(),
                                                         _users[replySocket]->get_nickname(),
                                                         args[2]));
    }
}