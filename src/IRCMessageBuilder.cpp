#include "include/IRCMessageBuilder.h"
#include <sstream>

using std::ostringstream;

string IRCMessageBuilder::pass(string password) {
    ostringstream msg;
    msg << "PASS " << password;
    return msg.str();
}

string IRCMessageBuilder::nick(string nick) {
    ostringstream msg;
    msg << "NICK " << nick;
    return msg.str();
}

string IRCMessageBuilder::user(string user, string host, string server, string realname) {
    ostringstream msg;
    msg << "USER " << user << " "
    << host << " "
    << server << " :"
    << realname;
    return msg.str();
}
