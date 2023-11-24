/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:32 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/23 11:39:57 by fraqioui         ###   ########.fr       */
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
            if (CurrentClientFD != t->first && ((t->second).first == data.second[0]))
                throw runtime_error(": 433 " + (t->second).second + " :Nickname is already in use\r\n");
        }
    }
    catch(const std::exception& e)
    {
        throw e;
    }
    if (save.find(CurrentClientFD) != save.end())
    {
        save[CurrentClientFD].first = data.second[0];
        return ;
    }
    Client::setClient(CurrentClientFD, data.second[0], "");
}
