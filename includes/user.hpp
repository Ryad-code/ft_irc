#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <queue>

# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <strings.h>

class User
{
	private:
		int				_socket;
		char*				_buffer;
		struct sockaddr_in		_address;
		std::string			_cap_ls;
		std::string			_pass;
		std::string			_nickname;
		std::string			_username;
		bool				_connected;

	public:
		//Constructor & Destructor
		User(int socket, struct sockaddr_in address, std::string nickname, std::string username);
		~User(void);

		//Getters
		int				get_socket(void) const;
		char*				get_buffer(void) const;
		struct sockaddr_in		get_address(void) const;
		std::string			get_cap_ls(void) const;
		std::string			get_pass(void) const;
		std::string			get_nickname(void) const;
		std::string			get_username(void) const;

		//Parsing
		int				parse_user(void);
};

#endif
