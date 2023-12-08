/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:39 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/08 11:14:28 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::deleteFromChn(const string & nick, const unsigned int & index)
{
    vector<Chan>& channel = Channel::getChannel();
    channel[index].getMembersFromFD().erase(channel[index].getMembersFromFD().find(CurrentClientFD));
    channel[index].getMembers().erase(channel[index].getMembers().find(nick));
    if (channel[index].getMembers().size() == 0)
    {
        vector<Chan>::iterator it = channel.begin();
        vector<Chan>::iterator ite = channel.end();
        vector<Chan>::iterator t = it;
        for (int i = 0; t != ite; t++, i++)
           if (i == index)
                break ; 
        Channel::getChannel().erase(t);
    }
}

void    Cmd::QUIT()
{
    string & nick = Client::getClient()[CurrentClientFD].second.first;
    Client::getClient().erase(Client::getClient().find(CurrentClientFD));
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
        if (channel[i].getMembers().find(nick) != channel[i].getMembers().end())
            deleteFromChn(nick, i);
}

void    Cmd::PART()
{
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
        if (channel[i].getChannelName() == data.second[0])
            deleteFromChn(Client::getClient()[CurrentClientFD].second.first, i);
}
