/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:39 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/27 21:29:15 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    Cmd::QUIT()
{
    if(data.second.size() != 0)
        throw runtime_error(": 461 :QUIT Not enough parameters\r\n");
    _send(CurrentClientFD, ": QUIT :Gone to have lunch\r\n");
    // TODO
}
