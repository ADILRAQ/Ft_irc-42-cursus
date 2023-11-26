/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainHeader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:08:36 by araqioui          #+#    #+#             */
/*   Updated: 2023/11/25 12:21:36 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <signal.h>

void	startServer(char *port, char *pswd);

// Command

std::string const	Bot(std::string const &request);