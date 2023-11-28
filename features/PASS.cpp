/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:37 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/28 14:08:57 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::PASS()
{
    string & nick = Client::getClient()[CurrentClientFD].second.first;

    if (data.second.size() != 1)
        throw runtime_error(": 461 " + nick + " :PASS Not enough parameters\r\n");

    if (Client::getClient()[CurrentClientFD].first >= 3)
        throw runtime_error(": 462 " + nick + " :You may not reregister\r\n");

    if (data.second[0] != pass)
        throw runtime_error(": 464 " + nick + " :PASS Password incorrect\r\n");

    return ;
}