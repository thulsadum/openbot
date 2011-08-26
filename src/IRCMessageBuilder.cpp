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

string IRCMessageBuilder::pong(string daemon) {
    ostringstream msg;
    msg << "PONG " << daemon;
    return msg.str();

}

string IRCMessageBuilder::join(string channel) {
    ostringstream msg;
    msg << "JOIN " << channel;
    return msg.str();
}

string IRCMessageBuilder::part(string channel) {
    ostringstream msg;
    msg << "PART " << channel;
    return msg.str();
}

string IRCMessageBuilder::mode(string target, string modemask) {
    ostringstream msg;
    msg << "MODE " << target << " " << modemask;
    return msg.str();

}

string IRCMessageBuilder::quit(string message) {
    ostringstream msg;
    msg << "QUIT :" << message;
    return msg.str();
}

string IRCMessageBuilder::privmsg(string target, string message) {
    ostringstream msg;
    msg << "PRIVMSG " << target <<" :" << message;
    return msg.str();
}
