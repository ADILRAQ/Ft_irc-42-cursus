/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:09 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/26 10:00:40 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include"../header.hpp"
#include"../Client.hpp"
#include"../Channel.hpp"

typedef pair<string, vector<string> > cmdInfos;

/************* Command holder *************/

class Cmd
{
private:
        cmdInfos        data;
        int             CurrentClientFD;
        string          &pass;

public:
        Cmd(cmdInfos& obj, int& fd, string &passwd);
        ~Cmd();

        const cmdInfos& getCmdInfos() const;
        void            executeCmd(const string & nick);
        void            BeginExec(int i);

        void    PASS();
        void    USER();
        void    NICK();
        void    JOIN();
        void    KICK();
        void    INVITE();
        void    TOPIC();
        void    MODE();
        void    QUIT();

};

typedef void (Cmd::*cmdFunc)();

/************* Helper Functions *************/

void            checkParamsUser(const vector<string> & vc, const string & nick);
void            checkParamsNick(const vector<string> & vc);
void            toLowerString(string & s);
void            placeCmds(string cmd, int fd, const char * passwd);
void            _send(int fd, string mess);
unsigned int    checkChannel(const vector<string> & vc, const string & nick);
unsigned int    checkTopic(const vector<string> & vc, const string & nick);
char            checkMode(const vector<string> & vc, const string & nick);
cmdInfos        placeParams(string & cmd, const string & nick);
