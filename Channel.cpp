/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:47 by fraqioui          #+#    #+#             */
/*   Updated: 2023/12/09 10:15:36 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Channel.hpp"
#include"features/Cmd.hpp"

vector<Chan> Channel::channel;

Channel::Channel()
{

}

Channel::~Channel()
{

}

void Channel::setChannel(Chan & add)
{
    channel.push_back(add);
}

vector<Chan> & Channel::getChannel()
{
    return channel;
}

Chan::Chan(string CN, const string & name, int & fd)
{
    toLowerString(CN);
    channelName = CN;
    members[name] = pair<int, bool>(fd, true);
    LookForUser[fd] = name;
    modesStat['i'] = pair<bool, string>(false, "");
    modesStat['t'] = pair<bool, string>(false, "");
    modesStat['k'] = pair<bool, string>(false, "");
    modesStat['o'] = pair<bool, string>(false, "");
    modesStat['l'] = pair<bool, string>(false, "");
    ChannelLimit = 0;
}

Chan::~Chan()
{

}

const string&           Chan::getChannelName() const
{
    return channelName;
}

const string&           Chan::getTopic() const
{
    return topic;
}

modeInfo&         Chan::getModes()
{
    return modesStat;
}

memberInfo&  Chan::getMembers()
{
    return members;
}

const unsigned int &    Chan::getLimit() const
{
    return ChannelLimit;
}

map<int, string>& Chan::getMembersFromFD()
{
    return LookForUser;
}

vector<string>& Chan::getInviteD()
{
    return InviteD;
}

void    Chan::setChannelName(const string & N)
{
    channelName = N; 
}

void    Chan::setTopic(const string & T)
{
    topic = T;
}

void    Chan::setMember(const string & mem, const int & fd)
{
    members[mem] = pair<int, bool>(fd, false);
    LookForUser[fd] = mem;
}

void    Chan::setModesStat(char index, bool flg, string param)
{
    modesStat[index] = pair<bool, string>(flg, param);
}

void    Chan::setChannelLimit(const int & L)
{
    ChannelLimit = L;
}

void    Chan::setInviteD(const string & name)
{
    InviteD.push_back(name);
}

void    Chan::setChannelOper(string & mmbr, bool Set)
{
    members[mmbr].second = Set;
}

void Chan::removeClient(string & nm)
{
    members.erase(members.find(nm));
    map<int, string>::iterator t = LookForUser.begin();
    map<int, string>::iterator te = LookForUser.end();
    for (map<int, string>::iterator i = t; i != te; i++)
    {
        if (nm == i->second)
        {
            LookForUser.erase(i);
            return ;
        }
    }
}

unsigned int    ChannelExist(vector<Chan>& CurrentChannels, string & Name, string & client)
{
    unsigned int c(0), sz = CurrentChannels.size();

    toLowerString(Name);
    if (!sz)
        throw runtime_error(": 403 " + client + " " + Name + " :No such channel\r\n");
    for (; c < sz; c++)
    {
        if (CurrentChannels[c].getChannelName() == Name)
            break ;
        if (c == sz - 1)
            throw runtime_error(": 403 " + client + " " + Name + " :No such channel\r\n");
    }
    return c;
}

void    IsInChannel(Chan& CurrentChannel, int fd, bool flg)
{
    map<int, string> &trav = CurrentChannel.getMembersFromFD();
    ClientInfos client = Client::getClient();

    if (trav.find(fd) == trav.end())
        throw runtime_error(": 442 " + client[fd].second.first + " :You're not on that channel\r\n");

    if (flg)
    {
        memberInfo meM = CurrentChannel.getMembers();
        if (!(meM[trav[fd]].second))
            throw runtime_error(": 482 " + trav[fd] + " :You're not channel operator\r\n");
    }
}

void    IsUserInChannel(Chan& CurrentChannel, string & Name, bool flg)
{
    memberInfo trav = CurrentChannel.getMembers();

    if (trav.find(Name) == trav.end())
    {
        if (flg)
            throw runtime_error(": 441 " + Name + " :They are not on that channel\r\n");
    }
    else
    {
        if (!flg)
            throw runtime_error(": 443 " + Name + " :is already on channel\r\n");
    }
}
