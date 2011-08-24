#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <libconfig.h++>
#include <list>
#include <string>
#include <map>

#include "include/Logger.h"
#include "include/IRC.h"
#include "include/HookCtrl.h"

using std::map;

typedef map<string, void*> MapLib;

class Controller
{
    public:
        static Controller* getController();
        static void setConfig(libconfig::Config* config);

        /** Default destructor */
        virtual ~Controller();

        void prepare();
        void run();
        void daemonize() const;

        void log(Loglevel level, string sClass, string message) const;
        void log(Loglevel level, string message) const;

        void addLogger(string target, int logmask, string format = "{DATE}\t{LEVEL}\t{CLASS}\t=> {MESSAGE}", string date_format = "%c");

        IRC *getIRC() const;
        HookCtrl *getHookControl() const;

        bool isRunning() const;
        void stop();
        void stop(string reason);

        void loadLib(string lib);
        void unloadLib(string lib);


    protected:
    private:
        static Controller* ctrl;
        static libconfig::Config* cfg;

        Controller(libconfig::Config* config);

        libconfig::Config* m_config;
        list<Logger> m_logger;
        IRC *m_irc;
        HookCtrl *m_hooks;
        bool m_running;

        MapLib *m_libs;
};

typedef void (*lib_entry_fn_t)(PluginController*);

#endif // CONTROLLER_H
