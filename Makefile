# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 12:10:18 by dlesieur          #+#    #+#             #
#    Updated: 2025/06/16 12:26:32 by dlesieur         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 12:10:18 by dlesieur          #+#    #+#             #
#    Updated: 2025/06/16 12:26:32 by dlesieur         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME=libfdf.a
PROG=fdf
CC=cc
INC=inc
CFLAGS=-Wall -Wextra -Werror -I$(INC) -I$(LIBX_PATH)
LDFLAGS=-lmlx -lXext -lX11
SRC_DIR=src
LIBX_PATH=$(INC)/Minilibx
LIBFT_PATH=$(INC)/libft
SRCS=$(SRC_DIR)/fdf.c\
	$(SRC_DIR)/render/draw_simple.c
OBJ_DIR=obj
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
AR=ar -rcs
RM=rm -rf

# Libraries
LIBFT=$(LIBFT_PATH)/libft.a
LIBMLX=$(LIBX_PATH)/libmlx.a

all: $(PROG)

# Build the final program
$(PROG): $(LIBMLX) $(LIBFT) $(NAME)
	$(CC) $(NAME) $(LIBFT) -L$(LIBX_PATH) $(LDFLAGS) -o $(PROG)

# Build our static library
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Build MinilibX library
$(LIBMLX):
	make -C $(LIBX_PATH)

# Build libft library  
$(LIBFT):
	make -C $(LIBFT_PATH)

# Compile source files to objects - with directory creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "LIBFT: $(LIBFT)"
	@echo "LIBMLX: $(LIBMLX)"

clean: 
	$(RM) $(OBJ_DIR)
	-make -C $(LIBFT_PATH) clean 2>/dev/null || true
	-make -C $(LIBX_PATH) clean 2>/dev/null || true

fclean: clean
	$(RM) $(NAME) $(PROG)
	-make -C $(LIBFT_PATH) fclean 2>/dev/null || true
	# MinilibX doesn't have fclean, skip it

re: fclean all

.PHONY: all clean fclean re debug