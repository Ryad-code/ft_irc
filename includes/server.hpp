#ifndef SERVER_HPP
#define SERVER_HPP

# include "socket.hpp"

struct User
{
	int			_socket;
	struct sockaddr_in	_address;
	std::string             name;
	std::string             nickname;
	std::string             username;
};

class Server
{
	private:
		Socket				_socket;
		int				_port;
		//std::vector<User>		Users;--->Bonne version
		std::string			_password;
		User				_user;
		int				_nb_user;

	public:
		//Constructor & Destructor
		Server(int port, std::string password);
		~Server(void);

		//Getters
		Socket		get_socket(void) const;
		int		get_port(void) const;
		std::string	get_password(void) const;
		int		get_nb_user(void) const;

		//Start Server
		int			start_server(void);
};

#endif
