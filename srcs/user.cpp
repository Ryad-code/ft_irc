#include "../includes/user.hpp"

User::User(int socket, struct sockaddr_in address, std::string name, std::string nickname, std::string username) : _socket(socket), _address(address), _name(name), _nickname(nickname), _username(username)
{
	bzero(_buffer, 1024);
}

User::~User(void) {}

int			User::get_socket(void) const {return _socket;}

struct sockaddr_in	User::get_address(void) const {return _address;}

std::string		User::get_name(void) const {return _name;}

std::string		User::get_nickname(void) const {return _nickname;}

std::string		User::get_username(void) const {return _username;}

//const std::queue<std::string> &User::get_request(void) const {return _request;}
