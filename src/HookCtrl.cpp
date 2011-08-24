#define HC_IMPL
#include "include/HookCtrl.h"

HookCtrl::HookCtrl()
{
    this->m_ping =  new vector<ping_hook>;
    this->m_join =  new vector<join_hook>;
    this->m_numeric =  new vector<numeric_hook>;
}

HOOK(Ping, ping_hook, m_ping)
HOOK(Join, join_hook, m_join)
HOOK(Numeric, numeric_hook, m_numeric)
