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
		std::string		_realname;
		bool 			_registred;
		bool 			_connected;
        std::string     _host;
        std::string     _awayMessage;

	public:
		User(int, const std::string&);
		~User();

		std::string const&	get_nickname() const;
		std::string const&	get_username() const;
		std::string const&	get_realname() const;
		bool 		const&	get_registred() const;
        const int&			get_socket() const;
        std::string const&	get_awayMessage() const;
        std::string         get_fullname() const;
        bool                is_away() const;
        bool                is_connected() const;
        bool                is_authenticated() const;

		void				set_registred(bool);
		void				set_connected(bool);
		void 				set_nickname(const std::string&);
		void 				set_username(const std::string&);
		void				set_realname(const std::string&);
        void                set_awayMessage(const std::string&);
};
