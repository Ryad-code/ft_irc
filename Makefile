NAME = IRCserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ_DIR = objs

SRC_DIR = $(shell find srcs -type d)

INC_DIR = $(foreach dir, ./includes, -I$(dir))

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC = main.cpp socket.cpp server.cpp user.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re


