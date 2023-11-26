/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:26 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/25 16:36:28 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::KICK()
{
    // the reason to kick, don't forget to add
    if (data.second.size() != 2)
        throw runtime_error(":ircserv 461 " + Client::getClient()[CurrentClientFD].second.first + " :Not enough parameters\r\n");

    unsigned int    ChannelIndex;
    vector<Chan>    CurrentChannels = Channel::getChannel();
    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[1], Client::getClient()[CurrentClientFD].second.first);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, true);
        memberInfo& keep = CurrentChannels[ChannelIndex].getMembers();
        if (keep.find(data.second[1]) == keep.end())
            throw runtime_error(":ircserv 441 " + data.second[1] + " :They aren't on that channel\r\n");
    }
    catch (const exception & e)
    {
        throw runtime_error(e.what());
    }

    Channel::getChannel()[ChannelIndex].removeClient(data.second[1]);
            /******/
            cout << "---------- KICK " << Channel::getChannel()[ChannelIndex].getChannelName()<< "--------------\n";
             memberInfo& sv = Channel::getChannel()[ChannelIndex].getMembers();
        memberInfo::iterator it = sv.begin();
        memberInfo::iterator ite = sv.end();
        for (memberInfo::iterator t = it; t != ite; t++)
        {
            cout << "first " << t->first << "  " << t->second.first<< '\n';
        }
        cout << "-------------------------\n";
        /*****   */
}
