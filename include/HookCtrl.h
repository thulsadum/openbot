#ifndef HOOKCTRL_H
#define HOOKCTRL_H

#include "include/hooks.h"

#include <vector>
using std::vector;

#define HOOK(NAME, TYPE) void register##NAME##Hook(TYPE); vector<TYPE> *get##NAME##Hooks() const;

class HookCtrl
{
    public:
        /** Default constructor */
        HookCtrl();

        // here come the hooks
        HOOK(Ping, ping_hook)
        HOOK(Join, join_hook)
        HOOK(Numeric, numeric_hook)


    protected:
    private:
        vector<ping_hook> *m_ping;
        vector<join_hook> *m_join;
        vector<numeric_hook> *m_numeric;
};

#undef HOOK

#ifdef HC_IMPL
#define HOOK(NAME, TYPE, MEMBER) \
    void HookCtrl::register##NAME##Hook(TYPE cb) { MEMBER->push_back(cb); } \
    vector<TYPE> *HookCtrl::get##NAME##Hooks() const { return MEMBER; }
#endif

#endif // HOOKCTRL_H
