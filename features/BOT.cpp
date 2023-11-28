/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BOT.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:50:35 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/28 15:02:09 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

const char	*API_HOST = "api.weatherapi.com";
const char	*API_PATH = "/v1/current.json";
const char	*API_KEY = "bd9f83a56f2b46b6ae3142327232411";

void Cmd::BOT()
{
	string& nick = Client::getClient()[CurrentClientFD].second.first;
	unsigned int sz = data.second.size();

	if (sz != 1)
		throw runtime_error(": 461 " + nick + " :BOT Not enough parameters\r\n");

	// Send the message
	// _send(CurrentClientFD, message);
}
