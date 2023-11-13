/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:50:49 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/13 18:13:57 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string const &port) : address(NULL), SSize(1)
{
	Addrinfo	hints;
	int			error;
	Pollfd		help;

	// this->Initialize();
	memset(&hints, '\0', sizeof(struct addrinfo));

	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((error = getaddrinfo("localhost", port.c_str(), &hints, &address)))
	{
		std::cout << gai_strerror(error) << std::endl;
		throw (-1);
	}
	help.fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (help.fd < 0)
	{
		perror("Socket ");
		throw -1;
	}
	std::cout << "MainSocket: " << help.fd << std::endl;
	help.events = POLLIN;
	help.revents = 0;
	Sockets.push_back(help);
	this->NonBlockMode();
}

Server::~Server(void)
{
	size_t	i = 0;

	while (i < Sockets.size())
		close(Sockets[i++].fd);
	if (address)
		freeaddrinfo(address);
}

void	Server::Revents(void)
{
	size_t	i = 0;

	while (i < Sockets.size())
		Sockets[i++].revents = 0;
}

void	Server::NonBlockMode(void)
{
	int	flag;

	if ((flag = fcntl(Sockets[0].fd, F_GETFL, 0)) == -1)
	{
		perror("fcntl1 ");
		throw (-1);
	}
	if (fcntl(Sockets[0].fd, F_SETFL, flag | O_NONBLOCK) == -1)
	{
		perror("fcntl2 ");
		throw (-1);
	}
}

int Server::operator [] (unsigned int i)
{
	std::cout << "HII: " << Sockets[i].fd << std::endl;
	return (Sockets[i].fd);
}

short	Server::operator [] (int i)
{
	return (Sockets[i].revents);
}

int	Server::getSize(void) const
{
	return (Sockets.size());
}

void	Server::SBind(void)
{
	int	reuseaddr = 1;

	if (setsockopt(Sockets[0].fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)))
		std::cout << "RESUSE: " << strerror(errno) << std::endl;

	if (bind(Sockets[0].fd, address->ai_addr, address->ai_addrlen) < 0)
	{
		perror("Bind ");
		throw (-1);
	}
}

void	Server::SListen(void)
{
	if (listen(Sockets[0].fd, BACKLOG) < 0)
	{
		perror("Listen ");
		throw (-1);
	}
}

int	Server::SPoll(void)
{
	this->Revents();
	return (poll(Sockets.data(), Sockets.size(), 0));
}

void	Server::SAccept(void)
{
	SStorage	inData;
	socklen_t	sizeStruct = sizeof(SStorage);
	int			newSocket;
	Pollfd		help;

	/**
		*! Be carefule
	*/
	if (Sockets.size() <= SIZE)
	{
		std::cout << "new connection accepted!" << std::endl;
		// TODO: We can Store new Connection's data
		newSocket = accept(Sockets[0].fd, (struct sockaddr *)&inData, &sizeStruct);
		if (newSocket < 0)
		{
			perror("Accept ");
			throw (-1);
		}
		help.fd = newSocket;
		std::cout << "NewSocket: " << help.fd << std::endl;
		help.events = POLLIN;
		help.revents = 0;
		Sockets.push_back(help);
	}
	else
		std::cout << "Connection Not Accepeted!" << std::endl;
}
