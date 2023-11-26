/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:44 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 15:43:10 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::USER()
{
    try
    {
        ClientInfos save = Client::getClient();
        checkParamsUser(data.second, save[CurrentClientFD].second.first);

        if (save.find(CurrentClientFD) != save.end() && !(save[CurrentClientFD].second.second.empty()))
            throw runtime_error(":ircserv 462 " + save[CurrentClientFD].second.first + " :You may not reregister\r\n");
        Client::getClient()[CurrentClientFD].second.second = data.second[0];
        _send(CurrentClientFD, ":ircserv 001 " + save[CurrentClientFD].second.first + " :Welcome to the Internet Relay Chat Network\r\n");
    }
    catch(const exception& e)
    {
        throw runtime_error(e.what());
    }
}
