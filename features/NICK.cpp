/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:32 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/27 17:56:36 by fraqioui         ###   ########.fr       */
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
        _send(CurrentClientFD, ":" + nick + "!~" + Client::getClient()[CurrentClientFD].second.second + "@localhost NICK " + ":" + data.second[0] + "\r\n");
    Client::getClient()[CurrentClientFD].second.first = data.second[0];
}
