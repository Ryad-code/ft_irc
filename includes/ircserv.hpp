#ifndef IRCSERV_HPP
# define IRCSERV_HPP
#define SERVER_PORT 6667
#define TCP 0
#define BACK_LOG 10
#define BUFF_SIZE 1024

# include <cstdlib>
# include <iostream>
# include <vector>
# include <map>
# include <queue>
# include <string>
# include <cstring>

# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <strings.h>

// ---- Sockets -----
//# include "socket.hpp"

// ----- Select -----
# include <sys/select.h>

// ----- IRC Objects ----- 
# include "server.hpp"

#endif
