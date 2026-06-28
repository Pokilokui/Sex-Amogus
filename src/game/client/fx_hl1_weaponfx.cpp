//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Game-specific impact effect hooks
//
//=============================================================================//

#include "cbase.h"
#include "fx_impact.h"
#include "tempent.h"
#include "c_te_effect_dispatch.h"
#include "c_te_legacytempents.h"

//-----------------------------------------------------------------------------
// Purpose: Handle weapon effect callbacks
//-----------------------------------------------------------------------------
void HL1_EjectBrass(int shell, const CEffectData& data)
{
	C_BasePlayer* pPlayer = C_BasePlayer::GetLocalPlayer();

	if (!pPlayer)
		return;

	tempents->HL1EjectBrass(data.m_vOrigin, data.m_vAngles, data.m_vStart, shell);
}

void HL1_FX_EjectBrass_Shell_Callback(const CEffectData& data)
{
	HL1_EjectBrass(m_pHL1Shell, data);
}

void HL1_FX_EjectBrass_ShotgunShell_Callback(const CEffectData& data)
{
	HL1_EjectBrass(m_pHL1ShotgunShell, data);
}


DECLARE_CLIENT_EFFECT("EjectBrass_Shell", HL1_FX_EjectBrass_Shell_Callback);
DECLARE_CLIENT_EFFECT("EjectBrass_ShotgunShell", HL1_FX_EjectBrass_ShotgunShell_Callback);
