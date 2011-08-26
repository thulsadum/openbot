#define HELPER_IMPL

#include "include/helper.h"
#include "include/debug.h"
#include <sstream>
#include <string>

using std::ostringstream;
using std::string;
// some helper functions
string replaceAll(string haystack, string needle, string replacement){
    int start = 0;
    while((start=haystack.find(needle)) >= 0){
        haystack=haystack.replace(start,needle.length(), replacement);
    }
    return haystack;
}

vector<string> split(string input, string delimeter) {
    vector<string> args;
    // spliting message into chunks separated by spaces
    int start=0, end;
    while((end = input.find(" ", start)) >= 0) {
        args.push_back(input.substr(start,end - start));
        start = end + 1;
    }
    args.push_back(input.substr(start, input.size() - start));
    return args;
}

string join(vector<string> input, int start, int end, string glue) {
     ostringstream tmp;
     if(start > end) return "";
     if(start < 0) return "";
     if((unsigned int)end > input.size()) return "";

     for(int i = start; i < end; i++) {
        tmp << input[i];
        if(i < end-1) tmp<<glue;
     }
     return tmp.str();
}

string join(vector<string> input, string glue) {
    return join(input, 0, input.size(), glue);
}

HHOOK(Ping, ping_hook)
HHOOK(Numeric, numeric_hook)
HHOOK(Join, join_hook)

void _log(Loglevel level, const char * module, const char* message) {
    TRACE_ENTER(,_log)
    Controller::getController()->log(level, module, message);
    TRACE_LEAVE(,_log)
}

void mkpluginctrl(PluginController* ppc){
    TRACE_ENTER(, mkpluginctrl)

    irc_st *irc = new irc_st;

    ppc->log = _log;

    ppc->registerPingHook = _registerPingHook;
    ppc->registerNumericHook = _registerNumericHook;
    ppc->registerJoinHook = _registerJoinHook;

    irc->sendCmd = _sendcmd;
    irc->join = _join;
    irc->part = _part;
    irc->privmsg = _privmsg;
    irc->parseHostMask = _parse_hostmask;

    ppc->irc = irc;

    ostringstream msg;
    msg << "address of ppc 0x" << hex << ppc;
    DEBG("::mkpluginctrl", msg.str());

    TRACE_LEAVE(, mkpluginctrl)
}

void _sendcmd(const char* message) {
    Controller::getController()->getIRC()->sendCmd(message);
}

void _join(const char* channel) {
    Controller::getController()->getIRC()->join(channel);
}
void _part(const char* channel) {
    Controller::getController()->getIRC()->part(channel);
}
void _privmsg(const char* target, const char* message) {
    Controller::getController()->getIRC()->privmsg(target, message);
}

Hostmask_st *_parse_hostmask(const char* mask) {
    Hostmask_st *pmask = new Hostmask_st;
    string smask = mask;
    int nickend, userend;

    char *nick, *user, *host;

    if((nickend=smask.find("!")) >= 0) {
        nick = new char[nickend];
        for(int i=0; i<nickend; i++)
            nick[i] = smask[i];
        pmask->nick = nick;
    }
    if(nickend >= 0 && (userend=smask.find("@")) >= 0) {
        user = new char[userend - nickend -1];
        for(int i=nickend+1; i<userend; i++)
            user[i - nickend - 1] = smask[i];
        pmask->user = user;
    }
    if(userend >= 0) {
        host = new char[smask.size() - userend -1];
        for(int i=userend+1; i<(int)smask.size(); i++)
            host[i - userend - 1] = smask[i];
        pmask->host = host;
    }

    return pmask;
}
