//
// Created by Achiote Tory on 4/12/22.
//

#pragma once

#include <iostream>
#include <map>
#include "User.hpp"

class User;

class Server {

	typedef	void (Server::*commandPtr)();

	private:
		const std::string&					_port;
		const std::string&					_password;
		int									_socket;

		std::map<std::string, commandPtr>	_commands;
		std::map<int, User*>				_users;

	public:
		Server(std::string const& port, std::string const& password);
		~Server();

		void	start();
//		void	stop();

		void	pass();
		void	user();

		int		max_socket() const;

	protected:
		void	Init();
};
