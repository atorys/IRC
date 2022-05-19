# IRC server

**An Internet Relay Chat server in C++ 98 based on rfc1459 standard.  
Сервер на базе IRC протокола для обмена сообщениями.**

<img src="https://media.giphy.com/media/xT1XGwtY71kMjBkORi/giphy.gif" width="300"  alt="channel"/>

### Supported clients :
- Netcat 
  ` nc localhost [port]`
- LimeChat
- Adium

## How to run
Use **make** rule to compile the program. Run it with port and password
``` 
make && ./ircserv [port] [password]
``` 


Bot running
```
cd Sources/bot && make
```
```
./bot 0.0.0.0 [port] [password]
```

## Useful links 
- [wiki by levensta](https://github.com/levensta/IRC-Server)
- [Example IRC Communications](http://chi.cs.uchicago.edu/chirc/irc_examples.html)
- [Select / poll / epoll: практическая разница](https://habr.com/ru/company/infopulse/blog/415259/)
- [Сеть: Системные вызовы](https://masandilov.ru/network/guide_to_network_programming5#5.9)
- [ERROR REPLIES](https://gist.github.com/proxypoke/2264878)
