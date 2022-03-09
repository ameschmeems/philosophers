NAME		:=	philo

SRCS		:=	main.c \
				error.c \
				ft_atoi.c \
				init.c \
				messages.c \
				utils.c
				

OBJS		:=	${SRCS:.c=.o}

CC			:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror -pthread

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${OBJS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re