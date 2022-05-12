#include "../UsersService.hpp"

void UsersService::kick(std::vector<std::string> args, int client_socket) {
    if (args.size() != 4 || args.size() != 3){
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(args[0]));
    } else if (args.size() == 3){
        if (findChannelByName(args[1]) == nullptr)
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(args[1]));
        else if (findChannelByName(args[1])->is_in_channel(findUserByNickname(args[2])))
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(args[1]));
        else if (findChannelByName(args[1])->get_userlist()[0]->get_socket() != client_socket)
            _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(args[1]));
        else
            findChannelByName(args[1])->removeUser(findUserByNickname(args[2]), "");
    } else {
        if (findChannelByName(args[1]) == nullptr)
            _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(args[1]));
        else if (findChannelByName(args[1])->is_in_channel(findUserByNickname(args[2])))
            _postman->sendReply(client_socket, ERR_NOTONCHANNEL(args[1]));
        else if (findChannelByName(args[1])->get_userlist()[0]->get_socket() != client_socket)
            _postman->sendReply(client_socket, ERR_CHANOPRIVSNEEDED(args[1]));
        else
            findChannelByName(args[1])->removeUser(findUserByNickname(args[2]), args[3]);
    }
}