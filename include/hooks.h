#ifndef HOOKS_H_INCLUDED
#define HOOKS_H_INCLUDED

typedef void (*ping_hook)(char* from);
typedef void (*numeric_hook)(int numeric, char** args);
typedef void (*join_hook)(char* channel);

#endif // HOOKS_H_INCLUDED
