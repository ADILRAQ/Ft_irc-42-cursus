/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:39 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/09 15:27:20 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::deleteFromChn(const string & nick, const unsigned int & index, const string cmd)
{
    vector<Chan>& channel = Channel::getChannel();
    map<int, string> memberS = channel[index].getMembersFromFD();
    map<int, string>::iterator ic = memberS.begin();
    map<int, string>::iterator ice = memberS.end();
    vector<string> save;
    if (cmd == "PART")
        save.push_back(channel[index].getChannelName());
    save.push_back("Leaving...");
    cmdInfos keep;
    keep.first = cmd;
    keep.second = save;
    for (map<int, string>::iterator c = ic; c != ice; c++)
        serverReplyFormat(c->first, Client::getClient()[CurrentClientFD].second, keep);
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
    vector<string> save;
    save.push_back("Leaving...");
    cmdInfos keep;
    keep.first = "QUIT";
    keep.second = save;
    serverReplyFormat(CurrentClientFD, Client::getClient()[CurrentClientFD].second, keep);
    Client::getClient().erase(CurrentClientFD);
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
        if (channel[i].getMembers().find(nick) != channel[i].getMembers().end())
            deleteFromChn(nick, i, "QUIT");
}

void    Cmd::PART()
{
    vector<Chan>& channel = Channel::getChannel();
    for (unsigned int i(0); i < channel.size(); i++)
        if (channel[i].getChannelName() == data.second[0])
            deleteFromChn(Client::getClient()[CurrentClientFD].second.first, i, "PART");
}
