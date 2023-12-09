/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:42 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/09 10:16:22 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::TOPIC()
{
    string& nick = Client::getClient()[CurrentClientFD].second.first;
    unsigned int ChannelIndex, sz = checkTopic(data.second, nick);
    vector<Chan>&    CurrentChannels = Channel::getChannel();
    bool IsOper;

    try   
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], nick);
        if ((CurrentChannels[ChannelIndex].getModes())['t'].first)
            IsOper = true;
        else
            IsOper = false;
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, IsOper);
    }
    catch (const exception & e)
    {
        throw runtime_error(e.what());
    }

    if (sz == 1)
    {
        if ((CurrentChannels[ChannelIndex].getTopic()).empty())
            throw runtime_error(": 331 " + nick + " " + data.second[0] + " :No topic is set\r\n");
        else
            _send(CurrentClientFD, ": 332 " + nick + " " + data.second[0] + " :" + CurrentChannels[ChannelIndex].getTopic() + "\r\n");
    }
    else
    {
        if (CurrentChannels[ChannelIndex].getModes()['t'].first && !CurrentChannels[ChannelIndex].getMembers()[nick].second)
            throw runtime_error(": 482 " + nick + " " + data.second[0] + " :You're not channel operator\r\n");
        Channel::getChannel()[ChannelIndex].setTopic(data.second[1]);
		map<int, string> var = CurrentChannels[ChannelIndex].getMembersFromFD();
		map<int, string>::iterator it = var.begin();
		map<int, string>::iterator ite = var.end();

		for (map<int, string>::iterator t = it; t != ite; t++)
			serverReplyFormat(t->first, Client::getClient()[CurrentClientFD].second, data);
    }
}
