/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:21 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 09:11:12 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::INVITE()
{
    unsigned int    ChannelIndex;

    if (data.second.size() != 2)
      std::cout << "461\n";

    vector<Chan> CurrentChannels = Channel::getChannel();
    ClientInfos CurrentClients = Client::getClient();

    try
    {
        ChannelIndex = ChannelExist(CurrentChannels, data.second[0]);
        IsInChannel(CurrentChannels[ChannelIndex], CurrentClientFD, false);
        if (CurrentClients.find(CurrentClientFD) == CurrentClients.end())
          throw runtime_error("User does not exist : look for right error\n ");
        IsUserInChannel(CurrentChannels[ChannelIndex], data.second[0]);
    } 
    catch (const exception & e)
    {

    }
    ClientInfos::iterator it = CurrentClients.begin();
    ClientInfos::iterator ite = CurrentClients.end();
    ClientInfos::iterator t = it;
    for (; t != ite; t++)
        if (t->second.first == data.second[0])
            break ;
    CurrentChannels[ChannelIndex].setMember(data.second[0], t->first);
    //341
}


// 442 "<channel> :You're not on that channel"
// 461 "<command> :Not enough parameters"
// 464 ":Password incorrect"
// 467 "<channel> :Channel key already set"
// 471 "<channel> :Cannot join channel (+l)"
// 472 "<char> :is unknown mode char to me"
// 473 "<channel> :Cannot join channel (+i)"
// 482 "<channel> :You're not channel operator"
/*

501     ERR_UMODEUNKNOWNFLAG
                ":Unknown MODE flag"
        - Returned by the server to indicate that a MODE
          message was sent with a nickname parameter and that
          the a mode flag sent was not recognized.
*/

/*
341     RPL_INVITING
                "<channel> <nick>"
        - Returned by the server to indicate that the
          attempted INVITE message was successful and is
          being passed onto the end client.
*/

/*
401     ERR_NOSUCHNICK
                "<nickname> :No such nick/channel"
        - Used to indicate the nickname parameter supplied to a
          command is currently unused.
*/

/*
443     ERR_USERONCHANNEL
                "<user> <channel> :is already on channel"
        - Returned when a client tries to invite a user to a
          channel they are already on.
*/

/*
  421     ERR_UNKNOWNCOMMAND
                    "<command> :Unknown command"
            - Returned to a registered client to indicate that the
              command sent is unknown by the server.
*/