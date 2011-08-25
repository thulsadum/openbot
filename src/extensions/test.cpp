#include "plugins.h"
#include <iostream>
using namespace std;

    void ping(char*);

    PluginController* ctrl;

    void ping(char* msg) {
        //ctrl->getIRC()->sendCmd("PRIVMSG #openbot :peng! :D");
    }

extern "C" {
    void setup(PluginController* cn)  {
        cout << "in setup" << endl;
        ctrl = cn;
        ctrl->registerPingHook(NULL);
    }
}
