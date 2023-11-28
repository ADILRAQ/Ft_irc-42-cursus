/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:05 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/28 14:52:47 by araqioui         ###   ########.fr       */
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
    cmdFunc f[] = {&Cmd::PASS, &Cmd::NICK, &Cmd::USER, &Cmd::JOIN, &Cmd::KICK, &Cmd::INVITE, &Cmd::TOPIC, &Cmd::MODE, &Cmd::PRIVMSG, &Cmd::QUIT, &Cmd::BOT};
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
    string Which[] = {"PASS", "NICK", "USER", "JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "QUIT", "BOT"};
    ClientInfos CurrentClient = Client::getClient();

    if (CurrentClient.find(CurrentClientFD) == CurrentClient.end())
        Client::setClient(CurrentClientFD, "", "");

    int j = CurrentClient[CurrentClientFD].first;
    if (j < 3 && Which[j] == data.first)
        BeginExec(j);
    else if (j < 3 && Which[j] != data.first)
        _send(CurrentClientFD, ": 451 :You have not registered in the right process\r\n");
    else
    {
        for (int i = 0; i < 11; i++)
        {
            if (data.first == Which[i])
            {
                BeginExec(i);
                break ;
            }
            if (i + 1 == 11)
                _send(CurrentClientFD, ": 421 " + nick + " :Unknown command\r\n");
        }
    }
}