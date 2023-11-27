/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:23 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/27 10:46:05 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    announceJoining(string & nick, string & user, string &channel, const int & fd, bool flg)
{
    _send(fd, ":" + nick + "!~" + user + "@" + "localhost" + " JOIN " + channel + "\r\n");
    if (flg)
        _send(fd, ":ircserv MODE " + channel + " +o " + nick + "\r\n");
}

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
        Chan obj(data.second[0], save[CurrentClientFD].second.first, CurrentClientFD);
        Channel::setChannel(obj);
        announceJoining(save[CurrentClientFD].second.first, save[CurrentClientFD].second.second, data.second[0], CurrentClientFD, 1);
        return ;
    }

    Chan currentChannel = CurrentChannels[ChannelIndex];
    modeInfo& keep = CurrentChannels[ChannelIndex].getModes();

    if ((sz == 2 && keep['k'].first == true && keep['k'].second != data.second[1]) || (sz == 2 && keep['k'].first == false))
        throw runtime_error(":ircserv 475 " + save[CurrentClientFD].second.first + " :Cannot join channel (+k)\r\n");
    if (keep['i'].first)
        throw runtime_error(":ircserv 473 " + save[CurrentClientFD].second.first + " :This channel is invite only\r\n");
    if (keep['l'].first && currentChannel.getMembersFromFD().size() >= currentChannel.getLimit())
        throw runtime_error(":ircserv 471 " + save[CurrentClientFD].second.first + " :Channel is full\r\n");

    Channel::getChannel()[ChannelIndex].setMember(save[CurrentClientFD].second.first, CurrentClientFD);
    announceJoining(save[CurrentClientFD].second.first, save[CurrentClientFD].second.second, data.second[0], CurrentClientFD, 0);

    map<int, string> var = CurrentChannels[ChannelIndex].getMembersFromFD();
    map<int, string>::iterator it = var.begin();
    map<int, string>::iterator ite = var.end();

    for (map<int, string>::iterator t = it; t != ite; t++)
        announceJoining(save[CurrentClientFD].second.first, save[CurrentClientFD].second.second, data.second[0], t->first, 0);
}
