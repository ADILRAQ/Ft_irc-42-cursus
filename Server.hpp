/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:48:32 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/25 15:50:00 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

#define SIZE			512
#define BACKLOG			10
#define BUFFER_SIZE		2028

#define ANSI_COLOR_RED "\033[1;31m"
#define ANSI_COLOR_GREEN "\033[1;32m"
#define ANSI_COLOR_YELLOW "\033[1;33m"
#define ANSI_COLOR_RESET "\033[0m"

typedef struct addrinfo			Addrinfo;
typedef struct pollfd			Pollfd;
typedef struct sockaddr_storage	SStorage;
typedef struct sockaddr_in		Sockaddr_in;
typedef struct hostent			Hostent;

class Server {
	private:
		std::vector<Pollfd>			Sockets;
		std::vector<std::string>	Request;
		Addrinfo					*Address;
		Server(void);
		Server(Server const &obj);
		Server	&operator = (Server const &source);
		void	NonBlockMode(void);

	public:
		Server(std::string const &port);
		~Server(void);
		int				operator [] (unsigned int i);
		short			operator [] (int i);
		std::string		&operator [] (long i);
		void			Revents(void);
		void			SBind(void);
		void			SListen(void);
		int				getSize(void) const;
		int				SPoll(void);
		void			SAccept(void);
		void			SClose(int i);
};
