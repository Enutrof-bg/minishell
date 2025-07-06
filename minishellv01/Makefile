# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 12:48:55 by kevwang           #+#    #+#              #
#    Updated: 2025/06/26 12:48:57 by kevwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

FLAGS = -lreadline

NAME = minishell

FILE = main.c \
ft_split.c \
ft_strjoin.c \
minishell_exec.c \
minishell_free.c \
minishell_utils.c

SRC = ${FILE:.c=.o}

all : ${NAME}

${NAME}: ${SRC}
	${CC} ${CFLAGS} -o $@ $^ ${FLAGS}

test: test.c
	${CC} ${CFLAGS} -o $@ $^ ${FLAGS}

%.o:%.c
	${CC} ${CFLAGS} -c $^

clean: 
	rm -f main.o \
	test \
	ft_split.o \
	ft_strjoin.o \
	minishell_exec.o \
	minishell_free.o \
	minishell_utils.o

fclean:clean
	rm -f minishell

re:fclean
	make