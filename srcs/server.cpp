#include "../includes/server.hpp"

//Constructor
Server::Server(int port, std::string password) : _socket(AF_INET, SOCK_STREAM, TCP, port, INADDR_ANY, BACK_LOG),
						_port(port), _password(password), _nb_user(0){}

//Destructor
Server::~Server(void)
{
}
//Getters
Socket		Server::get_socket(void) const
{
	return _socket;
}
int		Server::get_port(void) const
{
	return _port;
}
std::string	Server::get_password(void) const
{
	return _password;
}
int		Server::get_nb_user(void) const
{
	return _nb_user;
}
//Start Server
int			Server::start_server(void)
{
	int			listening;
	int			accepting;
	struct sockaddr_in	new_address;

	listening = _socket.listen_sock();
	if (listening < 0)
	{
		perror("Error: failed to listen...");
		return -1;
	}
//	while (true)
//	{
		accepting = _socket.accept_sock(new_address);
		if (accepting < 0)
		{
			perror("Error: failed to accept...");
			return -1;
		}
//		else
//		{
			std::cout << "New connection incoming\n";
			int		res;
			char 		buffer[1024];
			std::string 	str;
			std::string	str1;

			res = read(accepting, buffer, sizeof(buffer));
			if (res < 0)
				return -1;
			str = buffer;
			str1 = str;
			_user.push_back(User(accepting, new_address, str, "", ""));
			_nb_user++;
//		}
//	}
//	std::cout << str.size() << std::endl;

	std::string s1 = str.substr(0, str.find("\n"));

	str.erase(0, str.find("\n") + 1);

	std::string s2 = str.substr(0, str.find("\n"));

	str.erase(0, str.find("\n") + 1);

	std::string s3 = str.substr(0, str.find("\n"));

	str.erase(0, str.find("\n") + 1);

	std::string s4 = str.substr(0, str.find("\n"));

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	std::cout << s3 << std::endl;
	std::cout << s4 << std::endl;
	
	std::cout << "-----------\n" << _user[0].get_name() << std::endl;

	return 0;
}

