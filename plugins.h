#ifndef PLUGINS_H_INCLUDED
#define PLUGINS_H_INCLUDED

#include "include/hooks.h"

#undef LOG
#undef CRITICAL
#undef ERROR
#undef WARNING
#undef NOTICE
#undef INFO
#undef DEBUG

struct Hostmask_st {
    const char* nick;
    const char* user;
    const char* host;
};

// control functions
typedef void (*log_f_t)(Loglevel, const char*, const char*);
typedef void (*sendcmd_f_t)(const char*);
typedef void (*join_f_t)(const char*);
typedef void (*part_f_t)(const char*);
typedef void (*privmsg_f_t)(const char*,const char*);
typedef Hostmask_st* (*parse_hostmask_f_t)(const char*);

struct irc_st {
    sendcmd_f_t sendCmd;
    join_f_t join;
    part_f_t part;
    privmsg_f_t privmsg;

    parse_hostmask_f_t parseHostMask;
};


struct PluginController {
    log_f_t log;

    register_ping_t registerPingHook;
    register_join_t registerJoinHook;
    register_numeric_t registerNumericHook;

    irc_st *irc;

};

#endif // PLUGINS_H_INCLUDED
