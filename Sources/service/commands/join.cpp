#include "../UsersService.hpp"

void UsersService::join(std::vector<std::string> args, int client_socket){
    if (args.size() != 2){
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(args[0]));
    } else {
        if (args.size() == 2){
            std::vector<std::string> channelNames = ut::split(args[1], ",");
            std::set<Channel *>::iterator start;
            for (int i = 0; i < channelNames.size(); i++){
                start = _channels.begin();
                while (start != _channels.end()) {
                    if ((*start)->get_channelname() == channelNames[i]){
                        break;
                    }
                    start++;
                }
                std::vector<std::string> arg;
                arg.push_back("NAMES");
                if (start == _channels.end()) {
                    _channels.insert(new Channel(channelNames[i], _users[client_socket], _postman));
                    arg.push_back(channelNames[i]);
                } else {
                    (*start)->addUser(_users[client_socket]);
                    arg.push_back((*start)->get_channelname());
                }
                names(args, client_socket);
            }
        }
    }
}