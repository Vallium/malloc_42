# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 15:55:17 by aalliot           #+#    #+#              #
#    Updated: 2017/03/31 16:49:22 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(UNAME_S)
endif

DYNAMIC_LIB	= libft_malloc_$(HOSTTYPE).so
STATIC_LIB	= libft_malloc_$(HOSTTYPE).a
DEBUG_LIB	= libft_malloc_$(HOSTTYPE)_debug.so

SRC =	ft_malloc.c

HEAD_DIR	= includes
SRC_DIR		= src
DYNAMIC_DIR	= dynamic
STATIC_DIR	= static
DEBUG_DIR	= debug

DYNAMIC_OBJ		= $(patsubst %.c,$(DYNAMIC_DIR)/%.o,$(SRC))
STATIC_OBJ		= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ		= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

#DYNAMIC_DEPS	= $(patsubst %.c,$(DYNAMIC_DIR)/%.d,$(SRC))
#STATIC_DEPS		= $(patsubst %.c,$(STATIC_DIR)/%.d,$(SRC))
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

$(shell mkdir -p $(DYNAMIC_DIR) $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_LIB) binary $(DYNAMIC_LIB)

debug: $(DEBUG_LIB) binary_debug

$(DYNAMIC_LIB): $(LIBFT_STATIC) $(DYNAMIC_OBJ)
	$(CC) $(OPTI) -shared -o $@ $(DYNAMIC_OBJ) $(LIBFT_STATIC)

$(STATIC_LIB): $(LIBFT_STATIC) $(STATIC_OBJ)
	ar rc $@ $(STATIC_OBJ)
	ranlib $@

$(DEBUG_LIB): $(LIBFT_DEBUG) $(DEBUG_OBJ)
	ar rc $@ $(DEBUG_OBJ)
	ranlib $@

-include $(DYNAMIC_OBJ:.o=.d)

$(DYNAMIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) -fPIC $(DEPENDS) -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

-include $(STATIC_OBJ:.o=.d)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) $(DEPENDS) -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

-include $(DEBUG_OBJ:.o=.d)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -g $(DEPENDS) -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $<

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re binary

binary:
	$(CC) -o malloc_test main.c $(STATIC_LIB) $(LIBFT_STATIC) -I$(HEAD_DIR) -I$(LIBFT_HEAD)

binary_debug:
	$(CC) -g -o malloc_test main.c $(DEBUG_LIB) $(LIBFT_DEBUG) -I$(HEAD_DIR) -I$(LIBFT_HEAD)

clean:
	make -C libft clean
	@rm -f $(DYNAMIC_OBJ) $(STATIC_OBJ) $(DEBUG_OBJ) $(DYNAMIC_DEPS) $(STATIC_DEPS) $(DEBUG_DEPS)

fclean: clean
	make -C libft fclean
	@rm -f $(DYNAMIC_LIB) $(STATIC_LIB) $(DEBUG_LIB)

re: fclean
	make
