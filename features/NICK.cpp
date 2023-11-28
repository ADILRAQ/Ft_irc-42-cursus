/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:32 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/28 14:02:32 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::NICK()
{
    ClientInfos save = Client::getClient();
    try
    {
        checkParamsNick(data.second);
        ClientInfos::iterator it = save.begin();
        ClientInfos::iterator ite = save.end();
        for (ClientInfos::iterator t = it; t != ite; t++)
        {
            if (CurrentClientFD != t->first && ((t->second).second.first == data.second[0]))
                throw runtime_error(": 433 " + (t->second).second.second + " :Nickname is already in use\r\n");
        }
    }
    catch(const exception& e)
    {
        throw runtime_error(e.what());
    }

    string& nick = Client::getClient()[CurrentClientFD].second.first;
    if (!nick.empty())
    {
        vector<Chan> channel = Channel::getChannel();
        for (unsigned int i(0); i < channel.size(); i++)
        {
            if (channel[i].getMembers().find(nick) != channel[i].getMembers().end())
            {
                channel[i].getMembers()[data.second[0]] = channel[i].getMembers().find(nick)->second;
                channel[i].getMembers().erase(channel[i].getMembers().find(nick));
                channel[i].getMembersFromFD()[CurrentClientFD] = data.second[0];
            }
        }
        serverReplyFormat(CurrentClientFD, Client::getClient()[CurrentClientFD].second, data, 0);
    }
    Client::getClient()[CurrentClientFD].second.first = data.second[0];
}
