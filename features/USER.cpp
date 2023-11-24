/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:44 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/23 11:34:38 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::USER()
{
    try
    {
        ClientInfos save = Client::getClient();
        checkParamsUser(data.second, save[CurrentClientFD].first);

        ClientInfos::iterator it = save.begin();
        ClientInfos::iterator ite = save.end();
        for (ClientInfos::iterator t = it; t != ite; t++)
        {
            if (CurrentClientFD != t->first && ((t->second).second == data.second[0]))
                throw runtime_error(": 433 " + (t->second).second + " :Username is already in use\r\n");
        }
        if (save.find(CurrentClientFD) != save.end() && !(save[CurrentClientFD].second.empty()))
            throw runtime_error(": 462 " + save[CurrentClientFD].first + " :You may not reregister\r\n");
        save[CurrentClientFD].second = data.second[0];
        _send(1, ": 001 " + save[CurrentClientFD].first + " :Welcome to the Internet Relay Chat Network\r\n");
    }
    catch(const std::exception& e)
    {
        throw e;
    }
}
