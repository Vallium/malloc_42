# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 15:55:17 by aalliot           #+#    #+#              #
#    Updated: 2017/07/29 17:00:58 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(UNAME_S)
endif

DYNAMIC_LIB	= libft_malloc_$(HOSTTYPE).so
DEBUG_LIB	= libft_malloc_$(HOSTTYPE)_debug.so

LIBNAME		= ft_malloc_$(HOSTTYPE)
LINKNAME	= libf_malloc.so

SRC =	malloc.c			\
		realloc.c			\
		free.c				\
		show_alloc_mem.c	\
		zones.c				\
		alloc.c				

HEAD_DIR	= includes
SRC_DIR		= src
DYNAMIC_DIR	= dynamic
DEBUG_DIR	= debug

DYNAMIC_OBJ		= $(patsubst %.c,$(DYNAMIC_DIR)/%.o,$(SRC))
DEBUG_OBJ		= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

#DYNAMIC_DEPS	= $(patsubst %.c,$(DYNAMIC_DIR)/%.d,$(SRC))
#DEBUG_DEPS		= $(patsubst %.c,$(DEBUG_DIR)/%.d,$(SRC))

LIBFT_STATIC	= libft/libft.a
LIBFT_DEBUG		= libft/libft_debug.a
LIBFT_HEAD		= libft/includes

CC		= gcc
OPTI	= -O3
DEPENDS	= -MT $@ -MD -MP -MF $(subst .o,.d,$@)

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
	ln -fs $(DYNAMIC_LIB) $(LINKNAME) 

$(DEBUG_LIB): $(LIBFT_DEBUG) $(DEBUG_OBJ)
	$(CC) $(OPTI) -g -shared -o $@ $(DYNAMIC_OBJ) $(LIBFT_STATIC)

-include $(DYNAMIC_OBJ:.o=.d)

$(DYNAMIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) -fPIC $(DEPENDS) -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

-include $(DEBUG_OBJ:.o=.d)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -g -fPIC $(DEPENDS) -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re binary

binary:
	$(CC) -o malloc_test main.c -L. -l$(LIBNAME) -I$(HEAD_DIR) -I$(LIBFT_HEAD)

binary_debug:
	$(CC) -g -o malloc_test_debug main.c $(DEBUG_LIB) $(LIBFT_DEBUG) -I$(HEAD_DIR) -I$(LIBFT_HEAD)

tests:
	$(CC) -o my_test0 test0.c -L. -l$(LIBNAME) -I$(HEAD_DIR) -I$(LIBFT_HEAD)
	$(CC) -o my_test1 test1.c -L. -l$(LIBNAME) -I$(HEAD_DIR) -I$(LIBFT_HEAD)
	$(CC) -o my_test2 test2.c -L. -l$(LIBNAME) -I$(HEAD_DIR) -I$(LIBFT_HEAD)

clean:
	make -C libft clean
	@rm -f $(DYNAMIC_OBJ) $(DEBUG_OBJ) $(DYNAMIC_DEPS) $(DEBUG_DEPS)

fclean: clean
	make -C libft fclean
	@rm -f $(DYNAMIC_LIB) $(DEBUG_LIB) $(LINKNAME)

re: fclean
	make
