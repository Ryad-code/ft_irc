all:
	g++ -o ircserv server.cpp
	g++ -o client client.cpp

re:
	g++ -o ircserv server.cpp
	g++ -o client client.cpp

clean:
	rm -f client ircserv

