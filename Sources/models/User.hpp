//
// Created by Achiote Tory on 4/13/22.
//

#pragma once

#include "iostream"
// #include <poll.h>

class User {
	private:
		const int		_socket;
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;
		bool 			_registred;
	public:
		User(int);
		~User();

		std::string const&	get_nickname() const;
		std::string const&	get_username() const;
		std::string const&	get_realname() const;
		bool 		const&	get_registred() const;
		const int&			get_socket() const;

		void				set_registred(bool);
		void 				set_nickname(const std::string&);
		void 				set_username(const std::string&);
		void				set_realname(const std::string&);
};
