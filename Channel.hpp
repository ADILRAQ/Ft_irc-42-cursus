/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:14:52 by fraqioui          #+#    #+#             */
/*   Updated: 2023/11/25 16:15:21 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include"header.hpp"
#include"Client.hpp"

typedef map<string , pair<int, bool> > memberInfo;
typedef map<char, pair<bool, string> > modeInfo;

class Chan
{
private:
        string                          channelName;
        string                          topic;
        memberInfo                      members;
        map<int, string>                LookForUser;  
        modeInfo                        modesStat;
        unsigned int                    ChannelLimit;

public:
        Chan(string CN, const string & name, int & fd);
        ~Chan();

        const string&           getChannelName() const;
        const string&           getTopic() const;
        const unsigned int &    getLimit() const;
        map<int, string>&       getMembersFromFD();
        modeInfo&               getModes();
        memberInfo&             getMembers();

        void    setChannelName(const string & N);
        void    setChannelLimit(const int & L);
        void    setTopic(const string & T);
        void    setMember(const string & mem, const int & fd);
        void    setModesStat(char index, bool flg, string param);
        void    setChannelOper(string & mmbr, bool Set);
        void    removeClient(string & nm);
};

class Channel
{
private:
        static vector<Chan> channel;

public:
        Channel();
        ~Channel();

        static void setChannel(Chan & add);
        static vector<Chan> & getChannel();
};

/************************ Get Channels Data && Checking *************************/

unsigned int    ChannelExist(vector<Chan>& CurrentChannels, string & Name, string & client);
void            IsInChannel(Chan& CurrentChannel, int fd, bool flg);
void            IsUserInChannel(Chan& CurrentChannel, string & Name, bool flg);
