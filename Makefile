
NAME = ircserv

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

FILES = main Channel Client features/Cmd features/CmdHelper features/INVITE features/JOIN features/KICK features/MODE features/NICK features/PASS features/QUIT features/TOPIC features/USER

HEADERS = features/cmd.hpp Client.hpp Channel.hpp

FOBJ = ${FILES:=.o}

.PHONY = all clean fclean re

all: ${NAME}

${NAME}: ${FOBJ} ${HEADERS}
	${CC} ${FLAGS} ${FOBJ} -o ${NAME}

%.o: %.cpp
	${CC} ${FLAGS} -c $< -o $@

clean:
	${RM} ${FOBJ}
fclean: clean
	${RM} ${NAME}
re: fclean all