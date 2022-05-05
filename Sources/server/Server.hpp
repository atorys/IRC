//
// Created by Achiote Tory on 4/12/22.
//

#pragma once

#include <iostream>
#include <sys/poll.h>
#include <vector>
#include "../service/Service.hpp"

class Server {

	private:
		const std::string&					_port;
		int									_socket;
		std::vector<pollfd>					_polls;
		Service*                            _service;

	public:
		Server(std::string const&, std::string const&);
		~Server();

		void	start();
		void	stop();

	protected:
		void	init();
		void	createSocket();
		void	add();
		void	remove(std::vector<pollfd>::iterator);
		void 	receive(int);
};
