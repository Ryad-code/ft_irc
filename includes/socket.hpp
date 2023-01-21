#ifndef SOCKET_HPP
# define SOCKET_HPP

#define SERVER_PORT 6667
#define TCP 0
#define BACK_LOG 10
#define BUFF_SIZE 1024

# include <sys/socket.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <strings.h>

#include <iostream>
#include <ostream>

class Socket
{
	private:
		int				_sock;		//File descriptor
		sockaddr_in			_address;	//Binding address
		int				_back_log;	//Lenght of connexion queue

	public:
		//Constuctor & Destructor
		Socket(int domain, int service, int protocol, int port, u_long interface, int back_log);
		~Socket(void);

		//Getters
		const int& 			get_sock() const;
		struct sockaddr_in		get_addr() const;

		//Binding
		int				bind_sock(int sock, struct sockaddr_in addr);
		//Listening
		int				listen_sock(void);
		//Accepting connexion
		int				accept_sock(struct sockaddr_in addr);
		//Reading
		int				read_sock(const int fd);
};

#endif
