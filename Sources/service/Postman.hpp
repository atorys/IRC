//
// Created by Achiote Tory on 5/2/22.
//

#pragma once
#include <map>
#include "../models/User.hpp"


/*
 *  POSTMAN отправляет ответы на запросы юзеров
 *  с помощью функции sendReply(userFd, replyMessage, [OPTIONAL] arg1, [OPTIONAL] arg2);
 *  подставляет в запрос вместо <?> опциональные аргументы arg1 и arg2
 */
class Postman {
    public:
        static void sendReply(int, std::string, const std::string& = "", const std::string& = "");
};

#define INSERTER    "<?>"

//__REPLIES____________________________________________________
#define RPL_MOTDSTART           "375 :- <server> Message of the day - "
#define RPL_MOTD                "372 :- <?>"  // <message of the day>
#define RPL_ENDOFMOTD           "376 :End of /MOTD command"


//__ERRORS_____________________________________________________
#define ERR_NOSUCHNICK          "401 <?> :No such nick/channel"                         // <nickname>
#define ERR_NOSUCHCHANNEL       "403 <?> :No such channel"                              // <channel name>
#define ERR_CANNOTSENDTOCHAN    "404 <?> :Cannot send to channel"                       // <channel name>
#define ERR_WASNOSUCHNICK       "406 <?> :There was no such nickname"                   // <nickname>
#define ERR_TOOMANYTARGETS      "407 <?> :Duplicate recipients. No message delivered"   // <target>
#define ERR_UNKNOWNCOMMAND      "421 <?> :Unknown command"                              // <command>

//NICK
#define ERR_NONICKNAMEGIVEN     "431 :No nickname given"
#define ERR_ERRONEUSNICKNAME    "432 <?> :Erroneus nickname"            // <nick>
#define ERR_NICKNAMEINUSE       "433 <?> :Nickname is already in use"   // <nick>
#define ERR_NICKCOLLISION       "436 <?> :Nickname collision KILL"      // <nick>

//USER
#define ERR_NOLOGIN             "444 <?> :User not logged in"   // <user>

//CHANNEL
#define ERR_USERNOTINCHANNEL    "441 <?> <?> :They aren't on that channel"  // <nick> <channel>
#define ERR_NOTONCHANNEL        "442 <?> :You're not on that channel"       // <channel>
#define ERR_USERONCHANNEL       "443 <?> <?> :is already on channel"        // <user> <channel>

//PASS
#define ERR_NOTREGISTERED       "451 :You have not registered"
#define ERR_NEEDMOREPARAMS      "461 <?> :Not enough parameters"    // <command>
#define ERR_ALREADYREGISTRED    "462 :You may not reregister"
#define ERR_PASSWDMISMATCH      "464 :Password incorrect"