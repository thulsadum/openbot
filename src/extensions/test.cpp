#include "plugins.h"
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

    void ping(const char*);

    PluginController* ctrl;

    void ping(const char* msg) {
        ctrl->irc->sendCmd("PRIVMSG #openbot :peng! :D");
    }

    void join(const char* who, const char* channel){
        ctrl->log(LL_TRACE, "testplugin.so", "join");
        ostringstream msg;

        msg << "hello " << ctrl->irc->parseHostMask(who)->nick << " (" << ctrl->irc->parseHostMask(who)->user << "[at]" << ctrl->irc->parseHostMask(who)->host << ")";

        ctrl->irc->privmsg(channel, msg.str().c_str());
    }

extern "C" {
    void setup(PluginController* cn)  {
        ctrl = cn;
        ctrl->registerPingHook(ping);
        ctrl->registerJoinHook(join);
    }
}
