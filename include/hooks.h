#ifndef HOOKS_H_INCLUDED
#define HOOKS_H_INCLUDED

// hook callbacks
typedef void (*ping_hook)(char* from);
typedef void (*numeric_hook)(int numeric, char* args);
typedef void (*join_hook)(char* who, char* channel);

// register function pointers
typedef void (*register_ping_t)(ping_hook);
typedef void (*register_numeric_t)(numeric_hook);
typedef void (*register_join_t)(join_hook);

struct PluginController {
    register_ping_t registerPingHook;
//    register_join_t registerJoinHook;
//    register_numeric_t registerNumericHook;
};
#endif // HOOKS_H_INCLUDED
