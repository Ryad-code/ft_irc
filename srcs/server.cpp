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

//Parsing connexion request
int			Server::parse_connexion(int fd, struct sockaddr_in addr, std::string str)
{	
	std::string	cap_ls;
	std::string	pass;
	std::string	nick;
	std::string	user;
	std::string	delimiter = "\r\n";

	//CAUTION
	(void)fd;
	(void)addr;

	//PARSING
	while (true)
	{
		if (str.find(delimiter) > str.size())
			break;
		else
		{
			if (str.substr(0, str.find(" ")) == "CAP")
				cap_ls = str.substr(str.find(" ") + 1, 2);
			else if (str.substr(0, str.find(" ")) == "PASS")
				pass = str.substr(str.find(" ") + 1, str.find(delimiter) - 5);
			else if (str.substr(0, str.find(" ")) == "NICK")
				nick = str.substr(str.find(" ") + 1, str.find(delimiter) - 5);
			else if (str.substr(0, str.find(" ")) == "USER")
				user = str.substr(str.find(" ") + 1, str.find(delimiter) - 5);
			else
			{
				std::cout << "Parsing Error2\n";
				break;
			}
			str = str.substr(str.find(delimiter) + 2, str.size());
		}
	}
	if (cap_ls.empty() == false)
		std::cout << "|" << cap_ls << "|" << std::endl;
	if (pass.empty() == false)
		std::cout << "|" << pass << "|" << std::endl;
	if (nick.empty() == false)
		std::cout << "|" << nick << "|" << std::endl;
	if (user.empty() == false)
		std::cout << "|" << user << "|" << std::endl;
	//If all fields are set
	if (!pass.empty() && !nick.empty() && !user.empty())
		std::cout << "NEW USER\n";
	
	return 0;
}

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
			_user.push_back(User(new_fd, new_address, "", "", ""));
			//INCREASING NB_USER
			_nb_user++;
			//READING IN USER_BUFFER
			if (read(new_fd, _user[_nb_user - 1].get_buffer(), sizeof(_buffer)) < 0)
				return -1;
			//PARSING
			std::string buffer = _user[_nb_user - 1].get_buffer();
			parse_connexion(new_fd, new_address, buffer);
			//bzero(_buffer, sizeof(_buffer));
		}
	}
	std::cout << "--------------------------\n";

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

