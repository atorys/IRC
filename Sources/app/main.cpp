#include <iostream>
#include "../server/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "./ircserv <PORT> <PASSWORD>\n";
		exit(EXIT_FAILURE);
	}

	Server	irc_server(av[1], av[2]);
	irc_server.start();
	return 0;
}
