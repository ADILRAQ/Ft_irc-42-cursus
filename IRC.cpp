/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:06:32 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/15 09:58:23 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainHeader.hpp"

static int	Port(char *str)
{
	std::stringstream	ss(str);
	std::string			port;
	int					i = -1;

	ss >> port;
	std::cout << "Port__:" << port << std::endl;
	if (port.empty())
		return (0);
	while (port[++i])
		if (!isdigit(port[i]))
			return (0);
	if (std::stoi(port) < 1024 || std::stoi(port) > 65535)
		return (0);
	return (1);
}

static int	Password(char *str)
{
	int	i = -1;

	while (str[++i])
		if (!isalpha(str[i]))
			return (0);
	return (1);
}

void	signalHandler(int sig)
{
	if (sig == SIGINT)
	{
		std::cout << "\rExit successfully : Receiving SIGINT..." << std::endl;
		exit(EXIT_SUCCESS);
	}
	if (sig == SIGQUIT)
	{
		std::cout << "\rExit unsuccessfully : Receiving SIGQUIT..." << std::endl;
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		if (Port(av[1]) && Password(av[2]))
		{
			try {
				signal(SIGINT, signalHandler);
				signal(SIGQUIT, signalHandler);
				startServer(av[1], av[2]);
			}
			catch(int){}
		}
		else
			std::cout << "Error: Bad port format" << std::endl;
	}
	else
		std::cout << "Error: NB of args" << std::endl;
	return (1);
}
