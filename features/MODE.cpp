/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:29 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/27 11:34:49 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void announceMode(const int &fd, const string & nick, vector<string> & vc)
{
    if (vc.size() == 3)
        _send(fd, ":ircserv 324 " + nick + " " + vc[0] + " " + vc[1] + " " + vc[2] + "\r\n");
    else
        _send(fd, ":ircserv 324 " + nick + " " + vc[0] + " " + vc[1] + "\r\n");
}

void    Cmd::MODE()
{
    unsigned int    ChannelIndex;
    char            FlaG;
    bool            Set;
    vector<Chan> CurrentChannels = Channel::getChannel();

    try
    {
        FlaG = checkMode(data.second, Client::getClient()[CurrentClientFD].second.first);
        if (data.second[1][0] == '+')
            Set = true;
        else
            Set = false;
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], Client::getClient()[CurrentClientFD].second.first);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, true);
    }
    catch (const exception & e)
    {
        throw runtime_error(e.what());
    }

    switch (FlaG)
    {
        case 'i':
            Channel::getChannel()[ChannelIndex].setModesStat(FlaG, Set, "");
            break;
        case 't':
            Channel::getChannel()[ChannelIndex].setModesStat(FlaG, Set, "");
            break;
        case 'k':
            Channel::getChannel()[ChannelIndex].setModesStat(FlaG, Set, data.second[2]);
            break;
        case 'o':
            try
            {
                IsUserInChannel(Channel::getChannel()[ChannelIndex], data.second[2], true);
            }
            catch (const exception & e)
            {
                throw runtime_error(e.what());
                return ;
            }
            Channel::getChannel()[ChannelIndex].setChannelOper(data.second[2], Set);
            break;
        case 'l':
            Channel::getChannel()[ChannelIndex].setModesStat(FlaG, Set, "");
            Channel::getChannel()[ChannelIndex].setChannelLimit(atoi((data.second[2]).c_str()));
            break;
    }
    announceMode(CurrentClientFD, Client::getClient()[CurrentClientFD].second.first, data.second);
}
