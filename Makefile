# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlesage <nlesage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 15:49:33 by nlesage           #+#    #+#              #
#    Updated: 2022/12/28 15:11:17 by nlesage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
				handle_error.c \
				load_arg.c

SRCS_BONUS	= ${SRCS}

NAME		= philo

NAME_BO		= bon

HEADERS		= Includes/

FLAGS		= -Wall -Wextra -Werror

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

CC			= cc

.c.o:
			${CC} ${FLAGS} -I${HEADERS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${FLAGS} -I${HEADERS} -o ${NAME} ${OBJS}

${NAME_BO}:	${OBJS}
			${CC} ${FLAGS} -I${HEADERS} -o ${NAME_BO} ${OBJS}
			
bonus:		${NAME_BO}

clean:		
			rm -f ${OBJS} ${OBJS_BONUS}

fclean:		clean
			rm -f ${NAME} ${NAME_BO}

re:			fclean all

.PHONY:		clean, fclean, re, bonus, all
