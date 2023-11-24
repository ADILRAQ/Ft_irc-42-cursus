/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:47 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/24 09:12:28 by fraqioui         ###   ########.fr       */
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

void Channel::setChannel(const Chan & add)
{
    channel.push_back(add);
}

const vector<Chan> & Channel::getChannel()
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

void    Chan::removeMember(const string & name)
{
    members.erase(members.find(name));
    map<int, string>::iterator it = LookForUser.begin();
    map<int, string>::iterator ite = LookForUser.end();
    for (map<int, string>::iterator t = it; t != ite; t++)
    {
        if (it->second == name)
        {
            LookForUser.erase(it);
            break ;
        }
    }
}

unsigned int    ChannelExist(vector<Chan>& CurrentChannels, string & Name)
{
    unsigned int c(0), sz = CurrentChannels.size();

    toLowerString(Name);
    if (!sz)
        throw runtime_error("403\n");
    for (; c < sz; c++)
    {
        if (CurrentChannels[c].getChannelName() == Name)
            break ;
        if (c == sz - 1)
            throw runtime_error("403\n");
    }
    return c;
}

void    IsInChannel(Chan& CurrentChannel, int fd, bool flg)
{
    map<int, string> trav = CurrentChannel.getMembersFromFD();
    if (trav.find(fd) == trav.end())
        throw runtime_error("442\n");

    if (flg)
    {
        memberInfo meM = CurrentChannel.getMembers();
        if (!(meM[trav[fd]].second))
            throw runtime_error("482\n");
    }
}

void    IsUserInChannel(Chan& CurrentChannel, string & Name)
{
    memberInfo trav = CurrentChannel.getMembers();
    if (trav.find(Name) != trav.end())
        throw runtime_error("443\n");
}
