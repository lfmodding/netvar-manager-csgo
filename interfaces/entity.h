#pragma once
#include "netvar.h"

class CEntity
{
public:
	NETVAR(health, "CBasePlayer->m_iHealth", int)
	NETVAR(observerMode, "CBasePlayer->m_iObserverMode", int)
	NETVAR(flags, "CBasePlayer->m_fFlags", bool)
};