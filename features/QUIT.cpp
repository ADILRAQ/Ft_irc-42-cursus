/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:39 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/10 14:23:00 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::deleteFromChn(const string & nick, const unsigned int & index)
{
    vector<Chan>& channel = Channel::getChannel();
    map<int, string> memberS = channel[index].getMembersFromFD();
    map<int, string>::iterator ic = memberS.begin();
    map<int, string>::iterator ice = memberS.end();
    for (map<int, string>::iterator c = ic; c != ice; c++)
        serverReplyFormat(c->first, Client::getClient()[CurrentClientFD].second, data);
    channel[index].getMembersFromFD().erase(CurrentClientFD);
    channel[index].getMembers().erase(nick);
    if (channel[index].getMembers().size() == 0)
    {
        vector<Chan>::iterator it = channel.begin();
        vector<Chan>::iterator ite = channel.end();
        vector<Chan>::iterator t = it;
        for (unsigned int i = 0; t != ite; t++, i++)
           if (i == index)
                break ; 
        Channel::getChannel().erase(t);
    }
}

void    Cmd::QUIT()
{
    string & nick = Client::getClient()[CurrentClientFD].second.first;
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
        if (channel[i].getMembers().find(nick) != channel[i].getMembers().end())
            deleteFromChn(nick, i);
    Client::getClient().erase(CurrentClientFD);
}

void    Cmd::PART()
{
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
        if (channel[i].getChannelName() == data.second[0])
            deleteFromChn(Client::getClient()[CurrentClientFD].second.first, i);
}
