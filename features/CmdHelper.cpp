/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHelper.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:18 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/09 13:17:26 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cmd.hpp"

string    eliminateSpaces(string & str, const int & flg)
{
    string  ret;
    int     check(0);

    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (check == 2 && flg && str[i] == ' ')
            ;
        else if (str[i] == ' ')
        {
            while (i < str.length() && str[i] == ' ')
                i++;
            ret.push_back(' ');
            check++;
        }
        ret.push_back(str[i]);
    }
    str.clear();
    return ret;
}

cmdInfos    placeParams(string & cmd)
{
    cmdInfos        params;
    vector<string>  save;
    string          toStr;
    bool            flg(false);

    istringstream   in(cmd);
    getline(in, toStr, ' ');
    if (toStr == "PRIVMSG" || toStr == "NOTICE" || toStr == "TOPIC" || toStr == "KICK")
        flg = true;
    cmd = eliminateSpaces(cmd, flg);
    istringstream   instr(cmd);
    int check(0);
    for (; getline(instr, toStr, ' '); )
    {
        if (!check)
        {
            params.first = toStr;
            check++;
            continue ;
        }
        save.push_back(toStr);
        if (check == 1 && flg)
        {
            getline(instr, toStr);
            if (toStr[0] != ':')
                toStr.insert(0, ":");
            save.push_back(toStr);
            break ;
        }
    }
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
        if (cmd[cmd.size() - 1] == '\n')
            cmd.erase(cmd.size() - 1);
        if (cmd[cmd.size() - 1] == '\r')
            cmd.erase(cmd.size() - 1);
        obj = placeParams(cmd);
    }
    Cmd command(obj, fd, ps, IP);
    command.executeCmd(clients[fd].second.first);
}

/*********************************** Commands Syntax *****************************************/

int    ValidString(const string s, bool flg)
{
    int i = 0;

    if (!flg && s[0] == ':')
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
    if (isdigit(vc[0][i]) || vc[0][0] == '-')
        throw runtime_error(": 432" + vc[0] + " :Erroneous Nickname\r\n");
    for (; i < vc[0].length(); i++)
        if (!(isalnum(vc[0][i]) || vc[0][i] == '_' || vc[0][i] == '-'))
            throw runtime_error(": 432" + vc[0] + " :Erroneous Nickname\r\n");

    if (i > 9)
        throw runtime_error(": 432 " + vc[0] + " :Erroneous Nickname\r\n");
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

void    toLowerString(string & s)
{
    for (unsigned int i(0); i < s.length(); i++)
        s[i] = tolower(s[i]);
}

void _send(int fd, string mess)
{
    send(fd, mess.c_str(), mess.length(), 0);
}

void serverReplyFormat(const int &fd, const pair<string, string>& userInfo, const cmdInfos& params)
{
    string save;

    for (unsigned int i(0); i < params.second.size(); i++)
    {
        save += params.second[i];
        if (i != params.second.size() - 1)
            save += " ";
    }
    _send(fd, ":" + userInfo.first + "!" + userInfo.second + "@localhost " + params.first + " " + save + "\r\n");
}
