/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:54:53 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/29 16:10:04 by araqioui         ###   ########.fr       */
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
					memset(req, '\0', BUFFER_SIZE);
					if ((status = recv(serv[(unsigned int)i], req, BUFFER_SIZE, 0)) == -1)
					{
						perror("RECV ");
						throw (-1);
					}
					else if (status)
					{
						req[status] = '\0';
						std::string	message(req);
						serv[(long)i] += message;
						if (serv[(long)i][0] != '\n' && serv[(long)i].find('\n') != string::npos)
						{
							cout << COLOR_YELLOW << "INCOMIG DATA: " << serv[(long)i] << COLOR_RESET << endl;
							std::istringstream	iss(serv[(long)i]);
							std::string	word;

							iss >> word;

							// if (word == "BOT")
							// {
							// 	Bot(serv[(long)i]);
							// 	if (!mes.empty())
							// 		serv[(long)i] = "PRIVMSG :" + mes;
							// 	else
							// 		serv[(long)i] = "";
							// }
							// if (!serv[(long)i].empty())
							// {
								placeCmds(serv[(long)i], serv[(unsigned int)i], pswd);

								if (word == "QUIT")
									serv.SClose(i);
								serv[(long)i].clear();
								serv[(long)i].resize(0);
							// }
						}
					}
					else
					{
						// To Delete the user
						placeCmds("", serv[(unsigned int)i], pswd);
						serv.SClose(i);
					}
				}
			}
		}
	}
}
