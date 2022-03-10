NAME		:=	philo

SRCS		:=	main.c \
				error.c \
				ft_atoi.c \
				ft_isdigit.c \
				init.c \
				start.c \
				utils.c

OBJS		:=	${SRCS:.c=.o}

CC			:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${OBJS} -o ${NAME} -pthread

clean:
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re