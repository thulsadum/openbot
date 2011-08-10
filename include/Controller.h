#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <libconfig.h++>
#include <list>
#include <string>

#include "include/Logger.h"

class Controller
{
    public:
        static Controller* getController();
        static void setConfig(libconfig::Config* config);

        /** Default destructor */
        virtual ~Controller();

        void run();
        void daemonize() const;

        void log(Loglevel level, string sClass, string message) const;
        void log(Loglevel level, string message) const;

        void addLogger(string target, int logmask, string format = "{DATE}\t{LEVEL}\t{CLASS}\t=> {MESSAGE}", string date_format = "%c");


    protected:
    private:
        static Controller* ctrl;
        static libconfig::Config* cfg;

        Controller(libconfig::Config* config);

        libconfig::Config* m_config;
        list<Logger> m_logger;
};

#endif // CONTROLLER_H
