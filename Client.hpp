/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:58 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 11:02:37 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include"header.hpp"

typedef map<int, pair<int , pair<string, string> > > ClientInfos;

class Client
{
private:
        static ClientInfos client;

public:
        Client();
        ~Client();

        static void setClient(int fd, string nick, string user);
        static ClientInfos & getClient();
};
