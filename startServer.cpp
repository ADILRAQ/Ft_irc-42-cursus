/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:54:53 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/26 09:49:20 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainHeader.hpp"

void	startServer(char *port, char *pswd)
{
	Server	serv(port);
	char	req[BUFFER_SIZE];
	int		check;
	int		status;
	// (void)pswd;

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
					memset(req, '\0', BUFFER_SIZE);
					if ((status = recv(serv[(unsigned int)i], req, BUFFER_SIZE, 0)) == -1)
					{
						perror("RECV ");
						throw (-1);
					}
					else if (status)
					{
						string	message(req);
						serv[(long)i] += message;
						if (serv[(long)i][0] != '\n' && serv[(long)i].find('\n') != string::npos)
						{
							cout << "\t-->" << serv[(long)i] << endl;
							// TODO: Send serv[(long)i] to get parsed
							// put you function here......
							placeCmds(serv[(long)i], serv[(unsigned int)i], pswd);
							// std::string respond = "PRIVMSG ARAQ : ";
							// respond += Bot(serv[(long)i]) + "\r\n";
							// send(serv[(unsigned int)i], respond.c_str(), respond.length(), 0);
							serv[(long)i].clear();
							serv[(long)i].resize(0);
						}
					}
					else
					{
						placeCmds("", serv[(unsigned int)i]);
						cout << "Closed: " << serv[(unsigned int)i] << endl;
						serv.SClose(i);
					}
				}
			}
		}
	}
}
