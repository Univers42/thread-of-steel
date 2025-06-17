# Map Editor Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c99
NAME = map_editor
SRC = map_editor.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

install: $(NAME)
	cp $(NAME) ../$(NAME)
	@echo "Map editor installed in project root"

.PHONY: all clean fclean re install
