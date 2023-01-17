#include "server.hpp"

int main (int ac, char **av)
{
	Server IRC = Server();

	IRC.socket_bind();

	IRC.socket_listen(5);

	IRC.socket_accept();

	//for (int i = 0; i < 4; i++)
	int i = 0;
        while (true)
	{
                char *buffer = (char*)malloc(sizeof(char) * 1024);
		buffer = IRC.socket_recv(buffer);
                std::cout << buffer << std::endl;
		std::cout << "i = " << i << std::endl;
		i++;
                free(buffer);
        }
	
	IRC.socket_close();

	return 0;
}
