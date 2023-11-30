/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainHeader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:08:36 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/29 16:08:44 by araqioui         ###   ########.fr       */
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

void    Bot(std::string const &request);