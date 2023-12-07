/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:29:20 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/07 09:29:52 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"
// fix double message
void    Cmd::PRIVMSG()
{
	string& nick = Client::getClient()[CurrentClientFD].second.first;
	unsigned int sz = data.second.size();
	if (sz != 2)
		throw runtime_error(": 461 " + nick + " :PRIVMSG Not enough parameters\r\n");
	if (ValidString(data.second[1], 0) < 0)
		throw runtime_error(": 461 " + nick + " :Non valid character(s)\r\n");

	if (data.second[0][0] == '#')
	{
		unsigned int    ChannelIndex;
		vector<Chan>    CurrentChannels = Channel::getChannel();
		try
		{
			ChannelIndex = ChannelExist(CurrentChannels, data.second[0], nick);
			IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, false);
		}
		catch (const exception & e)
		{
			throw runtime_error(e.what());
		}
		map<int, string> var = CurrentChannels[ChannelIndex].getMembersFromFD();
		map<int, string>::iterator it = var.begin();
		map<int, string>::iterator ite = var.end();

		for (map<int, string>::iterator t = it; t != ite; t++)
			serverReplyFormat(t->first, Client::getClient()[CurrentClientFD].second, data);
		return ;
	}
	ClientInfos clientFD = Client::getClient();
	ClientInfos::iterator it = clientFD.begin();
	ClientInfos::iterator ite = clientFD.end();
	ClientInfos::iterator t = it;
	for (; t != ite; t++)
	{
		if (data.second[0] == t->second.second.first)
		{
			serverReplyFormat(t->first, Client::getClient()[CurrentClientFD].second, data);
			return ;
		}
	}
	throw runtime_error(": 401 " + data.second[0] + " :No such nick\r\n");
}
