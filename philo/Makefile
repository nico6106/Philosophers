# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 15:49:33 by nlesage           #+#    #+#              #
#    Updated: 2023/01/12 20:06:42 by nlesage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
				handle_error.c \
				load_arg.c \
				start_threads.c \
				actions.c \
				actions2.c \
				philo.c \
				utils.c \
				handle_end.c \
				free_and_finish.c

SRCS_BONUS	= ${SRCS}

NAME		= philo

HEADERS		= Includes/

FLAGS		= -Wall -Wextra -Werror -pthread -g #-fsanitize=thread -g

OBJS		= ${SRCS:.c=.o}

CC			= cc

.c.o:
			${CC} ${FLAGS} -I${HEADERS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${FLAGS} -I${HEADERS} -o ${NAME} ${OBJS}

clean:		
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		clean, fclean, re, all
