/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainHeader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:08:36 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/28 18:32:54 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "features/Cmd.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <signal.h>

void	startServer(char *port, char *pswd);

// Command

std::string const	Bot(std::string const &request, int fd);