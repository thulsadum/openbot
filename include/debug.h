#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define STR(X) #X

#define TRACE_ENTER(CLASS, F) Controller::getController()->log(LL_TRACE, STR(CLASS), STR(CLASS)"::"STR(F) " entered");
#define TRACE_LEAVE(CLASS, F) Controller::getController()->log(LL_TRACE, STR(CLASS), STR(CLASS)"::"STR(F) " leaved");

#endif // DEBUG_H_INCLUDED
