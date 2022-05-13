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
#define RPL_WELCOME(nickname, username, host)       (":ircserv 001 " + (nickname) + " :Welcome to the IRCServ, " + (nickname) + '!' + (username) + '@' + (host))
#define RPL_MOTDSTART(nickname)                     (":ircserv 375 " + (nickname) + " :- Message of the day -")
#define RPL_MOTD(nickname, message)                 (":ircserv 372 " + (nickname) + " :- " + (message))
#define RPL_ENDOFMOTD(nickname)                     (":ircserv 376 " + (nickname) + " :- End of /MOTD command")
#define RPL_AWAY(sender, recipient, away_message)   (":ircserv 301 " + (sender) + " " + (recipient) + " :" + (away_message))
#define RPL_UNAWAY(nickname)                        (":ircserv 305 " + (nickname) + " :You are no longer marked as being away")
#define RPL_NOWAWAY(nickname)                       (":ircserv 306 " + (nickname) + " :You have been marked as being away")
#define RPL_ISON(nickname, nicknames)               (":ircserv 303 " + (nickname) + " :" + (nicknames))
#define RPL_LISTSTART(nickname)                     (":ircserv 321 " + (nickname) + " Channel :Users  Name")
#define RPL_LIST(nickname, channel, topic)          (":ircserv 322 " + (nickname) + ' ' + (channel) + " :" + (topic))
#define RPL_LISTEND(nickname)                       (":ircserv 323 " + (nickname) + " :End of /LIST")
#define RPL_QUIT(nickname, message)                 (":ircserv " + (nickname) + " quited :" + (message))
#define RPL_NOTOPIC(nickname, channel)              (":ircserv 331 " + (nickname) + ' ' + (channel) + " :No topic is set")
#define RPL_TOPIC(nickname, channel, topic)         (":ircserv 332 " + (nickname) + ' ' + (channel) + " :" + (topic))
#define RPL_NAMREPLY(nickname, channel, nicknames)  (":ircserv 353 " + (nickname) + " = " + (channel) + " :" + (nicknames))
#define RPL_ENDOFNAMES(nickname, channel)           (":ircserv 366 " + (nickname) + ' ' + (channel) + " :End of /NAMES list")

#define RPL_PRIVMSG(sender, recipient, msg)         (":" + (sender) + " PRIVMSG " + (recipient) + " :"+ (msg))
#define RPL_JOIN(nickname, channel)                 (":" + (nickname) + " JOIN " + (channel))

//__ERRORS_____________________________________________________
#define ERR_NOSUCHNICK(nickname)                (":ircserv 401 " + (nickname) + " :No such nick/channel")
#define ERR_NOSUCHCHANNEL(channel)              (":ircserv 403 " + (channel) + " :No such channel")
#define ERR_NOSUCHSERVER(server)                (":ircserv 402 " + (server) + " :No such server")
#define ERR_NOORIGIN                            ":ircserv 409 :No origin specified"
#define ERR_CANNOTSENDTOCHAN(channel)           (":ircserv 404 " + (channel) + " :Cannot send to channel")
#define ERR_WASNOSUCHNICK(channel)              (":ircserv 406 " + (channel) + " :There was no such nickname")
#define ERR_TOOMANYTARGETS(nickname)            (":ircserv 407 " + (nickname) + " :Duplicate recipients. No message delivered)"
#define ERR_UNKNOWNCOMMAND(command)             (":ircserv 421 " + (command) + " :Unknown command")
#define ERR_CHANOPRIVSNEEDED(channel)           (":ircserv 482 " + (channel) + ":You're not channel operator")
//NICK
#define ERR_NONICKNAMEGIVEN                     ":ircserv 431 :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickname)          (":ircserv 432 " + (nickname) + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(oldnickname, nickname)    (":ircserv 433 " + (oldnickname) + ' ' + (nickname) + " :Nickname is already in use")
#define ERR_NICKCOLLISION(nickname)             (":ircserv 436 " + (nickname) + " :Nickname collision KILL")

//USER
#define ERR_NOLOGIN(username)                   (":ircserv 444 " + (username) + " :User not logged in")

//CHANNEL
#define ERR_USERNOTINCHANNEL(nickname, channel) (":ircserv 441 " + (nickname) + ' ' + (channel) + " :They aren't on that channel")
#define ERR_NOTONCHANNEL(channel)               (":ircserv 442 " + (channel) + " :You're not on that channel")
#define ERR_USERONCHANNEL(username, channel)    (":ircserv 443 " + (username) + ' ' + (channel) + " :is already on channel")

//PASS
#define ERR_NOTREGISTERED                       ":ircserv 451 :You have not registered"
#define ERR_NEEDMOREPARAMS(nickname, command)   (":ircserv 461 " + (nickname) + ' ' + (command) + " :Not enough parameters")
#define ERR_ALREADYREGISTRED                    ":ircserv 462 :You may not reregister"
#define ERR_PASSWDMISMATCH                      ":ircserv 464 :Password incorrect"

//PRIVMSG
#define ERR_NORECIPIENT(command)                (":ircserv 411 :No recipient given " + (command))
#define ERR_NOTEXTTOSEND                        ":ircserv 421 :No text to send"
