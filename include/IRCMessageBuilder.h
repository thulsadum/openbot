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
    protected:
    private:
};

#endif // IRCMESSAGEBUILDER_H
