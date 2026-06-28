// XenLight / LightStalk
// Code inspired by the npc_lightstalk from the hl2 beta
// and xen_plantlight from hl source.
// Rewritten and optimised for Source 2013 sp by Mazdo.
// Doesn't use any leaked assets, light.mdl is a Half-Life Source model.
// The Xen Plant Light is a plant from Xen that emits light when touched.
// When touched, the plant turns off it's light and retracts into it's base.
// WARNING: The light will only work if you target a light entity in the Hammer
// in the "target path corner" of the npc properties.

#include "cbase.h"
#include "npc_xenlight.h"
#include "sprite.h"
#include "eventqueue.h"

LINK_ENTITY_TO_CLASS( npc_xenlight, CNPC_XenLight );
LINK_ENTITY_TO_CLASS( xen_plantlight, CNPC_XenLight ); // HL: Source Support

BEGIN_DATADESC( CNPC_XenLight )

DEFINE_FIELD( m_pGlow, FIELD_CLASSPTR ),
DEFINE_FIELD( m_flStartFadeTime, FIELD_TIME ),
DEFINE_FIELD( m_nFadeDir, FIELD_INTEGER ),
DEFINE_FIELD( m_flHideEndTime, FIELD_TIME ),

DEFINE_OUTPUT( m_OnRise, "OnRise" ),
DEFINE_OUTPUT( m_OnLower, "OnLower" ),

END_DATADESC()

// Precache
void CNPC_XenLight::Precache(void)
{
	PrecacheModel( "models/light.mdl" );
	PrecacheModel( "sprites/glow03.vmt" );
}

// Spawn
void CNPC_XenLight::Spawn(void)
{
	Precache();
	SetModel( "models/light.mdl" );

	SetMoveType(MOVETYPE_NONE);
	SetSolid(SOLID_BBOX);
	AddSolidFlags(FSOLID_TRIGGER);
	SetActivity(ACT_IDLE);
	SetNextThink(gpGlobals->curtime + 0.1f);

	m_pGlow = CSprite::SpriteCreate("sprites/glow03.vmt", GetLocalOrigin() + Vector(0, 0, (WorldAlignMins().z + WorldAlignMaxs().z) * 0.5), false);
	m_pGlow->SetTransparency(kRenderGlow, m_clrRender->r, m_clrRender->g, m_clrRender->b, m_clrRender->a, kRenderFxGlowShell);
	m_pGlow->SetScale(1.0);
	m_pGlow->SetAttachment(this, 1);
	LightRise();
}

// Activity
void CNPC_XenLight::Think(void)
{
	StudioFrameAdvance();
	SetNextThink(gpGlobals->curtime + 0.1f);

	switch (GetActivity())
	{
	case ACT_CROUCH:
		if (IsActivityFinished())
		{
			SetActivity(ACT_CROUCHIDLE);
			LightOff();
		}
		break;

	case ACT_CROUCHIDLE:
		if (gpGlobals->curtime > m_flHideEndTime)
		{
			SetActivity(ACT_STAND);
			LightRise();
			LightOn();
		}
		break;

	case ACT_STAND:
		if (IsActivityFinished())
		{
			SetActivity(ACT_IDLE);
		}
		break;

	case ACT_IDLE:
	default:
		break;
	}

	if (m_nFadeDir && m_pGlow)
	{
		float flFadePercent = (gpGlobals->curtime - m_flStartFadeTime) / 2;

		if (flFadePercent > 1)
		{
			m_nFadeDir = FADE_NONE;
		}
		else
		{
			if (m_nFadeDir == FADE_IN)
			{
				m_pGlow->SetBrightness(120 * flFadePercent);
			}
			else
			{
				m_pGlow->SetBrightness(0);
			}
		}
	}
}

// When the player player touch the entity
void CNPC_XenLight::Touch(CBaseEntity* pOther)
{
	if (pOther->IsPlayer())
	{
		m_flHideEndTime = gpGlobals->curtime + 5;
		if (GetActivity() == ACT_IDLE || GetActivity() == ACT_STAND)
		{
			SetActivity(ACT_CROUCH);
			LightLower();
		}
	}
}

// Sprite Fade in and out
void CNPC_XenLight::LightRise(void)
{
	m_OnRise.FireOutput(this, this);
	m_nFadeDir = FADE_IN;
	m_flStartFadeTime = gpGlobals->curtime;
}

void CNPC_XenLight::LightLower(void)
{
	m_OnLower.FireOutput(this, this);
	m_nFadeDir = FADE_OUT;
	m_flStartFadeTime = gpGlobals->curtime;
}

// Light On and Light Off
void CNPC_XenLight::LightOn(void)
{
	variant_t Value;
	g_EventQueue.AddEvent(STRING(m_target), "TurnOn", Value, 0, this, this);

	if (m_pGlow)
		m_pGlow->RemoveEffects(EF_NODRAW);
}


void CNPC_XenLight::LightOff(void)
{
	variant_t Value;
	g_EventQueue.AddEvent(STRING(m_target), "TurnOff", Value, 0, this, this);

	if (m_pGlow)
		m_pGlow->AddEffects(EF_NODRAW);
}