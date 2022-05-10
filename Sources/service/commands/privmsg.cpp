#include "../UsersService.hpp"

void UsersService::privmsg(std::vector<std::string> args, int client_socket){
    if (!_users[client_socket]->get_registred()){
        _postman->sendReply(client_socket, ERR_NOLOGIN(_users[client_socket]->get_username()));
    } else if (args.size() != 3){
        if (args.size() == 2){
            if (args[1].find(":") != std::string::npos){
                _postman->sendReply(client_socket, ERR_NORECIPIENT(args[0]));
            } else {
                _postman->sendReply(client_socket, ERR_NOTEXTTOSEND);
            }
        } else {
            _postman->sendReply(client_socket, ERR_TOOMANYTARGETS(args[1])));
        }
    } else if (findUserByNickname(args[1]) == nullptr){
        _postman->sendReply(client_socket, ERR_WASNOSUCHNICK(args[1]));
    } else {
        int replySocket = findUserByNickname(args[1])->get_socket();
        _postman->sendReply(replySocket, _users[client_socket]->get_username() + args[2]);
    }
}