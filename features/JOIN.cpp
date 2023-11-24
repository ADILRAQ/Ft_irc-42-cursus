/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:23 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 09:58:41 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"
// check invite only
void    Cmd::JOIN()
{
    unsigned int sz;
    ClientInfos save = Client::getClient();

    try
    {
        sz = checkChannel(data.second, save[CurrentClientFD].first);
    }
    catch(const std::exception& e)
    {
        throw e;
    }

    vector<Chan> CurrentChannels = Channel::getChannel();
    unsigned int ChannelIndex;

    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0]);
        Chan keep = CurrentChannels[ChannelIndex];
        if ((keep.getModes())['l'].first && keep.getMembersFromFD().size() == keep.getLimit())
            throw runtime_error(": 471 " + save[CurrentClientFD].first + " :Channel is full\r\n");
    }
    catch (const exception & e)
    {
        if (sz != 1)
            throw runtime_error(": 461 " + save[CurrentClientFD].first + " :Not enough parameters\r\n");
        Chan obj(data.second[0], save[CurrentClientFD].first, CurrentClientFD);
        Channel::setChannel(obj);
        return ;
    }
    modeInfo& keep = CurrentChannels[ChannelIndex].getModes();
    if (sz == 2 && keep['k'].first == true && keep['k'].second != data.second[1])
        throw runtime_error("ERR_BADCHANNELKEY\n");
    else if (sz == 2 && keep['k'].first == false)
        throw runtime_error(": 461 " + save[CurrentClientFD].first + " :Not enough parameters\r\n");
    CurrentChannels[ChannelIndex].setMember(save[CurrentClientFD].first, CurrentClientFD);
                std::cout << "---------- KICK --------------\n";
        map<int, string>::iterator  it0 = CurrentChannels[ChannelIndex].getMembersFromFD().begin();
        map<int, string>::iterator  it0e = CurrentChannels[ChannelIndex].getMembersFromFD().end();
        for (map<int, string>::iterator  t0 = it0; t0 != it0e; t0++)
        {
            std::cout << "first " << t0->first << '\n';
        }
        std::cout << "-------------------------\n";
}
