/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:55 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/23 10:36:23 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"

ClientInfos Client::client;

Client::Client()
{

}

Client::~Client()
{

}

void Client::setClient(int fd, string nick, string user)
{
    client[fd] = pair<string, string>(nick, user);
}

ClientInfos & Client::getClient()
{
    return client;
}

// 401