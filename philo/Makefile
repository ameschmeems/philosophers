NAME		:=	philo

SRCS		:=	main.c \
				error.c \
				ft_atoi.c \
				ft_isdigit.c \
				init.c \
				start.c \
				utils.c \
				norm.c

OBJS		:=	${SRCS:.c=.o}

CC			:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror -pthread -g -fsanitize=thread

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${OBJS} -o ${NAME} ${CFLAGS}

clean:
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re