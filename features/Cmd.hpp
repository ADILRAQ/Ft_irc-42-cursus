/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:09 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/09 15:14:17 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include"../header.hpp"
#include"../Client.hpp"
#include"../Channel.hpp"
#include"../MainHeader.hpp"

typedef pair<string, vector<string> > cmdInfos;

/************* Command holder *************/

class Cmd
{
private:
        cmdInfos        data;
        int             CurrentClientFD;
        string          &pass;
        string          &host;

public:
        Cmd(cmdInfos& obj, int& fd, string &passwd, string &hst);
        ~Cmd();

        const cmdInfos& getCmdInfos() const;
        void            executeCmd(const string & nick);
        void            BeginExec(int i);
        void            deleteFromChn(const string & nick, const unsigned int & index, const string cmd);

        void    PASS();
        void    USER();
        void    NICK();
        void    JOIN();
        void    KICK();
        void    INVITE();
        void    TOPIC();
        void    MODE();
        void    PRIVMSG();
        void    QUIT();
        void    PART();
        void    NOTICE();
        void    BOT();
};

typedef void (Cmd::*cmdFunc)();

/************* Helper Functions *************/

void            checkParamsUser(const vector<string> & vc, const string & nick);
void            checkParamsNick(const vector<string> & vc);
void            toLowerString(string & s);
void            placeCmds(string cmd, int fd, const char * passwd, string IP);
void            _send(int fd, string mess);
void            serverReplyFormat(const int &fd, const pair<string, string>& userInfo, const cmdInfos& params);
void            checkKey(string key, const string & nick);
void            checkLimit(string limit, const string & nick);
unsigned int    checkChannel(const vector<string> & vc, const string & nick);
unsigned int    checkTopic(const vector<string> & vc, const string & nick);
int             ValidString(const string s, bool flg);
cmdInfos        placeParams(string & cmd, const string & nick);
