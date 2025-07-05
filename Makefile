# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 15:37:04 by dlesieur          #+#    #+#              #
#    Updated: 2025/07/05 21:34:50 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GEN_NAME
NAME=fdf.a
CPROG=fdf

# COMPILER AND FLAGS
CC = cc
DEBUG_FLAGS = -g -fsanitize=address -fsanitize=undefined
RELEASE_FLAGS = -O3 -DNDEBUG

# COMMAND
AR = ar rcs
RM = rm -rf

# DIRECTORY ARCHITECTURE
D_LIBS = libs
D_SRCS = srcs
D_CORE = $(D_SRCS)/core
D_HANDLERS = $(D_SRCS)/handlers
D_PARSER = $(D_SRCS)/parser
D_RENDU = $(D_SRCS)/rendu
D_LIBFT = $(D_LIBS)/libft
D_MINILIBX = $(D_LIBS)/minilibx-linux
CFLAGS = -Wall -Wextra -Werror -I./inc -I./$(D_LIBFT) -I./$(D_MINILIBX)

# SOURCE FILES
SRC_CORE = $(D_CORE)/main.c
SRC_HANDLERS = $(D_HANDLERS)/hooks/close.c
SRC_PARSER = $(D_PARSER)/super_trim.c $(D_PARSER)/parser.c

SRCS = $(SRC_CORE) $(SRC_HANDLERS) $(SRC_PARSER)
OBJECTS = $(SRCS:.c=.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[1;33m
NC = \033[0m

# Default target
all: $(NAME)

# COMPILE OBJECTS FILES
%.o: %.c
	@echo "$(YELLOW)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# LINK EXECUTABLES
$(NAME): $(OBJECTS)
	@echo "$(GREEN)Creating $(NAME)$(NC)"
	@$(AR) $(NAME) $(OBJECTS)

$(CPROG): $(OBJECTS)
	@echo "$(GREEN)Creating $(CPROG)$(NC)"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(CPROG)

# CLEAN OBJECT FILES
clean:
	@echo "$(RED)Cleaning object files$(NC)"
	@$(RM) $(OBJECTS)

# CLEAN EVERYTHING
fclean: clean
	@echo "$(RED)Cleaning $(NAME) and $(CPROG)$(NC)"
	@$(RM) $(NAME) $(CPROG)

# REBUILD
re: fclean all

# HELP
help:
	@echo "$(GREEN)FDF Parser Makefile$(NC)"
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)        - Build the program"
	@echo "  $(YELLOW)clean$(NC)      - Remove object files"
	@echo "  $(YELLOW)fclean$(NC)     - Remove object files and executable"
	@echo "  $(YELLOW)re$(NC)         - Rebuild everything"
	@echo "  $(YELLOW)help$(NC)       - Show this help"

.PHONY: all clean fclean re help
.DEFAULT_GOAL := all