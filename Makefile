# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 15:37:04 by dlesieur          #+#    #+#              #
#    Updated: 2025/07/04 15:40:00 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf.a

CC=cc
CFLAGS=-Wall -Wextra -Werror
CFLAGS+= -I./inclues
CFLAGS+= -g
CFLAGS+= -fsanitize=address
AR=ar rcs
RM=rm -f

SRCS=srcs/main.c \
