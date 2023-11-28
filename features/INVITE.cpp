/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:21 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/28 14:25:05 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::INVITE()
{
		unsigned int    ChannelIndex;
		vector<Chan> CurrentChannels = Channel::getChannel();
		ClientInfos CurrentClients = Client::getClient();
		string &nick = CurrentClients[CurrentClientFD].second.first;

		if (data.second.size() != 2)
				throw runtime_error(": 461 " + nick + " :INVITE Not enough parameters\r\n");

		try
		{
				ChannelIndex = ChannelExist(CurrentChannels, data.second[1], nick);
				IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, false);
				if (CurrentClients.find(CurrentClientFD) == CurrentClients.end())
					throw runtime_error(": 401 " + data.second[0] + " :No such nick\r\n");
				IsUserInChannel(CurrentChannels[ChannelIndex], data.second[0], false);
		}
		catch (const exception & e)
		{
				throw runtime_error(e.what());
		}
		if (CurrentChannels[ChannelIndex].getModes()['i'].first && !CurrentChannels[ChannelIndex].getMembers()[nick].second)
			throw runtime_error(": 482 " + nick + " :You're not channel operator\r\n");

		Channel::getChannel()[ChannelIndex].setInviteD(data.second[0]);

		ClientInfos clientFD = Client::getClient();
		ClientInfos::iterator it = clientFD.begin();
		ClientInfos::iterator ite = clientFD.end();
		ClientInfos::iterator t = it;
		for (; t != ite; t++)
			if (data.second[0] == t->second.second.first)
				break;
		serverReplyFormat(t->first, CurrentClients[CurrentClientFD].second, data, 0);
}