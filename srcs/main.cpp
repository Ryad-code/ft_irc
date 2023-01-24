#include "../includes/ircserv.hpp"

int main (int ac, char **av)
{
	(void)ac;
	(void)av;
	int res;
	Server	new_server = Server(6667, "password");

	res = new_server.start_server();
	if (res < 0)
	{
		std::cout << "Ca marche pas\n";
		return -1;
	}

	return 0;
}
