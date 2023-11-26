/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainHeader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:08:36 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/26 09:39:34 by fraqioui         ###   ########.fr       */
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

std::string const	Bot(std::string const &request);