#include "../includes/socket.hpp"

//Constructor
Socket::Socket(int domain, int service, int protocol, int port, u_long interface, int back_log)
{
	int	binding;
	//Initialising struct sockaddr_in
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(interface);
	//Creating socket
	_sock = socket(domain, service, protocol);
	//Test socket
	if (_sock < 0)
	{
		perror("Error: failed to create socket...");
		exit(1);
	}
	//Binding between socket and address
	binding = bind(_sock, (struct sockaddr *) &_address, sizeof(_address));
	//Test binding
	if (binding < 0)
	{
		perror("Error: failed to bind socket to local address...");
		exit(1);
	}
	//Socket queue lenght
	_back_log = back_log;
}

//Destructor
Socket::~Socket(void) {}

//Getters
const int&		Socket::get_sock(void) const
{
	return(_sock);
}
struct sockaddr_in	Socket::get_addr(void) const
{
	return(_address);
}
//Binding between socket and address
int			Socket::bind_sock(int sock, struct sockaddr_in addr)
{
	return (bind(sock, (struct sockaddr *) &addr, sizeof(addr)));
}
//Listening to incoming connexions on socket
int			Socket::listen_sock(void)
{
	return(listen(_sock, _back_log));
}
//Accepting connexions (Creating a connexion socket)
int			Socket::accept_sock(struct sockaddr_in addr)
{
	socklen_t len = sizeof(addr);
	return(accept(_sock, (struct sockaddr *) &addr, &len));
}
//Reading on socket created by accept_sock
int			Socket::read_sock(const int fd)
{
	int	res;
	char	buffer[BUFF_SIZE];

	res = read(fd, buffer, sizeof(buffer));
	std::cout << "->" << buffer << std::endl;
	bzero(&buffer, sizeof(buffer));
	return (res);
}

