#include "../includes/server.hpp"

//Constructor
Server::Server(int port, std::string password) : _socket(AF_INET, SOCK_STREAM, TCP, port, INADDR_ANY, BACK_LOG), _port(port), _password(password), _nb_user(0)
{
	bzero(_buffer, 1024);
}

//Destructor
Server::~Server(void)
{
}
//Getters
Socket			Server::get_socket(void) const {return _socket;}
int			Server::get_port(void) const {return _port;}
std::string		Server::get_password(void) const {return _password;}
int			Server::get_nb_user(void) const {return _nb_user;}

void			Server::update_sets(void)
{
	std::vector<User>::iterator it = _user.begin();

	//CLEANING FD_SETS
	FD_ZERO(&_read_sockets);
	FD_ZERO(&_write_sockets);
	FD_ZERO(&_except_sockets);
	//PUTTING LISTENING SOCKET IN FD_SETS
	FD_SET(_socket.get_sock(), &_read_sockets);
	FD_SET(_socket.get_sock(), &_write_sockets);
	FD_SET(_socket.get_sock(), &_except_sockets);
	//PUTIING USER SOCKETS IN FD_SETS
	for (; it != _user.end(); it++)
	{
		FD_SET((*it).get_socket(), &_read_sockets);
		FD_SET((*it).get_socket(), &_write_sockets);
		FD_SET((*it).get_socket(), &_except_sockets);
	}
}

//Start Server
int			Server::start_server(void)
{
	//LISTENING
	if (_socket.listen_sock() < 0)
	{
		std::cout << "Error: failed to listen...\n";
		return -1;
	}
//	for (int i = 0; i < 10; i++)
	while (true)
	{
		//UPDATE FT_SETS
		update_sets();
		//SELECT
		if (select(FD_SETSIZE, &_read_sockets, &_write_sockets, &_except_sockets, NULL) < 0)
		{
			std::cout << "Error:failed to select\n";
				return -1;
		}
		//CHECKING NEW CONNECTION
		if (FD_ISSET(_socket.get_sock(), &_read_sockets))
		{
			int			new_fd;
			struct sockaddr_in	new_address;

			std::cout << "New connection incoming\n";
			//ACCEPTING
			new_fd = _socket.accept_sock(new_address);
			if (new_fd < 0)
			{
				std::cout << "Error:failed to accept...\n";
				return -1;
			}
			//CREATING USER (Storing fd & address)
			_user.push_back(User(new_fd, new_address, "", ""));
			//INCREASING NB_USER
			_nb_user++;
		}
		//CHECKING IF NEW CONNECTION IS READABLE
		if (FD_ISSET(_user[_nb_user - 1].get_socket(), &_read_sockets))
		{
			//READING IN USER_BUFFER
			if (read(_user[_nb_user - 1].get_socket(), _user[_nb_user - 1].get_buffer(), sizeof(_buffer)) < 0)
				return -1;
			//PARSING
			std::string buffer = _user[_nb_user - 1].get_buffer();
			_user[_nb_user - 1].parse_user();
		}
	}
//	std::cout << "--------------------------\n";
//	std::cout << "nb_user = " << _nb_user << std::endl;
//	std::cout << _user[_nb_user - 1].get_cap_ls() << std::endl;	
//	std::cout << _user[_nb_user - 1].get_pass() << std::endl;
//	std::cout << _user[_nb_user - 1].get_nickname() << std::endl;
//	std::cout << _user[_nb_user - 1].get_username() << std::endl;

//	shutdown(listening, 2);
//	shutdown(accepting, 2);

	//CLOSING USER SOCKETS
	std::vector<User>::iterator it = _user.begin();
	for (; it != _user.end(); it++)
	{
		close((*it).get_socket());
		free((*it).get_buffer());
	}

	//CLOSING SERVER SOCKET
	close(_socket.get_sock());
	
	return 0;
}

