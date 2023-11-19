/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:54:53 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/19 10:50:23 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainHeader.hpp"

void	startServer(char *port, char *pswd)
{
	Server	serv(port);
	char	req[REQUEST_SIZE];
	int		check;
	int		status;
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
					std::cout << "Ready to be read!" << std::endl;
					memset(req, '\0', REQUEST_SIZE);
					if ((status = recv(serv[(unsigned int)i], req, REQUEST_SIZE, 0)) == -1)
					{
						perror("RECV ");
						throw (-1);
					}
					else if (status)
					{
						std::string	message(req);
						serv[(long)i] += message;
						if (serv[(long)i][0] != '\n' && serv[(long)i].find('\n') != std::string::npos)
						{
							std::cout << "\t-->" << serv[(long)i] << std::endl;
							// TODO: Send serv[(long)i] to get parsed
							// put you function here......
							serv[(long)i].clear();
							serv[(long)i].resize(0);
						}
					}
					else
					{
						std::cout << "Closed: " << serv[(unsigned int)i] << std::endl;
						serv.SClose(i);
					}
				}
			}
		}
	}
}
