#ifndef SERVER_HPP
#define SERVER_HPP

# include <vector>

# include "socket.hpp"
# include "user.hpp"

class Server
{
	private:
		Socket				_socket;
		char				_buffer[1024];
		int				_port;
		std::vector<User>		_user;
		std::string			_password;
		int				_nb_user;
		fd_set				_read_sockets;
		fd_set				_write_sockets;
		fd_set				_except_sockets;

	public:
		//Constructor & Destructor
		Server(int port, std::string password);
		~Server(void);

		//Getters
		Socket		get_socket(void) const;
		int		get_port(void) const;
		std::string	get_password(void) const;
		int		get_nb_user(void) const;

		//Parsing connexion request
		int		parse_connexion(int fd, struct sockaddr_in addr, std::string str);	

		//FD_SET
		void		update_sets(void);

		//Start Server
		int		start_server(void);
};

#endif
