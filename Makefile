# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 15:55:17 by aalliot           #+#    #+#              #
#    Updated: 2017/02/01 17:06:19 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(UNAME_S)
endif

DYNAMIC_LIB	= libft_malloc_$(HOSTTYPE).so
DEBUG_LIB	= libft_malloc_$(HOSTTYPE)_debug.so

SRC =	ft_malloc.c

HEAD_DIR	= includes
SRC_DIR		= src
DYNAMIC_DIR	= dynamic
DEBUG_DIR	= debug

DYNAMIC_OBJ		= $(patsubst %.c,$(DYNAMIC_DIR)/%.o,$(SRC))
DEBUG_OBJ		= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

LIBFT_STATIC	= libft/libft.a
LIBFT_DEBUG		= libft/libft_debug.a
LIBFT_HEAD		= libft/includes

CC = gcc
OPTI = -O3

ifeq ($(UNAME_S),Linux)
	FLAGS = -Wall -Wextra -Werror -Wno-unused-result
else
	FLAGS = -Wall -Wextra -Werror
endif

$(shell mkdir -p $(DYNAMIC_DIR) $(DEBUG_DIR))

all: $(DYNAMIC_LIB)

debug: $(DEBUG_LIB)

$(DYNAMIC_LIB): $(LIBFT_STATIC) $(DYNAMIC_OBJ)
	$(CC) $(OPTI) -shared -o $@ $(DYNAMIC_OBJ) $(LIBFT_STATIC)

$(DEBUG_LIB): $(LIBFT_DEBUG) $(DEBUG_OBJ)
	$(CC) $(OPTI) -g -shared -o $@ $(DEBUG_OBJ) $(LIBFT_DEBUG)

$(DYNAMIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) -fPIC -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) -g -fPIC -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re norme

clean:
	make -C libft clean
	@rm -f $(DYNAMIC_OBJ) $(DEBUG_OBJ)

fclean: clean
	make -C libft fclean
	@rm -f $(DYNAMIC_LIB) $(DEBUG_LIB)

re: fclean
	make
