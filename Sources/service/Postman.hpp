//
// Created by Achiote Tory on 5/2/22.
//

#pragma once
#include <iostream>
#include <map>
#define GREY_COL "\033[37m"
#define GREEN_COL "\033[32m"
#define NO_COL "\033[0m"


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
#define RPL_WELCOME(nickname)                           (":ircserv 001 " + (nickname) + " :Welcome to the IRCServ, " + (nickname))
#define RPL_MOTDSTART(nickname)                         (":ircserv 375 " + (nickname) + " :- Message of the day -")
#define RPL_MOTD(nickname, message)                     (":ircserv 372 " + (nickname) + " :- " + (message))
#define RPL_ENDOFMOTD(nickname)                         (":ircserv 376 " + (nickname) + " :- End of /MOTD command")
#define RPL_AWAY(sender, recipient, away_message)       (":ircserv 301 " + (sender) + " " + (recipient) + " :" + (away_message))
#define RPL_UNAWAY(nickname)                            (":ircserv 305 " + (nickname) + " :You are no longer marked as being away")
#define RPL_NOWAWAY(nickname)                           (":ircserv 306 " + (nickname) + " :You have been marked as being away")
#define RPL_ISON(nickname, nicknames)                   (":ircserv 303 " + (nickname) + " :" + (nicknames))
#define RPL_NOTOPIC(nickname, channel)                  (":ircserv 331 " + (nickname) + ' ' + (channel) + " :No topic is set")
#define RPL_TOPIC(nickname, channel, topic)             (":ircserv 332 " + (nickname) + ' ' + (channel) + " :" + (topic))
#define RPL_NAMREPLY(nickname, channel, nicknames)      (":ircserv 353 " + (nickname) + ' ' + (channel) + " :" + (nicknames))
#define RPL_ENDOFNAMES(nickname, channel)               (":ircserv 366 " + (nickname) + ' ' + (channel) + " :End of /NAMES list")
#define RPL_WHOREPLY(ownnickname, channel, username, \
                    host, nickname, away_message,    \
                    serverstatus, oper, realname)       (":ircserv 352 " + (ownnickname) + ' ' + (channel) + ' ' + (username) + ' ' \
                                                        + (host) + " ircserv " + (nickname) + ' ' + (away_message) + ' ' + (serverstatus) + ' ' \
                                                        + (oper) + " :0 " + (realname))
#define RPL_ENDOFWHO(nickname, name)                    (":ircserv 315 " + (nickname) + ' ' + (name) + " :End of /WHO list")

#define RPL_CHANNELMODEIS(nickname, channel, mode)      (":ircserv 324 " + (nickname) + ' ' + (channel) + " :" + (mode))
#define RPL_UMODEIS(nickname, user)                     " 221 <user mode string>"

#define RPL_QUIT(nickname, message)                     (":ircserv " + (nickname) + " quited :" + (message))
#define RPL_PRIVMSG(sender, recipient, msg)             (":" + (sender) + " PRIVMSG " + (recipient) + " :"+ (msg))
#define RPL_JOIN(nickname, channel)                     (":" + (nickname) + " JOIN " + (channel))
#define RPL_PART(nickname, channel, reason)             (":" + (nickname) + " PART " + (channel) + " :" + (reason))
#define RPL_KICK(nickname, channel, user, reason)       (":" + (nickname) + " KICK " + (channel) + ' ' + (user) + " :" + (reason))

//__ERRORS_____________________________________________________
#define ERR_NOSUCHNICK(nickname, nick)                  (":ircserv 401 " + (nickname) + ' ' + (nick) + " :No such nick/channel")
#define ERR_NOSUCHCHANNEL(nickname, channel)            (":ircserv 403 " + (nickname) + ' ' + (channel) + " :No such channel")
#define ERR_NOORIGIN(nickname)                          (":ircserv 409 " + (nickname) + " :No origin specified")
#define ERR_CANNOTSENDTOCHAN(channel)                   (":ircserv 404 " + (channel) + " :Cannot send to channel")
#define ERR_WASNOSUCHNICK(channel)                      (":ircserv 406 " + (channel) + " :There was no such nickname")
#define ERR_TOOMANYTARGETS(nickname, target)            (":ircserv 407 " + (nickname) + ' ' + (target) + " :Duplicate recipients. No message delivered)"
#define ERR_UNKNOWNCOMMAND(nickname, command)           (":ircserv 421 " + (nickname) + ' ' + (command) + " :Unknown command")
#define ERR_CHANOPRIVSNEEDED(nickname, channel)         (":ircserv 482 " + (nickname) + ' ' + (channel) + ":You're not channel operator")
//NICK
#define ERR_NONICKNAMEGIVEN(nickname)                   (":ircserv 431 " + (nickname) + " :No nickname given")
#define ERR_ERRONEUSNICKNAME(nickname, nick)            (":ircserv 432 " + (nickname) + ' ' + (nick) + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(oldnickname, nickname)        (":ircserv 433 " + (oldnickname) + ' ' + (nickname) + " :Nickname is already in use")

//CHANNEL
#define ERR_USERNOTINCHANNEL(nickname, user, channel)   (":ircserv 441 " + (nickname) + ' '  + (user) + ' ' + (channel) + " :They aren't on that channel")
#define ERR_NOTONCHANNEL(nickname, channel)             (":ircserv 442 " + (nickname) + ' ' + (channel) + " :You're not on that channel")
#define ERR_USERONCHANNEL(nickname, user, channel)      (":ircserv 443 " + (nickname) + ' ' + (user) + ' ' + (channel) + " :is already on channel")

//PASS
#define ERR_NOTREGISTERED(nickname)                     (":ircserv 451 " + (nickname) + " :You have not registered")
#define ERR_NEEDMOREPARAMS(nickname, command)           (":ircserv 461 " + (nickname) + ' ' + (command) + " :Not enough parameters")
#define ERR_ALREADYREGISTRED(nickname)                  (":ircserv 462 " + (nickname) + " :You may not reregister")
#define ERR_PASSWDMISMATCH(nickname)                    (":ircserv 464 " + (nickname) + " :Password incorrect")

//PRIVMSG
#define ERR_NORECIPIENT(nickname, command)      (":ircserv 411 " + (nickname) + " :No recipient given " + (command))
#define ERR_NOTEXTTOSEND(nickname)              (":ircserv 421 " + (nickname) + " :No text to send")
