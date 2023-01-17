#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	int client_socket;
	struct sockaddr_in server_address;

	// Créer un socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Configurer l'adresse du serveur
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// Connecter le socket au serveur
	connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Envoyer les messages au serveur
	bool 		res = true;
	std::string	 str;
	while (res)
	{
		if (!std::getline(std::cin, str))
			break;
		else
		{
			if (str == "EXIT")
				res = false;
			else
				send(client_socket, str.c_str(), str.size(), 0);
		}
	}
	str.clear();

	// Fermer le socket
	close(client_socket);

	return 0;
}
