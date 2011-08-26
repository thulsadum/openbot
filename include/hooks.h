#ifndef HOOKS_H_INCLUDED
#define HOOKS_H_INCLUDED

#include "include/Logger.h"


// hook callbacks
typedef void (*ping_hook)(const char* from);
typedef void (*numeric_hook)(int numeric, int argc, const char** args);
typedef void (*join_hook)(const char* who, const char* channel);

// register function pointers
typedef void (*register_ping_t)(ping_hook);
typedef void (*register_numeric_t)(numeric_hook);
typedef void (*register_join_t)(join_hook);


#endif // HOOKS_H_INCLUDED
