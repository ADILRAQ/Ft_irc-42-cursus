/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:26 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/22 11:44:27 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::KICK()
{
    // the reason to kick, don't forget to add
    if (data.second.size() != 2)
        throw "461\n";
    
    unsigned int    ChannelIndex;
    vector<Chan>    CurrentChannels = Channel::getChannel();

    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0]);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, true);
        memberInfo& keep = CurrentChannels[ChannelIndex].getMembers();
        if (keep.find(data.second[1]) == keep.end())
            throw runtime_error("ERR_USERNOTINCHANNEL\n");
    }
    catch (const exception & e)
    {
        std::cerr << e.what();
        return ;
    }
    CurrentChannels[ChannelIndex].removeMember(data.second[1]);
            /******/
            std::cout << "---------- KICK --------------\n";
             memberInfo& keep = CurrentChannels[ChannelIndex].getMembers();
        memberInfo::iterator it = keep.begin();
        memberInfo::iterator ite = keep.end();
        for (memberInfo::iterator t = it; t != ite; t++)
        {
            std::cout << "first " << t->first << '\n';
        }
        std::cout << "-------------------------\n";
        /*****   */
}
