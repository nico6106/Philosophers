# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 15:49:33 by nlesage           #+#    #+#              #
#    Updated: 2023/01/11 10:18:52 by nlesage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main_bonus.c \
				load_arg_bonus.c \
				handle_error_bonus.c \
				utils_bonus.c \
				init_bonus.c \
				action_bonus.c \
				philo_bonus.c \
				threads_check_bonus.c

SRCS_BONUS	= ${SRCS}

NAME		= philo_bonus

HEADERS		= Includes/

FLAGS		= -Wall -Wextra -Werror -pthread -g #-fsanitize=thread -g

OBJS		= ${SRCS:.c=.o}

CC			= cc

.c.o:
			${CC} ${FLAGS} -I${HEADERS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${FLAGS} -I${HEADERS} -o ${NAME} ${OBJS}
			
bonus:		${NAME}

clean:		
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		clean, fclean, re, bonus, all
