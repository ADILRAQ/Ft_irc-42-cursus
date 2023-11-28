/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:55 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 13:40:15 by fraqioui         ###   ########.fr       */
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
    client[fd] = pair<int, pair<string, string> >(0, pair<string, string>(nick, user));
}

ClientInfos & Client::getClient()
{
    return client;
}
