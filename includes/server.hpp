#ifndef SERVER_HPP
#define SERVER_HPP

# include <vector>

# include "socket.hpp"
# include "user.hpp"

/*struct User
{
	int			_socket;
	struct sockaddr_in	_address;
	std::string             name;
	std::string             nickname;
	std::string             username;
};*/

class Server
{
	private:
		Socket				_socket;
		int				_port;
		std::vector<User>		_user;
		std::string			_password;
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
