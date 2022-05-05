//
// Created by Achiote Tory on 5/2/22.
//

#pragma once
#include <iostream>


/*
 *  POSTMAN отправляет ответы на запросы юзеров
 */
class Postman {
    public:
        static void sendReply(int, std::string);
};

//__REPLIES____________________________________________________
#define RPL_MOTDSTART                           "375 :- <server> Message of the day -"
#define RPL_MOTD(message)                       std::string("372 :- ") + (message)
#define RPL_ENDOFMOTD                           "376 :End of /MOTD command"


//__ERRORS_____________________________________________________
#define ERR_NOSUCHNICK(nickname)                ("401 " + (nickname) + " :No such nick/channel")
#define ERR_NOSUCHCHANNEL(channel)              ("403 " + (channel) + " :No such channel")
#define ERR_CANNOTSENDTOCHAN(channel)           ("404 " + (channel) + " :Cannot send to channel")
#define ERR_WASNOSUCHNICK(channel)              ("406 " + (channel) + " :There was no such nickname")
#define ERR_TOOMANYTARGETS(nickname)            ("407 " + (nickname) + " :Duplicate recipients. No message delivered)"
#define ERR_UNKNOWNCOMMAND(command)             ("421 " + (command) + " :Unknown command")

//NICK
#define ERR_NONICKNAMEGIVEN                     "431 :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickname)          ("432 " + (nickname) + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(nickname)             ("433 " + (nickname) + " :Nickname is already in use")
#define ERR_NICKCOLLISION(nickname)             ("436 " + (nickname) + " :Nickname collision KILL")

//USER
#define ERR_NOLOGIN(username)                   ("444 " + (username) + " :User not logged in")

//CHANNEL
#define ERR_USERNOTINCHANNEL(nickname, channel) ("441 " + (nickname) + " " + (channel) + " :They aren't on that channel")
#define ERR_NOTONCHANNEL(channel)               ("442 " + (channel) + " :You're not on that channel")
#define ERR_USERONCHANNEL(username, channel)    ("443 " + (username) + " " + (channel) + " :is already on channel")

//PASS
#define ERR_NOTREGISTERED                       "451 :You have not registered"
#define ERR_NEEDMOREPARAMS(command)             (std::string("461 ") + (command) + " :Not enough parameters")
#define ERR_ALREADYREGISTRED                    "462 :You may not reregister"
#define ERR_PASSWDMISMATCH                      "464 :Password incorrect"