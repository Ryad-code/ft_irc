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
/*int			Server::parse_connexion(int fd, struct sockaddr_in addr, std::string str)
{
//	std::string tmp;
	if (str.empty())
	{
		std::cout << "Error: empty buffer..." << std::endl;
		return -1;
	}
	//Parsing commands
	std::string cap_ls = str.substr(0, str.find("\r\n"));	//CAP LS
	str.erase(0, str.find("\r\n") + 2);
	
	std::string password = str.substr(0, str.find("\r\n"));	//PASSWORD
	tmp = password;
	password = tmp.substr(tmp.find(" ") + 1, tmp.size());
	str.erase(0, str.find("\r\n") + 2);

	std::string nick = str.substr(0, str.find("\r\n"));	//NICK
	str.erase(0, str.find("\r\n") + 2);

	std::string user = str.substr(0, str.find("\n"));	//USER
	if (password.empty() || nick.empty() || user.empty())
	{
		std::cout << "Error: wrong connexion request..." << std::endl;
		return -1;
	}
	//Creating new user
	if (password == _password)
		_user.push_back(User(fd, addr, password, nick, user));
	else
	{
		std::cout << "Error: wrong password..." << std::endl;
		return -1;
	}
	_user.push_back(User(fd, addr, "", "", ""));
	_user[_nb_user - 1].get_request().push(str);
	std::cout << _nb_user << std::endl;
//	std::cout << "bonjour\n";
	std::cout << _user[_nb_user - 1].get_request().front() << std::endl;
//	std::cout << _user[_nb_user - 1].get_request().back() << std::endl;

	return 0;
}*/

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
//	while (true)
//	{
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
			//READING IN BUFFER
			if (read(new_fd, _buffer, sizeof(_buffer)) < 0)
				return -1;
			//INCREASE _NB_USER
			_nb_user++;
			//CLOSING NEW_FD
			close(new_fd);
		}
		std::string	str = _buffer;
		//PRINTING INFOS
		std::cout << "--------------------------\n";
		std::cout << _buffer << std::endl;
//		std::cout << _user[_nb_user - 1].get_name() << std::endl;
//		std::cout << _user[_nb_user - 1].get_nickname() << std::endl;
//		std::cout << _user[_nb_user - 1].get_username() << std::endl;
//	}
//	shutdown(listening, 2);
//	shutdown(accepting, 2);
	close(_socket.get_sock());
//	close(new_fd);

	return 0;
}

