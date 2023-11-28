/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:50:49 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/26 18:06:20 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string const &port) : Address(NULL)
{
	Addrinfo	hints;
	Pollfd		help;
	int			error;

	memset(&hints, '\0', sizeof(struct addrinfo));

	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((error = getaddrinfo("localhost", port.c_str(), &hints, &Address)))
	{
		std::cout << gai_strerror(error) << std::endl;
		throw (-1);
	}
	help.fd = socket(Address->ai_family, Address->ai_socktype, Address->ai_protocol);
	if (help.fd < 0)
	{
		perror("Socket ");
		throw -1;
	}
	std::cout << "MainSocket: " << help.fd << std::endl;
	help.events = POLLIN;
	help.revents = 0;
	Sockets.push_back(help);
	Request.push_back("");
	this->NonBlockMode();
}

Server::~Server(void)
{
	size_t	i = 0;

	while (i < Sockets.size())
		close(Sockets[i++].fd);
	if (Address)
		freeaddrinfo(Address);
}

void	Server::Revents(void)
{
	size_t	i = 0;

	while (i < Sockets.size())
		Sockets[i++].revents = 0;
}

void	Server::NonBlockMode(void)
{
	if (fcntl(Sockets[0].fd, F_SETFL, O_NONBLOCK) == -1)
	{
		perror("fcntl ");
		throw (-1);
	}
}

int Server::operator [] (unsigned int i)
{
	return (Sockets[i].fd);
}

short	Server::operator [] (int i)
{
	return (Sockets[i].revents);
}

std::string	&Server::operator [] (long i)
{
	return (Request[i]);
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

	if (bind(Sockets[0].fd, Address->ai_addr, Address->ai_addrlen) < 0)
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
	return (poll(Sockets.data(), Sockets.size(), -1));
}

void	Server::SAccept(void)
{
	SStorage	inData;
	socklen_t	sizeStruct = sizeof(SStorage);
	int			newSocket;
	Pollfd		help;

	if (Sockets.size() <= SIZE)
	{
		newSocket = accept(Sockets[0].fd, (struct sockaddr *)&inData, &sizeStruct);
		if (newSocket < 0)
		{
			perror("Accept ");
			throw (-1);
		}
		help.fd = newSocket;
		Sockaddr_in	PrintIP;
		memcpy(&PrintIP.sin_addr, &inData, inData.ss_len);
		std::cout << "NewSocket: " << help.fd << "   IP: " << inet_ntoa(PrintIP.sin_addr) << std::endl;
		std::stringstream	IPaddr(inet_ntoa(PrintIP.sin_addr));
		help.events = POLLIN;
		help.revents = 0;
		Sockets.push_back(help);
		SockAddrInfo.push_back(IPaddr.str());
		Request.push_back("");
	}
	else
		std::cout << "Connection Not Accepeted!" << std::endl;
}

void	Server::SClose(int i)
{
	std::cout << "Close: " << Sockets[i].fd << "   IP: " << SockAddrInfo[i - 1] << std::endl;
	close(Sockets[i].fd);
	Sockets.erase(Sockets.begin() + i);
	SockAddrInfo.erase(SockAddrInfo.begin() + i - 1);
	Request.erase(Request.begin() + i);
}
