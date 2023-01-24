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
		char				_buffer[1024];
		struct sockaddr_in		_address;
		std::string			_name;
		std::string			_nickname;
		std::string			_username;
		//std::queue<std::string>		_request;

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
		const std::queue<std::string>	&get_request(void) const;
};

#endif
