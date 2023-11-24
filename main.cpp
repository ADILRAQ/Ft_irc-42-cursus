
#include"Client.hpp"
#include"Channel.hpp"
#include"features/Cmd.hpp"

// replace 1 by client fd

int main()
{
    string us = "sf d d";
    placeCmds(us, 0);

    
    // string s = "JOIN #kjgj";
    // placeCmds(s, 0);
    // string k = "MODE #kjgj +l 89";
    // placeCmds(k, 0);
    // string n = "USER new";
    // placeCmds(n, 2);
    // string p = "JOIN #kjgj";
    // placeCmds(p, 2);
    // string o = "KICK #kjgj tima";
    // placeCmds(o, 2);
    // string n = "USER new";
    // string j = "JOIN #kjgj";
    // placeCmds(j, 1);
    // cout << s <<".\n";
}
