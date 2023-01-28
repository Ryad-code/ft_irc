#include "../includes/user.hpp"

#include <stdlib.h>
#include <iostream>

User::User(int socket, struct sockaddr_in address, std::string nickname, std::string username) : _socket(socket), _address(address), _nickname(nickname), _username(username)
{
	_buffer = (char*)malloc(sizeof(char) * 1024);
	bzero(_buffer, 1024);
	_connected = false;
}

User::~User(void) {}

int			User::get_socket(void) const {return _socket;}

char*			User::get_buffer(void) const {return _buffer;}

struct sockaddr_in	User::get_address(void) const {return _address;}

std::string		User::get_cap_ls(void) const {return _cap_ls;}

std::string		User::get_pass(void) const {return _pass;}

std::string		User::get_nickname(void) const {return _nickname;}

std::string		User::get_username(void) const {return _username;}

int			User::parse_user(void)
{
	std::string str = _buffer;
	std::string delimiter = "\r\n";

	while (true)
	{
		if (str.find(delimiter) > str.size())
			break;
		else
		{
			if (str.substr(0, str.find(" ")) == "CAP")
			{
				if (_cap_ls.empty() && _pass.empty() && _nickname.empty() && _username.empty())
					_cap_ls = str.substr(str.find(" ") + 1, 2);
			}
			else if (str.substr(0, str.find(" ")) == "PASS")
			{
				if (_pass.empty() && _nickname.empty() && _username.empty())
					_pass = str.substr(str.find(" ") + 1, str.find(delimiter) - 5);
			}
			else if (str.substr(0, str.find(" ")) == "NICK")
			{
				if (!_pass.empty() && _nickname.empty() && _username.empty())
					_nickname = str.substr(str.find(" ") + 1, str.find(delimiter) - 5);
			}
			else if (str.substr(0, str.find(" ")) == "USER")
			{
				if (!_pass.empty() && !_nickname.empty() && _username.empty())
					_username = str.substr(str.find(" ") + 1, str.find(delimiter) - 5);
			}
			else
				std::cout << "Error\n";
		}
		str = str.substr(str.find(delimiter) + 2, str.size());
		if (!_pass.empty() && !_nickname.empty() && !_username.empty())
		{
			std::cout << "New user created :\n";
			std::cout << "Pass = " << _pass << std::endl;
			std::cout << "Nick = " << _nickname << std::endl;
			std::cout << "User = " << _username << std::endl;
		}
	}
	return 0;
}

