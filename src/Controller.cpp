#include "include/Controller.h"

#include "include/debug.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

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

    if(target.compare("STDOUT") == 0)
        stream = &std::cout;
    else if(target.compare("STDLOG") == 0)
        stream = &std::clog;
    else{
        stream = new ofstream();
        ((ofstream*)stream)->open(target.c_str(), ios_base::app);
    }

    logger.setStream(stream);
    logger.setLevelMask(logmask);
    logger.setFormat(format);
    logger.setDateFormat(date_format);

    this->m_logger.push_back(logger);
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

void Controller::run() {
    TRACE_ENTER(Controller, run)

    TRACE_LEAVE(Controller, run)
}
