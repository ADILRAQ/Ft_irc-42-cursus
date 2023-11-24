/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:29 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 10:12:10 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::MODE()
{
    unsigned int    ChannelIndex;
    char            FlaG;
    bool            Set;
    vector<Chan> CurrentChannels = Channel::getChannel();

    try
    {
        FlaG = checkMode(data.second, Client::getClient()[CurrentClientFD].first);
        if (data.second[1][0] == '+')
            Set = true;
        else
            Set = false;
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0]);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, true);
    }
    catch (const exception & e)
    {
        std::cerr << e.what();
    }

    switch (FlaG)
    {
        case 'i':
            CurrentChannels[ChannelIndex].setModesStat(FlaG, Set, "");
            break;
        case 't':
            CurrentChannels[ChannelIndex].setModesStat(FlaG, Set, "");
            break;
        case 'k':
            CurrentChannels[ChannelIndex].setModesStat(FlaG, Set, data.second[2]);
            break;
        case 'o':
        // still need work
            IsUserInChannel(CurrentChannels[ChannelIndex], data.second[2]);
            CurrentChannels[ChannelIndex].setModesStat(FlaG, Set, data.second[2]);
            break;
        case 'l':
            CurrentChannels[ChannelIndex].setModesStat(FlaG, Set, "");
            CurrentChannels[ChannelIndex].setChannelLimit(atoi((data.second[2]).c_str()));
            break;
    }
}
