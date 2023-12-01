/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:23 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/01 19:43:13 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::JOIN()
{
    unsigned int    sz;
    string          s;
    ClientInfos save = Client::getClient();
    string&     nick = save[CurrentClientFD].second.first;

    try
    {
        sz = checkChannel(data.second, nick);
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
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], nick);
    }
    catch(const std::exception& e)
    {
        flg = 1;
    }

    if (flg)
    {
        Chan obj(data.second[0], nick, CurrentClientFD);
        Channel::setChannel(obj);
        serverReplyFormat(CurrentClientFD, save[CurrentClientFD].second, data);
    _send(CurrentClientFD, ": 353 " + nick + " @ " + data.second[0] + " :" + "@" + nick + "\r\n");
    _send(CurrentClientFD, ": 366 " + nick + " " + data.second[0] + " :End of /NAMES list.\r\n");
        return ;
    }

    Chan currentChannel = CurrentChannels[ChannelIndex];
    modeInfo& keep = CurrentChannels[ChannelIndex].getModes();

    if ((sz == 2 && keep['k'].first == true && keep['k'].second != data.second[1]) || (sz == 2 && keep['k'].first == false))
        throw runtime_error(": 475 " + nick + " :Cannot join channel (+k)\r\n");
    if (keep['i'].first && find(currentChannel.getInviteD().begin(), currentChannel.getInviteD().end(), nick) == currentChannel.getInviteD().end())
        throw runtime_error(": 473 " + nick + " :This channel is invite only\r\n");
    if (keep['l'].first && currentChannel.getMembersFromFD().size() >= currentChannel.getLimit())
        throw runtime_error(": 471 " + nick + " :Channel is full\r\n");

    Channel::getChannel()[ChannelIndex].setMember(nick, CurrentClientFD);
    serverReplyFormat(CurrentClientFD, save[CurrentClientFD].second, data);
    memberInfo trav = CurrentChannels[ChannelIndex].getMembers();
    map<int, string> var = CurrentChannels[ChannelIndex].getMembersFromFD();
    map<int, string>::iterator it = var.begin();
    map<int, string>::iterator ite = var.end();
    for (map<int, string>::iterator t = it; t != ite; t++)
    {
        if (t == it)
            s += nick + " ";
        if (t->second == nick)
            continue ;
        if (trav[t->second].second)
            s += "@";
        s += t->second + " ";
    }
    if (!CurrentChannels[ChannelIndex].getTopic().empty())
        _send(CurrentClientFD, ": 332 " + nick + " " + data.second[0] + " :" + CurrentChannels[ChannelIndex].getTopic() + "\r\n");
    _send(CurrentClientFD, ": 353 " + nick + " @ " + data.second[0] + " :" + s + "\r\n");
    _send(CurrentClientFD, ": 366 " + nick + " " + data.second[0] + " :End of /NAMES list.\r\n");

    for (map<int, string>::iterator t = it; t != ite; t++)
        serverReplyFormat(t->first, save[CurrentClientFD].second, data);
}
//handle part
// new the ancient modes of the channel
//handl colon