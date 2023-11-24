/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:05 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 09:55:56 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

Cmd::Cmd(cmdInfos& obj, int& fd) : data(obj) , CurrentClientFD(fd)
{

}

Cmd::~Cmd()
{

}

const cmdInfos& Cmd::getCmdInfos() const
{
    return data;
}

void    Cmd::executeCmd(const string & nick)
{
    cmdFunc f[] = {&Cmd::PASS, &Cmd::USER, &Cmd::NICK, &Cmd::JOIN, &Cmd::KICK, &Cmd::INVITE, &Cmd::TOPIC, &Cmd::MODE, &Cmd::QUIT};
    string Which[] = {"PASS", "USER", "NICK", "JOIN", "KICK", "INVITE", "TOPIC", "MODE", "QUIT"};
    // check the process of PASS NICK USER
    for (int i = 0; i < 9; i++)
    {
        if (data.first == Which[i])
        {
            std::cout << "Check cmd: " << Which[i] << '\n';
            try
            {
                (this->*f[i])();
            }
            catch(const std::exception& e)
            {
                _send(1, e.what());
            }
            return ;
        }
        if (i + 1 == 9)
            _send(1, ": 421 " + nick + " :Unknown command\r\n");
    }
}
