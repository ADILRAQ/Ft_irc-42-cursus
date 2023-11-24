/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:42 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 10:11:52 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::TOPIC()
{
    unsigned int ChannelIndex, sz = checkTopic(data.second, Client::getClient()[CurrentClientFD].first);
    vector<Chan>    CurrentChannels = Channel::getChannel();
    bool IsOper;

    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0]);
        if ((CurrentChannels[ChannelIndex].getModes())['t'].first)
            IsOper = true;
        else
            IsOper = false;
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, IsOper);
    }
    catch (const exception & e)
    {
        std::cerr << e.what();
    }

    if (sz == 1)
    {
        if ((CurrentChannels[ChannelIndex].getTopic()).empty())
            throw runtime_error("331 no topic is set\n");
        else
            std::cout << CurrentChannels[ChannelIndex].getTopic() << '\n';
    }
    else
        CurrentChannels[ChannelIndex].setTopic(data.second[1]);
}
