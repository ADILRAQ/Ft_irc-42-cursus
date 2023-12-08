/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:26 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/08 14:59:08 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::KICK()
{
    string& nick = Client::getClient()[CurrentClientFD].second.first;
    unsigned int sz = data.second.size();
    if (sz != 2 && sz != 3)
        throw runtime_error(": 461 " + nick + " :KICK Not enough parameters\r\n");
    if (sz == 3 && ValidString(data.second[2], 0) < 0)
        throw runtime_error(": 461 " + nick + " :Non valid character(s)\r\n");

    unsigned int    ChannelIndex;
    vector<Chan>&    CurrentChannels = Channel::getChannel();
    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], nick);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, true);
        memberInfo& keep = CurrentChannels[ChannelIndex].getMembers();
        if (keep.find(data.second[1]) == keep.end())
            throw runtime_error(": 441 " + data.second[1] + " " + data.second[0] + " :They aren't on that channel\r\n");
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

    CurrentChannels[ChannelIndex].removeClient(data.second[1]);
}
