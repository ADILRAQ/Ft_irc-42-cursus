/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:05 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/28 10:58:49 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

Cmd::Cmd(cmdInfos& obj, int& fd, string &passwd) : data(obj) , CurrentClientFD(fd), pass(passwd)
{

}

Cmd::~Cmd()
{

}

const cmdInfos& Cmd::getCmdInfos() const
{
    return data;
}

void Cmd::BeginExec(int i)
{
    cmdFunc f[] = {&Cmd::PASS, &Cmd::NICK, &Cmd::USER, &Cmd::JOIN, &Cmd::KICK, &Cmd::INVITE, &Cmd::TOPIC, &Cmd::MODE, &Cmd::PRIVMSG, &Cmd::QUIT};
    try
    {
        (this->*f[i])();
        ++Client::getClient()[CurrentClientFD].first;
    }
    catch(const exception& e)
    {
        _send(CurrentClientFD, e.what());
    }
}

void    Cmd::executeCmd(const string & nick)
{
    string Which[] = {"PASS", "NICK", "USER", "JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "QUIT"};
    ClientInfos CurrentClient = Client::getClient();

    if (CurrentClient.find(CurrentClientFD) == CurrentClient.end())
        Client::setClient(CurrentClientFD, "", "");
//TO FIX
    if (CurrentClient[CurrentClientFD].first < 3 && Which[CurrentClient[CurrentClientFD].first] == data.first)
        BeginExec(CurrentClient[CurrentClientFD].first);
    else if (CurrentClient[CurrentClientFD].first < 3 && Which[CurrentClient[CurrentClientFD].first] != data.first)
        _send(CurrentClientFD, ": 451 :You have not registered in the right process\r\n");
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (data.first == Which[i])
            {
                BeginExec(i);
                break ;
            }
            if (i + 1 == 10)
                _send(CurrentClientFD, ": 421 " + nick + " :Unknown command\r\n");
        }
    }
}

    // /******************/
    // ClientInfos::iterator it = CurrentClient.begin();
    // ClientInfos::iterator ite = CurrentClient.end();
    // cout << "////////////////////////////////////\n";
    // for(ClientInfos::iterator t = it; t != ite; t++)
    // {
    //     cout << t->first << "  " << t->second.first << "  " << t->second.second.first << "  " << t->second.second.second << '\n';
    // }
    // /*****************/