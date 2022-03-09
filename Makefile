NAME		:=	philo

SRCS		:=

OBJS		:=	${SRCS:.c=.o}

CC			:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror -pthread

INCLUDES	:=	./includes

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${OBJS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re