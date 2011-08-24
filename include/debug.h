#ifndef DEBUG_H_INCLUDED
#include "include/Controller.h"
#define DEBUG_H_INCLUDED

#define STR(X) #X

#define TRACE_ENTER(CLASS, F) Controller::getController()->log(LL_TRACE, STR(CLASS), STR(CLASS)"::"STR(F) " entered");
#define TRACE_LEAVE(CLASS, F) Controller::getController()->log(LL_TRACE, STR(CLASS), STR(CLASS)"::"STR(F) " leaved");

#define LOG(LEVEL,CLASS,MSG) Controller::getController()->log(LEVEL, CLASS, MSG);
#define CRITICAL(CLASS, MSG) LOG(LL_CRITICAL,CLASS,MSG)
#define ERROR(CLASS, MSG) LOG(LL_ERROR,CLASS,MSG)
#define WARNING(CLASS, MSG) LOG(LL_WARNING,CLASS,MSG)
#define NOTICE(CLASS, MSG) LOG(LL_NOTICE,CLASS,MSG)
#define INFO(CLASS, MSG) LOG(LL_INFO,CLASS,MSG)
#define DEBG(CLASS, MSG) LOG(LL_DEBUG,CLASS,MSG)

#endif // DEBUG_H_INCLUDED
