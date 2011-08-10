#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define STR(X) #X

#define _TENTER(CLASS, F) Controller::getController()->log(LL_TRACE, STR(CLASS), STR(F) " entered");
#define _TLEAVE(CLASS, F) Controller::getController()->log(LL_TRACE, STR(CLASS), STR(F) " leaved");

#define TENTER(CLASS) _TENTER(CLASS, __FUNCTION__)
#define TLEAVE(CLASS) _TLEAVE(CLASS, __FUNCTION__)

#endif // DEBUG_H_INCLUDED
