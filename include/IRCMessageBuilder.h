#ifndef IRCMESSAGEBUILDER_H
#define IRCMESSAGEBUILDER_H
#include <string>
using std::string;

class IRCMessageBuilder
{
    public:
        static string pass(string password);
        static string nick(string nick);
        static string user(string user, string host, string server, string realname);
        static string pong(string msg);
        static string join(string channel);
        static string part(string channel);
        static string mode(string target, string modemask);
        static string quit(string message);
        static string privmsg(string target, string message);
    protected:
    private:
};

#endif // IRCMESSAGEBUILDER_H
