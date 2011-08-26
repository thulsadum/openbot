#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "include/debug.h"
#include "plugins.h"
#include "include/Controller.h"

#include <string>
#include <vector>
using namespace std;

/** replaces all occurences of an string in a string
  * @param haystack string in which will be searched
  * @param needle string for which will be searched
  * @param replacemant string which will replace the needles
  * @return string with replacements
  */
string replaceAll(string haystack, string needle, string replacement);

vector<string> split(string input, string delimeter);
string join(vector<string> input, int start, int end , string glue);
string join(vector<string> input, string glue);


#define HHOOK(NAME,TYPE) void _register##NAME##Hook(TYPE callback);

HHOOK(Ping,ping_hook)
HHOOK(Join,ping_hook)
HHOOK(Numeric,ping_hook)

void _log(Loglevel level, const char * module, const char* message);

void _sendcmd(const char* message);
void _join(const char* channel);
void _part(const char* channel);
void _privmsg(const char* target, const char* message);
Hostmask_st *_parse_hostmask(const char* mask);

#undef HHOOK

#ifdef HELPER_IMPL

#define HHOOK(NAME, TYPE) void _register##NAME##Hook(TYPE callback){ TRACE_ENTER(,_register##NAME##Hook) Controller::getController()->getHookControl()->register##NAME##Hook(callback); TRACE_LEAVE(,_register##NAME##Hook)}

#endif

void mkpluginctrl(PluginController * ppc);

#endif // HELPER_H_INCLUDED
