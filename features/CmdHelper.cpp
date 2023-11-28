/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHelper.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:18 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/28 18:30:47 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

void    checkWhitespaces(string & s, bool & flg, const string & nick)
{
    for (unsigned int i(0); i < s.length(); i++)
    {
        if (!i && s[i] == ' ')
            break ;
        if (s[i] == ':')
        {
            flg = true;
            return ;
        }
        if (s[i] == ' ' && i + 1 < s.length() && s[i + 1] == ' ')
            break ;
        if (i == s.length() - 1)
            return ;
    }
    throw runtime_error(": 461 " + nick + " :Not enough parameters\r\n");
}

cmdInfos    placeParams(string & cmd, const string & nick)
{
    cmdInfos        params;
    vector<string>  save;
    string          toStr;
    string          Split;
    string          NSplit;
    bool             flg(0);

    checkWhitespaces(cmd, flg, nick);
    if (flg)
    {
        istringstream   in(cmd);
        getline(in, cmd, ':');
        getline(in, NSplit);
    }
    istringstream   instr(cmd);
    for (int check(0); getline(instr, toStr, ' '); )
    {
        if (!check)
        {
            params.first = toStr;
            check++;
            continue ;
        }
        save.push_back(toStr);
    }
    if (flg)
        save.push_back(NSplit);
    params.second = save;
    cout << "********** print data **********\n";
    cout << "cmd: " << params.first << '\n';
    for (unsigned int i(0); i < params.second.size(); i++)
        cout << '\"' << params.second[i] << "\" ";
    cout << "\n********** End **********\n";
    return params;
}

void    placeCmds(string cmd, int fd, const char * passwd, string IP)
{
    cmdInfos    obj;
    ClientInfos clients = Client::getClient();
    string ps(passwd);

    if (!cmd.empty())
    {
        try
        {
            cmd.erase(cmd.size() - 1);
            if (cmd[cmd.size() - 1] == '\r')
                cmd.erase(cmd.size() - 1);
            obj = placeParams(cmd, clients[fd].second.first);
        }
        catch(const exception & e)
        {
            _send(fd, e.what());
        }
    }
    Cmd command(obj, fd, ps, IP);
    command.executeCmd(clients[fd].second.first);
}

/*********************************** Commands Syntax *****************************************/

int    ValidString(const string s, bool flg)
{
    int i = 0;

    if (!flg)
        i++;
    for (; i < int(s.length()); i++)
    {
        if (flg && s[i] == 32)
            return -1;
        if (s[i] < 32 || s[i] == 44 || s[i] == 58 || s[i] >= 127)
            return -1;
    }
    return i;
} 

void    checkParamsUser(const vector<string> & vc, const string & nick)
{
    if ((vc.size() != 1 && vc.size() != 4) || vc[0].empty())
        throw runtime_error(": 461 " + nick + " :USER Not enough parameters\r\n");
//start with num
    unsigned int i = 0;
    for (; i < vc[0].length(); i++)
        if (!(isalnum(vc[0][i]) || vc[0][i] == '_' || vc[0][i] == '-'))
            throw runtime_error(": 432" + nick + " :Non valid character\r\n");

    if (i > 9)
        throw runtime_error(": 432 " + nick + " :Passed the valid length\r\n");
}

void    checkParamsNick(const vector<string> & vc)
{
    if (vc.size() != 1 || vc[0].empty())
        throw runtime_error(": 461 :NICK Not enough parameters\r\n");

    unsigned int i = 0;
    for (; i < vc[0].length(); i++)
        if (!(isalnum(vc[0][i]) || vc[0][i] == '_' || vc[0][i] == '-'))
            throw runtime_error(": 432" + vc[0] + " :Non valid character(s)\r\n");

    if (i > 9)
        throw runtime_error(": 432 " + vc[0] + " :Passed the valid length\r\n");
}

unsigned int    checkChannel(const vector<string> & vc, const string & nick)
{
    unsigned int sz = vc.size();
    if (sz != 1 && sz != 2)
        throw runtime_error(": 461 " + nick + " :JOIN Not enough parameters\r\n");

    if (vc[0].empty() || vc[0][0] != '#' || (sz == 2 && vc[1].empty()))
        throw runtime_error(": 403 " + vc[0] + " :No such channel\r\n");

    int i = ValidString(vc[0], true);
    if (i < 0 || i > 50)
        throw runtime_error(": 403 " + vc[0] + " :No such channel\r\n");
    return sz;
}

unsigned int    checkTopic(const vector<string> & vc, const string & nick)
{
    unsigned int sz = vc.size();

    if (sz != 1 && sz != 2)
        throw runtime_error(": 461 " + nick + " :TOPIC Not enough parameters\r\n");

    if (vc[0].empty() || (sz == 2 && vc[1].empty()))
        throw runtime_error(": 461 " + nick + " :TOPIC Not enough parameters\r\n");

    if (sz == 2 && ValidString(vc[1], false) < 0)
        throw runtime_error(": 461 " + nick + " :Non valid character(s)\r\n");
    return sz;
}

void    checkKey(string key, const string & nick)
{
    for (unsigned int i(0); i < key.length(); i++)
        if (!isalpha(key[i]))
            throw runtime_error(": 461 " + nick + " :MODE Not enough parameters\r\n");
}

void    checkLimit(string limit, const string & nick)
{
    for (unsigned int i(0); i < limit.length(); i++)
        if (!isdigit(limit[i]))
            throw runtime_error(": 461 " + nick + " :MODE Not enough parameters\r\n");
}

char    checkMode(const vector<string> & vc, const string & nick)
{
    unsigned int sz = vc.size();
    if ((sz != 2 && sz != 3) || (vc[0].empty() || vc[1].empty() || (sz == 3 && vc[2].empty())))
        throw runtime_error(": 461 " + nick + " :MODE Not enough parameters\r\n");

    if (vc[1].length() != 2 || (vc[1][0] != '-' && vc[1][0] != '+') || (vc[1][1] != 'i' && vc[1][1] != 't' && vc[1][1] != 'k' && vc[1][1] != 'o' && vc[1][1] != 'l'))
        throw runtime_error(": 472 " + nick + " " + vc[1] + " :is unknown mode char to me\r\n");

    if (sz == 3 && vc[1][0] == '+' && !(vc[1][1] == 'k' || vc[1][1] == 'o' || vc[1][1] == 'l'))
        throw runtime_error(": 461 " + nick + " :MODE Not enough parameters\r\n");

    if (vc[1][1] == 'k')
        checkKey(vc[2], nick);

    if (vc[1][1] == 'l')
        checkLimit(vc[2], nick);

    return vc[1][1];
}

void    toLowerString(string & s)
{
    for (unsigned int i(0); i < s.length(); i++)
        s[i] = tolower(s[i]);
}

void _send(int fd, string mess)
{
    send(fd, mess.c_str(), mess.length(), 0);
}

void serverReplyFormat(const int &fd, const pair<string, string>& userInfo, const cmdInfos& params, const int flg)
{
    string save;

    for (unsigned int i(0); i < params.second.size(); i++)
    {
        save += params.second[i];
        if (i != params.second.size() - 1)
            save += " ";
    }
    _send(fd, ":" + userInfo.first + "!" + userInfo.second + "@localhost " + params.first + " " + save + "\r\n");
    if (flg)
        _send(fd, ": MODE " + params.second[0] + " +o " + userInfo.first + "\r\n");
}
