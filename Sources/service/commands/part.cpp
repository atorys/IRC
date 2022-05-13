#include "../UsersService.hpp"

void UsersService::part(std::vector<std::string> args, int client_socket){
    if (args.size() != 2)
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(args[0]));
    else{
        std::vector<std::string> splitedStr = ut::split(args[1], ",");
        for (std::vector<std::string>::iterator start = splitedStr.begin(); start != splitedStr.end(); start++){
            if (findChannelByName(*start) == nullptr)
                _postman->sendReply(client_socket, ERR_NOSUCHCHANNEL(*start));
            else if (!findChannelByName(*start)->is_in_channel(_users[client_socket]))
                _postman->sendReply(client_socket, ERR_NOTONCHANNEL(*start));
            else
                findChannelByName(*start)->removeUserFromChannel(_users[client_socket], "");
        }
    }
}