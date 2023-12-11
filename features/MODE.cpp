/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:29 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/11 09:59:30 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::MODE()
{
    unsigned int    ChannelIndex;
    bool            Set, done(false);
    string          holder1, holder2, toS;
    vector<Chan>& CurrentChannels = Channel::getChannel();
    ClientInfos&  CurrentClients = Client::getClient();
    string& nick = CurrentClients[CurrentClientFD].second.first;
    unsigned int sz = data.second.size();

    if (sz == 1)
        return ;

    if (sz < 2)
        throw runtime_error(": 461 " + nick + " :MODE Not enough parameters\r\n");

    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0], CurrentClients[CurrentClientFD].second.first);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, true);
    }
    catch (const exception & e)
    {
        throw runtime_error(e.what());
    }

    unsigned int index = 2, flg = 0;
    vector<string>& vc = data.second;
    if (vc[1] == "+sn")
        return ;
    for (unsigned int j(0); j < vc[1].size(); j++)
    {
        cout << "JJJ " << j<<endl;
        if (!j && vc[1][j] != '+' && vc[1][j] != '-')
        {
            for (; vc[1][j] != '+' && vc[1][j] != '-' && j < vc[1].size(); j++)
                _send(CurrentClientFD, ": 472 " + nick + " " + vc[1][j] + " :is unknown mode char to me\r\n");
        }
        if (vc[1][j] == '+' || vc[1][j] == '-')
        {
            if (vc[1][j] == '+')
                {Set = true; holder1 += "+";}
            else
                {Set = false; holder1 += "-";}
            j++;
            for (; vc[1][j] != '+' && vc[1][j] != '-' && j < vc[1].size(); j++)
            {
                cout << "JJJ2 " << j<<endl;
                if (vc[1][j] != 'i' && vc[1][j] != 't' && vc[1][j] != 'k' && vc[1][j] != 'o' && vc[1][j] != 'l')
                    {_send(CurrentClientFD, ": 472 " + nick + " " + vc[1][j] + " :is unknown mode char to me\r\n"); continue;}
                // cout << "HERE " << index << " " << vc[index] <<endl;
                if ((vc[1][j] == 'o' || (Set && (vc[1][j] == 'k' || vc[1][j] == 'l'))) && vc[index].empty())
                    {_send(CurrentClientFD, ": 461 " + nick + " :MODE Not enough parameters\r\n"); index++; continue;}
                if (Set && vc[1][j] == 'k')
                {
                    if (CurrentChannels[ChannelIndex].getModes()['k'].first)
                        {_send(CurrentClientFD, ": 467 " + nick + " " + vc[0] + " :Channel key already set\r\n"); continue;}
                    try
                    {
                        checkKey(vc[index], nick);
                        CurrentChannels[ChannelIndex].setModesStat('k', true, vc[index]);
                        flg = 1;
                    }
                    catch (const exception & e)
                    {
                        _send(CurrentClientFD, e.what());
                        index++;
                        continue ;
                    }
                }
                else if (Set && vc[1][j] == 'l')
                {
                    try
                    {
                        checkLimit(vc[index], nick);
                        CurrentChannels[ChannelIndex].setModesStat('l', true, vc[index]);
                        CurrentChannels[ChannelIndex].setChannelLimit(atoi((vc[index]).c_str()));
                        flg = 1;
                    }
                    catch (const exception & e)
                    {
                        _send(CurrentClientFD, e.what());
                        index++;
                        continue ;
                    }
                }
                else if (vc[1][j] == 'o')
                {
                    try
                    {
                        IsUserInChannel(CurrentChannels[ChannelIndex], vc[index], true);
                        flg = 1;
                    }
                    catch (const exception & e)
                    {
                        _send(CurrentClientFD, e.what());
                        index++;
                        continue ;
                    }
                    CurrentChannels[ChannelIndex].setChannelOper(vc[index], Set);
                }
                else
                    CurrentChannels[ChannelIndex].setModesStat(vc[1][j], Set, "");
                done = true;
                {toS.clear(); toS.push_back(vc[1][j]);}
                if (Set)
                    holder1 += toS;
                else
                    holder1 += toS;
                if (flg)
                {
                    holder2 += vc[index] + " ";
                    index++;
                }
            }
        }
        j--;
    }
    if (!done)
        return ;
    data.second.erase(data.second.begin() + 1, data.second.end());
    data.second.push_back(holder1 + " " + holder2);

    map<int, string> var = CurrentChannels[ChannelIndex].getMembersFromFD();
    map<int, string>::iterator it = var.begin();
    map<int, string>::iterator ite = var.end();

    for (map<int, string>::iterator t = it; t != ite; t++)
        serverReplyFormat(t->first, CurrentClients[CurrentClientFD].second, data);
}
