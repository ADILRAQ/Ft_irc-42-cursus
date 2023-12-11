/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:50:49 by araqioui          #+#    #+#             */
/*   Updated: 2023/12/11 11:17:41 by fraqioui         ###   ########.fr       */
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
	hints.ai_flags = AI_PASSIVE;

	if ((error = getaddrinfo(NULL, port.c_str(), &hints, &Address)))
	{
		std::cout << COLOR_RED << gai_strerror(error) << COLOR_RESET << std::endl;
		throw (-1);
	}
	help.fd = socket(Address->ai_family, Address->ai_socktype, Address->ai_protocol);
	if (help.fd < 0)
	{
		perror(COLOR_RED "Socket " COLOR_RESET);
		throw -1;
	}
	Sockaddr_in	*ptr = (Sockaddr_in *)Address->ai_addr;
	std::cout << COLOR_GREEN << "MainSocket: " << help.fd << "  " << inet_ntoa(ptr->sin_addr) << ":" << ntohs(ptr->sin_port) << COLOR_RESET << std::endl;
	std::cout << std::endl;
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
		perror(COLOR_RED "fcntl " COLOR_RESET);
		throw (-1);
	}
}

int Server::getFD(size_t i)
{
	return (Sockets[i].fd);
}

short	Server::getRevents(size_t i)
{
	return (Sockets[i].revents);
}

std::string	&Server::getRequest(size_t i)
{
	return (Request[i]);
}

size_t	Server::getSize(void) const
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
		perror(COLOR_RED "Bind " COLOR_RESET);
		throw (-1);
	}
}

void	Server::SListen(void)
{
	if (listen(Sockets[0].fd, SOMAXCONN) < 0)
	{
		perror(COLOR_RED "Listen " COLOR_RESET);
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
	sockaddr_in	inData;
	socklen_t	sizeStruct = sizeof(SStorage);
	int			newSocket;
	Pollfd		help;

	if (Sockets.size() <= SIZE)
	{
		newSocket = accept(Sockets[0].fd, reinterpret_cast<struct sockaddr *>(&inData), &sizeStruct);
		if (newSocket < 0)
		{
			perror(COLOR_RED "Accept " COLOR_RESET);
			throw (-1);
		}
		help.fd = newSocket;
		std::cout << COLOR_GREEN << "NewSocket: " << help.fd << "   IP: " << inet_ntoa(inData.sin_addr) << ":" << ntohs(inData.sin_port) << COLOR_RESET << std::endl;
		std::string	IPaddr(inet_ntoa(inData.sin_addr));
		help.events = POLLIN;
		help.revents = 0;
		Sockets.push_back(help);
		SockAddrInfo.push_back(IPaddr);
		Request.push_back("");
	}
	else
		std::cout << "Connection Not Accepeted!" << std::endl;
}

void	Server::SClose(size_t i)
{
	std::cout << COLOR_RED << "Close: " << Sockets[i].fd << "   IP: " << SockAddrInfo[i - 1] << COLOR_RESET << std::endl;
	close(Sockets[i].fd);
	Sockets.erase(Sockets.begin() + i);
	SockAddrInfo.erase(SockAddrInfo.begin() + i - 1);
	Request.erase(Request.begin() + i);
}

std::string const	&Server::getIP(size_t i) const
{
	return (SockAddrInfo[i - 1]);
}
