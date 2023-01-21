#include "../includes/ircserv.hpp"

int main (int ac, char **av)
{
	int res;
	Server	new_server = Server(6667, "password");

	res = new_server.start_server();
	if (res < 0)
	{
		perror("Ca marche pas\n");
		reurn -1;
	}

	return 0;
}
