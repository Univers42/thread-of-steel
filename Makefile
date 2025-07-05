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

##
## @note : for now I'm usign recursive assignment, but I need to use ':='
## 
##

# DEFINE MACROS
define cmd_lib 
	@echo "$(YELLOW)[WARNING]$(NC) $(1) => $(2)"
	$(MAKE) -C $(1) $(2)
endef

# GEN_NAME
NAME=fdf.a
CPROG=fdf

# COMPILER AND FLAGS
CC = cc
CFLAGS= -Wall -Wextra -Werror -I./inc
DEBUG_FLAGS = -g -fsanitize=address -fsanitize=undefined
RELEASE_FLAGS = -O3 -DNDEBUG

# COMMAND
AR = ar rcs
RM = rm -rf

# DIRECTORY ARCHITECTURE
D_LIB = libs
D_SRCS = srcs
D_CORE = $(D_SRCS)/core
D_HANDLERS = $(D_SRCS)/handlers
D_PARSER = $(D_SRCS)/parser
D_RENDU = $(D_SRCS)/rendu
D_LIBFT = $(D_LIBS)/libft
D_MINILIBX = $(D_LIBS)/minilibx-linux

# FILES FOR EACH DIRECTORIES
SRC_PARSER =	super_trim.c		\
				parser_helper.c		\
				main_parser.c

# Colors for output
GREEN =	\033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[1;33m
NC = \033[0m # No Color

# Default target
all :  $(NAME)

# COMPILE OBJECTS FILES
%.o :  %.c
	@echo "$(YELLOW)Linking $(NAME) $<$(NC)"
	@$(CC) $(CFLAGS) -c %< -o $@

# LINK EXECUTABLES
$(NAME): $(OBJECTS)
	$(AR) $(OBJECTS) $(NAME)

build:
	@echo "$(YELLOW) Building the libs: $(D_LIBFT) $(MINILIBX)"
	$(call cmd_lib, $(D_LIBFT), all)
	$(call cmd_lib, $(MINILIBX), all)
	
# DEBUG BUILD
debug: $(OBJECTS)

# CLEAN  OBJECT FILES
clean:
	$(RM) $(OBJECTS)
	$(call cmd_lib, $(D_LIBFT), clean)
	$(call cmd_lib, $(D_LIBFT), clean)

# CLEAN EVERYTHING
fclean: clean
	$(RM) $(NAME) $(CPROG)
	$(call cmd_lib, $(D_LIBFT), fclean)
	$(call cmd_lib, $(D_LIBFT), fclean)

# MEMORY LEAK TEST
# PERFORMANCE TEST
# INSTALL DEPENDENCIES

# HELP
help:
	@echo "$(GREEN)FDF Parser Makefile$(NC)"
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)        - Build the program"
	@echo "  $(YELLOW)debug$(NC)      - Build with debug flags"
	@echo "  $(YELLOW)release$(NC)    - Build optimized version"
	@echo "  $(YELLOW)clean$(NC)      - Remove object files"
	@echo "  $(YELLOW)fclean$(NC)     - Remove object files and executable"
	@echo "  $(YELLOW)re$(NC)         - Rebuild everything"
	@echo "  $(YELLOW)valgrind$(NC)   - Run memory leak tests"
	@echo "  $(YELLOW)perf$(NC)       - Run performance tests"
	@echo "  $(YELLOW)help$(NC)       - Show this help"
# PHONY TARGETS

.PHONY: all debug release clean fclean re help install valgrind

# DEFAULT GOAL
.DEFAULT_GOAL := all