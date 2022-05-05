#include <iostream>
#include "../server/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "./ircserv <PORT> <PASSWORD>\n";
		exit(EXIT_FAILURE);
	} else if (strtol(av[1], nullptr, 10) <= 1024
	|| strtol(av[1], nullptr, 10) > 65535) {
		std::cerr << "Invalid <PORT>\n";
		exit(EXIT_FAILURE);
	}

	Server	irc_server(av[1], av[2]);
	irc_server.start();
	irc_server.stop();
	return 0;
}
