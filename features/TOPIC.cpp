/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:42 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/27 19:48:09 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::TOPIC()
{
    string& nick = Client::getClient()[CurrentClientFD].second.first;
    unsigned int ChannelIndex, sz = checkTopic(data.second, nick);
    vector<Chan>    CurrentChannels = Channel::getChannel();
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
        runtime_error(e.what());
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
        _send(CurrentClientFD, ":" + nick + "!"+ Client::getClient()[CurrentClientFD].second.second + "@localhost TOPIC " + data.second[0] + data.second[1] + "\r\n");
    }
}
