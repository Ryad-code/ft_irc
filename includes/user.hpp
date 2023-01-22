#ifndef USER_HPP
#define USER_HPP

#include <string>

# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <strings.h>

class User
{
	private:
		int			_socket;
		struct sockaddr_in	_address;
		std::string		_name;
		std::string		_nickname;
		std::string		_username;

	public:
		//Constructor & Destructor
		User(int socket, struct sockaddr_in address, std::string name, std::string nickname, std::string username);
		~User(void);

		//Getters
		int			get_socket(void) const;
		struct sockaddr_in	get_address(void) const;
		std::string		get_name(void) const;
		std::string		get_nickname(void) const;
		std::string		get_username(void) const;
};

#endif
