# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 20:00:00 by dlesieur          #+#    #+#              #
#    Updated: 2025/07/05 21:45:12 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = fdf_parser

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
DEBUG_FLAGS = -g -fsanitize=address -fsanitize=undefined
RELEASE_FLAGS = -O3 -DNDEBUG

# Use current directory for sources and objects
SRC_FILES = main.c \
			super_trim.c \
			parser_helper.c \

SRCS = $(SRC_FILES)
OBJS = $(SRC_FILES:.c=.o)

# Header files
HEADERS = parser.h

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[1;33m
NC = \033[0m # No Color

# Default target
all: $(NAME)

# Compile object files
%.o: %.c $(HEADERS)
	@echo "$(YELLOW)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re
	@echo "$(YELLOW)🐛 Debug build completed$(NC)"

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: re
	@echo "$(GREEN)🚀 Release build completed$(NC)"

# Clean object files
clean:
	@rm -f *.o
	@echo "$(RED)🧹 Object files cleaned$(NC)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧹 Executable cleaned$(NC)"

# Rebuild
re: fclean all

# Create source directory structure
setup:
	@mkdir -p $(SRC_DIR) $(INC_DIR) $(TEST_DIR)
	@echo "$(BLUE)📁 Project structure created$(NC)"

# Create test maps
test_maps: setup
	@echo "$(BLUE)Creating test maps...$(NC)"
	@echo "0 0 0 0 0\n0 0 0 0 0\n0 0 0 0 0\n0 0 0 0 0\n0 0 0 0 0" > $(TEST_DIR)/simple.fdf
	@echo "10 0 0 0 0 0 0 0 0 0 10\n0 0 0 0 0 0 0 0 0 0 0\n0 0 10 10 0 0 10 10 0 0 0\n0 0 10 10 0 0 10 10 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 10 10 0 0 10 10 0 0 0\n0 0 10 10 0 0 10 10 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n10 0 0 0 0 0 0 0 0 0 10" > $(TEST_DIR)/pyramids.fdf
	@echo "0,0xFF0000 0,0x00FF00 0,0x0000FF\n0,0xFFFF00 10,0xFF00FF 0,0x00FFFF\n0,0xFFFFFF 0,0x000000 0,0x888888" > $(TEST_DIR)/colors.fdf
	@echo "-5 -3 -1 1 3 5\n-4 -2 0 2 4 6\n-3 -1 1 3 5 7" > $(TEST_DIR)/negative.fdf
	@echo "$(GREEN)✅ Test maps created in $(TEST_DIR)/$(NC)"

# Test with different maps
test: $(NAME) test_maps
	@echo "$(BLUE)🧪 Testing parser with different maps...$(NC)"
	@echo "\n$(YELLOW)Testing simple map:$(NC)"
	@./$(NAME) $(TEST_DIR)/simple.fdf
	@echo "\n$(YELLOW)Testing pyramids map:$(NC)"
	@./$(NAME) $(TEST_DIR)/pyramids.fdf
	@echo "\n$(YELLOW)Testing colors map:$(NC)"
	@./$(NAME) $(TEST_DIR)/colors.fdf
	@echo "\n$(YELLOW)Testing negative values map:$(NC)"
	@./$(NAME) $(TEST_DIR)/negative.fdf

# Test with custom file
test_file: $(NAME)
	@if [ -z "$(FILE)" ]; then \
		echo "$(RED)❌ Usage: make test_file FILE=<path_to_file>$(NC)"; \
	else \
		echo "$(BLUE)🧪 Testing with custom file: $(FILE)$(NC)"; \
		./$(NAME) $(FILE); \
	fi

# Memory leak test
valgrind: $(NAME) test_maps
	@echo "$(BLUE)🔍 Running memory leak tests...$(NC)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(TEST_DIR)/colors.fdf

# Performance test
perf: release test_maps
	@echo "$(BLUE)⚡ Running performance test...$(NC)"
	@time ./$(NAME) $(TEST_DIR)/pyramids.fdf

# Help
help:
	@echo "$(GREEN)FDF Parser Makefile$(NC)"
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)        - Build the program"
	@echo "  $(YELLOW)debug$(NC)      - Build with debug flags"
	@echo "  $(YELLOW)release$(NC)    - Build optimized version"
	@echo "  $(YELLOW)clean$(NC)      - Remove object files"
	@echo "  $(YELLOW)fclean$(NC)     - Remove object files and executable"
	@echo "  $(YELLOW)re$(NC)         - Rebuild everything"
	@echo "  $(YELLOW)setup$(NC)      - Create project directory structure"
	@echo "  $(YELLOW)test_maps$(NC)  - Create test map files"
	@echo "  $(YELLOW)test$(NC)       - Run tests with all test maps"
	@echo "  $(YELLOW)test_file$(NC)  - Test with custom file (make test_file FILE=path)"
	@echo "  $(YELLOW)valgrind$(NC)   - Run memory leak tests"
	@echo "  $(YELLOW)perf$(NC)       - Run performance tests"
	@echo "  $(YELLOW)help$(NC)       - Show this help"

# Install dependencies (for development)
install:
	@echo "$(BLUE)📦 Installing development dependencies...$(NC)"
	@which valgrind > /dev/null || echo "$(YELLOW)⚠️  Consider installing valgrind for memory testing$(NC)"
	@which gcc > /dev/null || echo "$(RED)❌ GCC is required$(NC)"
	@echo "$(GREEN)✅ Dependencies checked$(NC)"

# Phony targets
.PHONY: all debug release clean fclean re setup test_maps test test_file valgrind perf help install

# Default goal
.DEFAULT_GOAL := all