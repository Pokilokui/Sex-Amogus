// XenLight / LightStalk
// Code inspired by the npc_lightstalk from the hl2 beta
// and xen_plantlight from hl source.
// Rewritten and optimised for Source 2013 sp by Mazdo.
// Doesn't use any leaked assets, light.mdl is a Half-Life Source model.
// The Xen Plant Light is a plant from Xen that emits light when touched.
// When touched, the plant turns off it's light and retracts into it's base.
// WARNING: The light will only work if you target a light entity in the Hammer
// in the "target path corner" of the npc properties.

#ifndef	XENLIGHT_H
#define	XENLIGHT_H

#include "ai_basenpc.h"
#include "entityoutput.h"

// Sprite fade in/out
enum XenlightFade_t
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
};

class CSprite;

class CNPC_XenLight : public CAI_BaseNPC
{
public:
	DECLARE_CLASS( CNPC_XenLight, CAI_BaseNPC );

	void				Spawn(void);
	void				Precache(void);
	void				Touch(CBaseEntity* pOther);
	void				Think(void);
	void				LightRise(void);
	void				LightLower(void);

	// Lighting
	void				LightOn(void);
	void				LightOff(void);

	COutputEvent		m_OnRise;
	COutputEvent		m_OnLower;

private:
	float				m_flHideEndTime;
	float				m_flStartFadeTime;
	XenlightFade_t		m_nFadeDir;
	CSprite*			m_pGlow;

public:
	DECLARE_DATADESC();
};

#endif