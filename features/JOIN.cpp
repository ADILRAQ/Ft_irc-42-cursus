/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:23 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/26 14:08:08 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::JOIN()
{
    unsigned int sz;
    ClientInfos save = Client::getClient();

    try
    {
        sz = checkChannel(data.second, save[CurrentClientFD].second.first);
    }
    catch(const exception& e)
    {
        throw runtime_error(e.what());
    }

    vector<Chan> CurrentChannels = Channel::getChannel();
    unsigned int ChannelIndex;
    bool flg = 0;
    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], save[CurrentClientFD].second.first);
    }
    catch(const std::exception& e)
    {
        flg = 1;
    }

    if (flg)
    {
        if (sz != 1)
            throw runtime_error(": 461 " + save[CurrentClientFD].second.first + " :Not enough parameters\r\n");
        Chan obj(data.second[0], save[CurrentClientFD].second.first, CurrentClientFD);
        Channel::setChannel(obj);
        _send(CurrentClientFD, ":" + save[CurrentClientFD].second.first + "!~" + save[CurrentClientFD].second.second + "@" + "localhost" + " JOIN " + data.second[0] + "\r\n");
        _send(CurrentClientFD, ":ircserv MODE " + data.second[0] + " +o " + save[CurrentClientFD].second.first + "\r\n");
        _send(CurrentClientFD, "ircserv 353 " + save[CurrentClientFD].second.first + " = " + data.second[0] + " :@" + save[CurrentClientFD].second.first + "\r\n");
        _send(CurrentClientFD, "ircserv 366 " + save[CurrentClientFD].second.first + data.second[0] + " :End of /NAMES list.\r\n");
        return ;
    }

    try
    {
        Chan keep = CurrentChannels[ChannelIndex];
        if (keep.getModes()['i'].first)
            throw runtime_error(":ircserv 473 " + save[CurrentClientFD].second.first + " :This channel is invite only\r\n");
        cout << "^^^^^^^ " << (keep.getModes())['l'].first << "  " << keep.getMembersFromFD().size() << " " << keep.getLimit() << '\n';
        if ((keep.getModes())['l'].first && keep.getMembersFromFD().size() >= keep.getLimit())
            throw runtime_error(":ircserv 471 " + save[CurrentClientFD].second.first + " :Channel is full\r\n");
    }
    catch (const exception & e)
    {
        throw runtime_error(e.what());
    }

    modeInfo& keep = CurrentChannels[ChannelIndex].getModes();
    if (sz == 2 && keep['k'].first == true && keep['k'].second != data.second[1])
        throw runtime_error("ERR_BADCHANNELKEY\n");
    else if (sz == 2 && keep['k'].first == false)
        throw runtime_error(": 461 " + save[CurrentClientFD].second.first + " :Not enough parameters\r\n");
    Channel::getChannel()[ChannelIndex].setMember(save[CurrentClientFD].second.first, CurrentClientFD);
    _send(CurrentClientFD, ":" + save[CurrentClientFD].second.first + "!~" + save[CurrentClientFD].second.second + "@" + "localhost" + " JOIN " + data.second[0] + "\r\n");
    _send(CurrentClientFD, "ircserv 353 " + save[CurrentClientFD].second.first + " = " + data.second[0] + " :@" + save[CurrentClientFD].second.first + "\r\n");
    _send(CurrentClientFD, "ircserv 366 " + save[CurrentClientFD].second.first + data.second[0] + " :End of /NAMES list.\r\n");
}

        //         cout << "---------- JOIN " << CurrentChannels[ChannelIndex].getChannelName()<< " --------------\n";
        // map<int, string>::iterator  it0 = CurrentChannels[ChannelIndex].getMembersFromFD().begin();
        // map<int, string>::iterator  it0e = CurrentChannels[ChannelIndex].getMembersFromFD().end();
        // for (map<int, string>::iterator  t0 = it0; t0 != it0e; t0++)
        // {
        //     cout << "first " << t0->first << "  "  << t0->second << '\n';
        // }
        // cout << "-------------------------\n";