
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 17:50:29 by araqioui          #+#    #+#              #
#    Updated: 2023/11/25 17:51:01 by araqioui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ircserv

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

FILES = IRC Server startServer Channel Client features/Cmd features/CmdHelper features/INVITE features/JOIN \
		features/KICK features/MODE features/NICK features/PASS features/QUIT features/TOPIC features/USER Bot

HEADERS = MainHeader.hpp Server.hpp features/cmd.hpp Client.hpp Channel.hpp

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
