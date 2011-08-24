#include "include/Controller.h"
#include "include/helper.h"
#include "include/debug.h"
#include "include/IRCMessageBuilder.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/select.h>

Controller* Controller::ctrl = 0;
libconfig::Config*  Controller::cfg = 0;


Controller::Controller(libconfig::Config* config)
{
    this->m_config = config;
}

Controller::~Controller()
{
    //dtor
}

void Controller::setConfig(libconfig::Config* config){
    Controller::cfg = config;
}

Controller* Controller::getController(){
    if(Controller::ctrl == NULL) Controller::ctrl = new Controller(Controller::cfg);
    return Controller::ctrl;
}

void Controller::daemonize() const {
    int pid = fork();
    // in child
    if(pid){
        return;
    }
    exit(0);
}

void Controller::addLogger(string target, int logmask, string format, string date_format) {
    Logger logger;
    ostream* stream;
    std::ostringstream msg;

    if(target.compare("STDOUT") == 0)
        stream = &std::cout;
    else if(target.compare("STDLOG") == 0)
        stream = &std::clog;
    else if(target.compare("STDERR") == 0)
        stream = &std::cerr;
    else{
        stream = new ofstream();
        ((ofstream*)stream)->open(target.c_str(), ios_base::app);
    }

    logger.setStream(stream);
    logger.setLevelMask(logmask);
    logger.setFormat(format);
    logger.setDateFormat(date_format);

    this->m_logger.push_back(logger);
    msg << "added Logger '"<<target<<"'";
    log(LL_INFO, "Controller::addLogger", msg.str());
}

void Controller::log(Loglevel level, string message) const {
    this->log(level, "misc", message);
}

void Controller::log(Loglevel level, string sClass, string message) const {
    list<Logger>::const_iterator i = this->m_logger.begin();
    while(i != this->m_logger.end()){
        i->log(level, sClass, message);
        i++;
    }
}

IRC* Controller::getIRC() const {
    return this->m_irc;
}


void Controller::run() {
    TRACE_ENTER(Controller, run)

    while(isRunning()){
        getIRC()->poll();
    }

    TRACE_LEAVE(Controller, run)
}

void Controller::prepare() {
    TRACE_ENTER(Controller, prepare)
    // set up logger
    const libconfig::Setting& root = this->m_config->getRoot();
    const libconfig::Setting& logging = root["logging"];

    std::ostringstream msg;

    // setting up loggers
    if(logging.isList()){
        int logmask;
        string logtarget;
        string logformat;
        string logdateformat;
        for(int i=0; i<logging.getLength(); i++){
            if(logging[i].lookupValue("target", logtarget)){
                msg.str("");
                msg << "target-"<< i <<" is " << logtarget;

                log(LL_DEBUG, "Controller::prepare", msg.str());
            }
            else{
                 log(LL_WARNING, "Controller::prepare", "musst specify a target for loggger!");
                 continue;
            }

            if(logging[i].lookupValue("logmask", logmask)){
                msg.str("");
                msg << "target-"<< i <<" is 0x" << hex << logmask;

                log(LL_DEBUG, "Controller::prepare", msg.str());
            }
            else{
                 log(LL_WARNING, "Controller::prepare", "musst specify a logmask for loggger!");
                 continue;
            }

            if(!logging[i].lookupValue("format", logformat)){
                msg.str("");
                msg<<"no format specified for target " << logtarget << " - using default format";
                log(LL_INFO, "Controller::prepare", msg.str());
                logformat = "{DATE}\t{LEVEL}\t{CLASS}\t=> {MESSAGE}";
            }

            if(!logging[i].lookupValue("date-format", logdateformat)){
                msg.str("");
                msg<<"no date-format specified for target " << logtarget << " - using default format";
                log(LL_INFO, "Controller::prepare", msg.str());
                logdateformat = "%c";
            }

            addLogger(logtarget, logmask, logformat, logdateformat);

        }
    } else {
        log(LL_WARNING, "Controlller::prepare", "Errornous configuration section - logging musst be a list. Logging disabled entirely. I wonder anyone will ever read this message?");
    }

    // set up irc connection
    log(LL_INFO, "Controller::prepare", "setting up irc..");
    this->m_irc = new IRC();

    string nick, user, realname;
    this->m_config->lookupValue("info.nick", nick);
    msg.str("");
    msg << "bot nick is " << nick;
    log(LL_INFO, "Controller::prepare", msg.str());
    this->m_config->lookupValue("info.user", user);
    msg.str("");
    msg << "bot user is " << user;
    log(LL_INFO, "Controller::prepare", msg.str());
    this->m_config->lookupValue("info.realname", realname);
    msg.str("");
    msg << "bot realname is " << realname;
    log(LL_INFO, "Controller::prepare", msg.str());

    this->getIRC()->setNick(nick);
    this->getIRC()->setUser(user);
    this->getIRC()->setRealname(realname);

    const libconfig::Setting &servers = root["network"]["servers"];
    string host;
    int port;
    bool success = false;

    for(int i=0; i<servers.getLength(); i++){
        servers[i].lookupValue("host", host);
        servers[i].lookupValue("port", port);
        if( getIRC()->connect(host, (unsigned short) port) ) {
            success = true;
            break;
        }
    }

    if(success){
       INFO("Controller::prepare", "successfuly connected!")

       int maxsend;
       double maxsendint;
       if(m_config->lookupValue("security.max-messages", maxsend)) getIRC()->setMaxMessages(maxsend);
       if(m_config->lookupValue("security.max-messages-interval", maxsendint)) getIRC()->setResetInterval(maxsendint);

       if(m_config->exists("info.autojoin")){
           const libconfig::Setting &channels = m_config->lookup("info.autojoin");
           string channel;
            for(int i = 0; i<channels.getLength(); i++) {
                channel = channels[i].c_str();
                msg.str("");
                msg << "joining " << channel;
                NOTICE("Controller::prepare", msg.str());
                getIRC()->sendCmd(IRCMessageBuilder::join(channel));
            }
       }
       string modes;
       if(m_config->lookupValue("info.automode", modes)) getIRC()->sendCmd(IRCMessageBuilder::mode(getIRC()->getNick(), modes));
    } else
        CRITICAL("Controller::prepare", "could not connect to any server!")


    m_running = success;

    TRACE_LEAVE(Controller, prepare)
}

bool Controller::isRunning() const {
    return this->m_running;
}

void Controller::stop() {
    this->m_running = false;
}
