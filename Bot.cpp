/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:17:22 by araqioui          #+#    #+#             */
/*   Updated: 2023/12/02 10:01:22 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainHeader.hpp"

const char	*API_HOST = "api.weatherapi.com";
const char	*API_PATH = "/v1/current.json";
const char	*API_KEY = "bd9f83a56f2b46b6ae3142327232411";

static std::string const	getCityName(std::string cmdLine)
{
	std::string	request;
	int			i = 0;

	while (cmdLine[i] != ' ')
		i++;
	while (cmdLine[i] == ' ')
		i++;
	if (cmdLine[i] == '\n' || cmdLine[i] == '\r')
	{
		return ("");
	}
	while (cmdLine[i] != '\n' && cmdLine[i] != '\r')
	{
		if (cmdLine[i] == ' ')
		{
			while (cmdLine[i] == ' ')
				i++;
			if (cmdLine[i] == '\n' || cmdLine[i] == '\r')
				break ;
			else
				request += "%20";
		}
		else
			request += cmdLine[i++];
	}
	return (request);
}

static std::string const	makeRequest(std::string const &cityName)
{
	std::ostringstream	request;

	if (cityName.empty())
		return ("");
	std::cout << COLOR_YELLOW << "City: " << cityName << COLOR_RESET << std::endl;

	request << "GET " << API_PATH << "?key=" << API_KEY << "&q=" << cityName << " HTTP/1.1\r\n";
    request << "Host: " << API_HOST << "\r\n";
    request << "Connection: close\r\n\r\n";

	return (request.str());
}

static bool	HTTPcode(std::string const &respond)
{
	std::string	line = respond.substr(0, respond.find('\r'));

	return (line.find("200") != std::string::npos);
}

static std::string	getValue(std::string const &request, std::string const &name)
{
	size_t	nameId = 0, quoteId = 0;

	nameId = request.find(name) + name.length();

	nameId += (name == "\"temp_c\":") ? 0 : 1;
	while (request[nameId + quoteId] != ',' && request[nameId + quoteId] != '\"')
		quoteId++;

	std::string	value = request.substr(nameId, quoteId);

	return (value);
}

void	Bot(std::string const &cmdLine)
{
	Hostent		*hostInfo;
	Sockaddr_in	server;
	int			hostSocket = 0;
	std::string	request, help, message = "";
	char		respond[BUFFER_SIZE];
	ssize_t		len;

	request = makeRequest(getCityName(cmdLine));

	if (!request.empty())
	{
		if ((hostInfo = gethostbyname(API_HOST)) == NULL)
			return (perror(COLOR_RED "Gethostbyname " COLOR_RESET));

		if ((hostSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
			return (perror(COLOR_RED "HostSocket " COLOR_RESET));

		memset(&server, '\0', sizeof(Sockaddr_in));
		server.sin_family = AF_INET;
		server.sin_port = htons(80);
		memcpy(&server.sin_addr, hostInfo->h_addr_list[0], hostInfo->h_length);

		if (connect(hostSocket, (struct sockaddr *)&server, sizeof(server)) == -1)
			return (perror(COLOR_RED "Connect " COLOR_RESET));

		if (send(hostSocket, request.c_str(), request.length(), 0) == -1)
			return (perror(COLOR_RED "SendHost " COLOR_RESET));

		while ((len = recv(hostSocket, respond, BUFFER_SIZE - 1, 0)) > 0)
		{
			respond[len] = '\0';
			std::string newstring(respond);
			help += newstring;
		}
		if (len < 0)
			return (perror(COLOR_RED "HostRecv " COLOR_RESET));

		if (HTTPcode(help))
		{
			message = getValue(help, "\"name\":") + ", " + getValue(help, "\"country\":") + "  " + getValue(help, "\"localtime\":");
			message += "  ==>  " + getValue(help, "\"temp_c\":") + "°C   " + getValue(help, "\"text\":");
		}
		else
			message = getValue(help, "\"message\":");
		std::cout << COLOR_GREEN << message << COLOR_RESET << std::endl;
		close(hostSocket);
	}
};
