//
// Created by Achiote Tory on 5/2/22.
//

#pragma once
#include <iostream>
#include <map>


/*
 *  POSTMAN формирует буферы запросов юзеров и ответы на них
 */
class Postman {
    std::map<int, std::string >     _requests;
    std::map<int, std::string >     _replies;

    public:
        void sendRequest(int, const std::string&);
        void sendReply(int, const std::string&);

        bool hasRequest(int) const;
        bool hasReply(int) const;

        void clearRequests(int);
        void clearReplies(int);

        std::string   getRequest(int);
        std::string   getReply(int);

};

//__REPLIES____________________________________________________
#define RPL_WELCOME(nickname)                       (":server 001 " + (nickname) + " :Welcome to the IRCServ, " + (nickname))
#define RPL_MOTDSTART(nickname)                     (":server 375 " + (nickname) + " :- Message of the day -")
#define RPL_MOTD(nickname, message)                 (":server 372 " + (nickname) + " :- " + (message))
#define RPL_ENDOFMOTD(nickname)                     (":server 376 " + (nickname) + " :- End of /MOTD command")
#define RPL_AWAY(sender, recipient, away_message)   (":server 301 " + (sender) + " " + (recipient) + " :" + (away_message))
#define RPL_UNAWAY(nickname)                        (":server 305 " + (nickname) + " :You are no longer marked as being away")
#define RPL_NOWAWAY(nickname)                       (":server 306 " + (nickname) + " :You have been marked as being away")
#define RPL_ISON(nickname, nicknames)               (":server 303 " + (nickname) + " :" + (nicknames))
#define RPL_LISTSTART                               ":server 321 Channel :Topic"
#define RPL_LIST(channel, topic)                    (":server 322 " + (channel) + " :" + (topic))
#define RPL_LISTEND                                 ":server 323 :End of /LIST"
#define RPL_QUIT(nickname, message)                 (":server " + (nickname) + " quited :" + (message))
#define RPL_NOTOPIC(channel)                        (":server 331 " + (channel) + " :No topic is set")
#define RPL_TOPIC(channel, topic)                   (":server 332 " + (channel) + " :" + (topic) + '\n')
#define RPL_NAMREPLY(channel, nicknames)            (":server 353 " + (channel) + " :" + (nicknames))
#define RPL_ENDOFNAMES(channel)                     (":server 366 " + (channel) + " :End of /NAMES list")
#define RPL_PRIVMSG(sender, recipient, msg)         (":" + (sender) + " PRIVMSG " + (recipient) + " :"+ (msg))

//__ERRORS_____________________________________________________
#define ERR_NOSUCHNICK(nickname)                (":server 401 " + (nickname) + " :No such nick/channel")
#define ERR_NOSUCHCHANNEL(channel)              (":server 403 " + (channel) + " :No such channel")
#define ERR_NOSUCHSERVER(server)                (":server 402 " + (server) + " :No such server")
#define ERR_NOORIGIN                            ":server 409 :No origin specified"
#define ERR_CANNOTSENDTOCHAN(channel)           (":server 404 " + (channel) + " :Cannot send to channel")
#define ERR_WASNOSUCHNICK(channel)              (":server 406 " + (channel) + " :There was no such nickname")
#define ERR_TOOMANYTARGETS(nickname)            (":server 407 " + (nickname) + " :Duplicate recipients. No message delivered)"
#define ERR_UNKNOWNCOMMAND(command)             (":server 421 " + (command) + " :Unknown command")
#define ERR_CHANOPRIVSNEEDED(channel)           (":server 482 " + (channel) + ":You're not channel operator")
//NICK
#define ERR_NONICKNAMEGIVEN                     ":server 431 :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickname)          (":server 432 " + (nickname) + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(nickname)             (":server 433 " + (nickname) + " :Nickname is already in use")
#define ERR_NICKCOLLISION(nickname)             (":server 436 " + (nickname) + " :Nickname collision KILL")

//USER
#define ERR_NOLOGIN(username)                   (":server 444 " + (username) + " :User not logged in")

//CHANNEL
#define ERR_USERNOTINCHANNEL(nickname, channel) (":server 441 " + (nickname) + " " + (channel) + " :They aren't on that channel")
#define ERR_NOTONCHANNEL(channel)               (":server 442 " + (channel) + " :You're not on that channel")
#define ERR_USERONCHANNEL(username, channel)    (":server 443 " + (username) + " " + (channel) + " :is already on channel")

//PASS
#define ERR_NOTREGISTERED                       ":server 451 :You have not registered"
#define ERR_NEEDMOREPARAMS(command)             (std::string(":server 461 ") + (command) + " :Not enough parameters")
#define ERR_ALREADYREGISTRED                    ":server 462 :You may not reregister"
#define ERR_PASSWDMISMATCH                      ":server 464 :Password incorrect"

//PRIVMSG
#define ERR_NORECIPIENT(command)                (":server 411 :No recipient given " + (command))
#define ERR_NOTEXTTOSEND                        ":server 421 :No text to send"
