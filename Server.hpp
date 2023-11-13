/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:48:32 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/13 18:04:26 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <poll.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

#define SIZE	512
#define BACKLOG	10

typedef struct addrinfo			Addrinfo;
typedef struct pollfd			Pollfd;
typedef struct sockaddr_storage	SStorage;

class Server {
	private:
		std::vector<Pollfd>		Sockets;
		Addrinfo				*address;
		int						SSize;
		Server(void);
		Server(Server const &obj);
		Server	&operator = (Server const &source);
		void	Initialize(void);
		void	NonBlockMode(void);

	public:
		Server(std::string const &port);
		~Server(void);
		int				operator [] (unsigned int i);
		short			operator [] (int i);
		void			Revents(void);
		// Addrinfo const	&GetAddrInfo(void) const;
		void			SBind(void);
		void			SListen(void);
		int				getSize(void) const;
		int				SPoll(void);
		void			SAccept(void);
};
