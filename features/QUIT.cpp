/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:39 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/07 11:54:16 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::deleteFromChn(const string & nick)
{
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
    {
        if (channel[i].getMembers().find(nick) != channel[i].getMembers().end())
        {
            channel[i].getMembersFromFD().erase(channel[i].getMembersFromFD().find(CurrentClientFD));
            channel[i].getMembers().erase(channel[i].getMembers().find(nick));
        }
    }
    if (channel.size() == 0)
        ;//delte channel
}

void    Cmd::QUIT()
{
    Client::getClient().erase(Client::getClient().find(CurrentClientFD));
    deleteFromChn(Client::getClient()[CurrentClientFD].second.first);
}

void    Cmd::PART()
{
    deleteFromChn(Client::getClient()[CurrentClientFD].second.first);
}
