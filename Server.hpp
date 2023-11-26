/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:48:32 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/24 13:39:53 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

#define SIZE			512
#define BACKLOG			10
#define REQUEST_SIZE	1024

typedef struct addrinfo			Addrinfo;
typedef struct pollfd			Pollfd;
typedef struct sockaddr_storage	SStorage;

class Server {
	private:
		vector<Pollfd>			Sockets;
		vector<string>	Request;
		Addrinfo					*address;
		Server(void);
		Server(Server const &obj);
		Server	&operator = (Server const &source);
		void	NonBlockMode(void);

	public:
		Server(string const &port);
		~Server(void);
		int				operator [] (unsigned int i);
		short			operator [] (int i);
		string		&operator [] (long i);
		void			Revents(void);
		void			SBind(void);
		void			SListen(void);
		int				getSize(void) const;
		int				SPoll(void);
		void			SAccept(void);
		void			SClose(int i);
};
