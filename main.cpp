#include <iostream>
#include "Sources/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "try \n./ft_irc <PORT> <PASSWORD> \n";
		exit(EXIT_FAILURE);
	}

	Server	irc_server(av[1], av[2]);
	irc_server.start();
	return 0;
}
