#include "../UsersService.hpp"

void UsersService::join(std::vector<std::string> args, int client_socket){
    if (args.size() != 2 && args.size() != 3){
        _postman->sendReply(client_socket, ERR_NEEDMOREPARAMS(args[0]));
    } else {
        if (args.size() == 2){
            std::vector<std::string> channelNames = ut::split(args[1], ",");
            std::set<Channel *>::iterator start = _channels.begin();
            std::set<Channel *>::iterator end = _channels.end();
            while (start != end) {
                for (int i = 0; i < channelNames.size(); i++){
                    if ((*start)->get_channelname() == channelNames[i]){
                        (*start)->addUser(_users[client_socket]);
                    }
                }
                start++;
            }
            for (int i = 0; i < channelNames.size(); i++){
                start = _channels.begin();
                while (start != end){
                    if ((*start)->get_channelname() == channelNames[i]){
                        break;
                    }
                    start++;
                }
                if (start == end){
                    _channels.insert(new Channel(channelNames[i], _users[client_socket]));
                }
            }
        }
    }
}