/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:54:53 by araqioui          #+#    #+#             */
/*   Updated: 2023/12/03 14:00:05 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainHeader.hpp"

void	startServer(char *port, char *pswd)
{
	Server	serv(port);
	char	req[BUFFER_SIZE];
	int		check, status, flg = 0;

	serv.SBind();
	serv.SListen();
	while (true)
	{
		// check = 0;
		if ((check = serv.SPoll()) == -1)
		{
			perror(COLOR_RED "Poll " COLOR_RESET);
			throw (-1);
		}
		else if (check)
		{
			for (size_t i = 0; i < serv.getSize(); i++)
			{
				if (i == 0 && serv.getRevents(i) & POLLIN)
					serv.SAccept();
				else if (serv.getRevents(i) & POLLIN)
				{
					memset(req, '\0', BUFFER_SIZE);
					if ((status = recv(serv.getFD(i), req, BUFFER_SIZE, 0)) == -1)
					{
						perror(COLOR_RED "RECV " COLOR_RESET);
						throw (-1);
					}
					else if (status)
					{
						req[status] = '\0';
						std::string	message(req);
						serv.getRequest(i) += message;
						if (serv.getRequest(i)[0] != '\n' && *(serv.getRequest(i).end() - 1) == '\n')
						{
							cout << COLOR_YELLOW << "INCOMIG DATA: " << serv.getRequest(i) << COLOR_RESET << endl;
							std::istringstream	CompleteMes(serv.getRequest(i));
							std::string			line;
							while (getline(CompleteMes, line))
							{
								std::cout << COLOR_GREEN << "\tLINE: " << line  << "  " << flg << COLOR_RESET << std::endl;
								if (line.substr(0, line.find(' ')) == "QUIT")
								{
									status = 0; // To enter the next condition
									break ;
								}
								placeCmds(serv.getRequest(i), serv.getFD(i), pswd, serv.getIP(i));
							}
							serv.getRequest(i).clear();
							serv.getRequest(i).resize(0);
						}
					}
					if (!status)
					{
						// To Delete the user
						placeCmds("", serv.getFD(i), pswd, "");
						serv.SClose(i);
					}
				}
				flg++;
			}
		}
	}
}
