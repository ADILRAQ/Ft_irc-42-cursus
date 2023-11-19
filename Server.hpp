/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:48:32 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/19 10:05:39 by araqioui         ###   ########.fr       */
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
#define REQUEST_SIZE	1024

typedef struct addrinfo			Addrinfo;
typedef struct pollfd			Pollfd;
typedef struct sockaddr_storage	SStorage;

class Server {
	private:
		std::vector<Pollfd>			Sockets;
		std::vector<std::string>	Request;
		Addrinfo					*address;
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
