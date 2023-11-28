/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:37 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/27 21:26:49 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::PASS()
{
    if (data.second.size() != 1)
        throw runtime_error(": 461 :PASS Not enough parameters\r\n");

    if (Client::getClient()[CurrentClientFD].first == 3)
        throw runtime_error(": 462 " + Client::getClient()[CurrentClientFD].second.first + " :You may not reregister\r\n");

    if (data.second[0] != pass)
        throw runtime_error(": 464 :PASS Password incorrect\r\n");

    return ;
}
