/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:32 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/11 09:34:30 by fraqioui         ###   ########.fr       */
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
            memberInfo& saving = channel[i].getMembers();
            if (saving.find(nick) != saving.end())
            {
                saving[data.second[0]] = saving.find(nick)->second;
                saving.erase(saving.find(nick));
                channel[i].getMembersFromFD()[CurrentClientFD] = data.second[0];
                map<int, string> keep = channel[i].getMembersFromFD();
                map<int, string>::iterator ic = keep.begin();
                map<int, string>::iterator ice = keep.end();
                for (map<int, string>::iterator c = ic; c != ice; c++)
                    if (CurrentClientFD != c->first)
                        serverReplyFormat(c->first, Client::getClient()[CurrentClientFD].second, data);
            }
        }
        serverReplyFormat(CurrentClientFD, Client::getClient()[CurrentClientFD].second, data);
    }
    Client::getClient()[CurrentClientFD].second.first = data.second[0];
}
