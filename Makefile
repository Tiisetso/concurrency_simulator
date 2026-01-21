# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/07 14:02:01 by timurray          #+#    #+#              #
#    Updated: 2026/01/21 16:34:02 by timurray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CPPFLAGS := -Iinclude
CFLAGS := -Wall -Wextra -Werror
VFLAGS := -g
SFLAGS := -ggdb3 -fsanitize=address -fsanitize=leak -fsanitize=undefined

THREADS := -pthread

SRC_DIR := src
UTL_DIR := $(SRC_DIR)/utils
OBJ_DIR := obj

SOURCES := \
$(SRC_DIR)/clean.c \
$(SRC_DIR)/error.c \
$(SRC_DIR)/init.c \
$(SRC_DIR)/lock.c \
$(SRC_DIR)/mutex.c \
$(SRC_DIR)/parse.c \
$(SRC_DIR)/philo.c \
$(SRC_DIR)/print.c \
$(SRC_DIR)/start.c \
$(SRC_DIR)/thread.c \
$(SRC_DIR)/time.c 

# UTILS := \
# $(UTL_DIR)/ft_atoi_check.c

# SOURCES += ${UTILS}

OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

debug ?= 0
ifeq (${debug}, 1)
	CFLAGS := ${CFLAGS} ${VFLAGS}
endif
ifeq (${debug}, 2)
	CFLAGS := ${CFLAGS} ${SFLAGS}
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJECTS) $(THREADS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
