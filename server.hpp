#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <iostream>

struct User
{
	int			client_socket;
	socklen_t		client_len;
	struct sockaddr_in	client_address;
	std::string             name;
	std::string             nickname;
	std::string             username;
};

class Server
{
	private:
		int				server_socket;
		struct sockaddr_in		server_address;
		//std::vector<User>		Users;--->Bonne version
		User				user;
		int				nb_user;

	public:
		Server()
		{
			//Creating socket
			server_socket = socket(AF_INET, SOCK_STREAM, 0);
			//Configurating server address
			server_address.sin_family = AF_INET;
			server_address.sin_port = htons(8080);
			server_address.sin_addr.s_addr = INADDR_ANY;
			//No user to start
			nb_user = 0;
			std::cout << "Creating server\n";
			std::cout << "Creating socket\n";
			std::cout << "Configuring server address\n";
		}

		//Binding socket to server address
		void	socket_bind()
		{
			bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
			std::cout << "Binding socket to server address\n";
		}

		//Listening to connexion
		void	socket_listen(int nb_connexion)
		{
			listen(server_socket, nb_connexion);
			std::cout << "Socket listening...\n";
		}

		//Accepting entering connexion
		//void	socket_accept(User user)--->bon proto
		void	socket_accept(void)	
		{
			user.client_len = sizeof(user.client_address);
			user.client_socket = accept(server_socket, (struct sockaddr *) &user.client_address, &user.client_len);
			std::cout << "Accepting connexions...\n";
		}

		char* socket_recv(char *buffer)
		{
			recv(user.client_socket, buffer, 1024, 0);
			return (buffer);
		}

		void	socket_close(void)
		{
			close(user.client_socket);
			close(server_socket);
		}
};

#endif
