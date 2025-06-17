# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 16:01:49 by dlesieur          #+#    #+#              #
#    Updated: 2025/06/17 16:05:25 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libfdf.a
PROG=fdf
CC=cc
INC=inc
CFLAGS=-Wall -Wextra -Werror -I$(INC) -I$(LIBX_PATH)
LDFLAGS=-lmlx -lXext -lX11 -lm
SRC_DIR=src
LIBX_PATH=$(INC)/Minilibx
LIBFT_PATH=$(INC)/libft

# All source files organized by directory
SRCS=$(SRC_DIR)/fdf.c \
	$(SRC_DIR)/parser/parse_map.c \
	$(SRC_DIR)/render/draw_map.c \
	$(SRC_DIR)/render/draw_line.c \
	$(SRC_DIR)/render/pixel.c \
	$(SRC_DIR)/render/color_themes.c \
	$(SRC_DIR)/render/shapes/shapes_manager.c \
	$(SRC_DIR)/render/shapes/shape_flat.c \
	$(SRC_DIR)/render/shapes/shape_sphere.c \
	$(SRC_DIR)/render/shapes/shape_cylinder.c \
	$(SRC_DIR)/render/shapes/shape_cone.c \
	$(SRC_DIR)/render/shapes/shape_wave.c \
	$(SRC_DIR)/render/shapes/shape_torus.c \
	$(SRC_DIR)/render/shapes/shape_saddle.c \
	$(SRC_DIR)/render/shapes/shape_helix.c \
	$(SRC_DIR)/render/shapes/shape_ripple.c \
	$(SRC_DIR)/events/key.c \
	$(SRC_DIR)/events/mouse.c \
	$(SRC_DIR)/events/projection.c \
	$(SRC_DIR)/events/theme_controls.c \
	$(SRC_DIR)/utils/get.c \
	$(SRC_DIR)/utils/exit.c \
	$(SRC_DIR)/utils/vec3.c \
	$(SRC_DIR)/utils/vec2.c \
	$(SRC_DIR)/utils/matrix.c \
	$(SRC_DIR)/utils/math.c \
	$(SRC_DIR)/utils/conversion.c \
	$(SRC_DIR)/utils/verify.c

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

re: fclean all

# Demo and testing targets
demo: $(NAME)
	@chmod +x demo_script.sh
	@./demo_script.sh

test: $(NAME)
	@chmod +x test_performance.sh
	@./test_performance.sh

install_demo_deps:
	@echo "Installing demo dependencies..."
	@sudo apt-get update > /dev/null 2>&1 || true
	@sudo apt-get install -y bc valgrind > /dev/null 2>&1 || true

help:
	@echo "FDF - Thread of Steel Edition"
	@echo "Usage:"
	@echo "  make         - Build the project"
	@echo "  make clean   - Remove object files"
	@echo "  make fclean  - Remove all build files"
	@echo "  make re      - Rebuild everything"
	@echo "  make demo    - Run interactive demo"
	@echo "  make test    - Run performance tests"
	@echo "  make help    - Show this help"

.PHONY: all clean fclean re debug demo test install_demo_deps help