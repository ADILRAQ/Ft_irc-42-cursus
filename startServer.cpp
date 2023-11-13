/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:54:53 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/13 18:59:00 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainHeader.hpp"

void	startServer(char *port, char *pswd)
{
	Server	serv(port);
	int		check;
	(void)pswd;

	serv.SBind();
	serv.SListen();
	while (true)
	{
		check = 0;
		if ((check = serv.SPoll()) == -1)
		{
			perror("Poll ");
			throw (-1);
		}
		else if (check)
		{
			for (int i = 0; i < serv.getSize(); i++)
			{
				if (i == 0 && serv[(short)0] & POLLIN)
					serv.SAccept();
				else if (serv[(short)i] & POLLIN)
				{
					// TODO: Read data an Parse
					char	buff[100];
					memset(buff, '\0', 100);
					std::cout << "Ready to be read!" << std::endl;
					std::cout << "REC: " << recv((int)serv[(unsigned int)i], buff, 100, 0) << std::endl;
					// perror("--> ");
					std::cout << "InDATA: " << buff << std::endl;
					throw (-1);
				}
			}
		}
	}
}
