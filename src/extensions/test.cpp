#include "plugins.h"


    void ping(char*);

    //PluginController* ctrl;

extern "C"    void setup(PluginController* cn)  {
        //ctrl = cn;
        //ctrl->registerPingHook(ping);
    }

    void ping(char* msg) {
        //ctrl->getIRC()->sendCmd("PRIVMSG #openbot :peng! :D");
    }
