#include "include/Logger.h"
#include "include/helper.h"

#include <ctime>
#include <iostream>

string Logger::strLoglevel(Loglevel level) {
    switch(level){
        case  LL_CRITICAL:
            return "CRITICAL";
        case  LL_ERROR:
            return "Error";
        case  LL_WARNING:
            return "warning";
        case  LL_NOTICE:
            return "notice";
        case  LL_INFO:
            return "info";
        case  LL_DEBUG:
            return "debug";
        case  LL_TRACE:
            return "trace";
        case  LL_RAW:
            return "RAW";
        default:
            return "unknown";
    }
}

Logger::Logger()
{
    m_out = &std::cerr;
    m_format = "{DATE}\t{LEVEL}\t{CLASS}\t=> {MESSAGE}";
    m_dateformat = "%c";
    m_mask = LL_LEASTWARN;
}

Logger::~Logger(){}

ostream* Logger::getStream() const {
    return this->m_out;
}
void Logger::setStream(ostream* stream){
    this->m_out = stream;
}

string Logger::getFormat() const {
    return this->m_format;
}
void Logger::setFormat(string format){
    this->m_format = format;
}

string Logger::getDateFormat() const {
    return this->m_dateformat;
}
void Logger::setDateFormat(string format) {
    this->m_dateformat = format;
}

int Logger::getLevelMask() const {
    return this->m_mask;
}
void Logger::setLevelMask(int mask) {
    this->m_mask = mask;
}


void Logger::log(Loglevel level, string message) const{
    this->log(level, "misc", message);
}

void Logger::log(Loglevel level, string sClass, string message) const {
    if(!this->isLevel(level)) return;
    char* pcDate = new char[256];
    time_t now;
    time(&now);


    int dlen = strftime(pcDate, 256, this->m_dateformat.c_str(), localtime(&now));

    pcDate[dlen] = 0;

    message = replaceAll(m_format, "{MESSAGE}", message);
    message = replaceAll(message, "{DATE}", pcDate);
    message = replaceAll(message, "{CLASS}", sClass);
    message = replaceAll(message, "{LEVEL}", Logger::strLoglevel(level));

    (*this->m_out) << message << endl;

    delete pcDate;
}

void Logger::mark() const {
    this->mark("\n--- MARK ---\n");
}

void Logger::mark(string message) const {
    (*this->m_out) << message << endl;
}


bool Logger::isLevel(Loglevel level) const {
    return (m_mask & level);
}

