#include "../includes/server.hpp"

//Constructor
Server::Server(int port, std::string password) : _socket(AF_INET, SOCK_STREAM, TCP, port, INADDR_ANY, BACK_LOG),
						_port(port), _password(password), _nb_user(0){}

//Destructor
Server::~Server(void)
{
}
//Getters
const Socket		Server::get_socket(void) const
{
	return _socket;
}
const int		Server::get_port(void) const
{
	return _port;
}
const std::string	Server::get_password(void) const
{
	return _password;
}
const int		Server::get_nb_user(void) const
{
	return _nb_user;
}
//Start Server
int			Server::start_server(void)
{
	int	listening;
	int	accepting;

	listening = _socket.listen_sock();
	if (listening < 0)
	{
		perror("Error: failed to listen...");
		return -1;
	}
	accepting = _socket.accept_sock(_user._address);
	if (accepting < 0)
	{
		perror("Error: failed to accept...");
		return -1;
	}
	while (true)
	{
		std::cout << "...\n";
		sleep(5);
		_socket.read_sock(accepting);
	}
	return 0;
}

