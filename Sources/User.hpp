//
// Created by Achiote Tory on 4/13/22.
//

#pragma once

#include "iostream"


class User {
	private:
		const int		_socket;
		std::string		_nickname;
		std::string		_username;
	public:
		User(int socket);
		~User();

		std::string const&	get_nickname() const;
		std::string const&	get_username() const;

		void 				set_nickname(const std::string&	nickname);
		void 				set_username(const std::string&	username);
};
