/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:42 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/25 18:19:38 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::TOPIC()
{
    unsigned int ChannelIndex, sz = checkTopic(data.second, Client::getClient()[CurrentClientFD].second.first);
    vector<Chan>    CurrentChannels = Channel::getChannel();
    bool IsOper;

    try   
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], Client::getClient()[CurrentClientFD].second.first);
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
            throw runtime_error(":ircserv 331 " + CurrentChannels[ChannelIndex].getMembersFromFD()[CurrentClientFD] + " :No topic is set\r\n");
        else
            _send(CurrentClientFD, CurrentChannels[ChannelIndex].getTopic() + "\r\n");
    }
    else
        Channel::getChannel()[ChannelIndex].setTopic(data.second[1]);
}
