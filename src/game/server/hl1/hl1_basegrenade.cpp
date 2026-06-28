//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//


#include "cbase.h"
#include "decals.h"
#include "basecombatcharacter.h"
#include "shake.h"
#include "engine/IEngineSound.h"
#include "soundent.h"
#include "EntityList.h"
#include "hl1_basegrenade.h"


//extern short	g_sModelIndexFireball;		// (in combatweapon.cpp) holds the index for the fireball 
//extern short	g_sModelIndexWExplosion;	// (in combatweapon.cpp) holds the index for the underwater explosion

static int s_nFireballSprite = 0;
static int s_nWaterSprite = 0;
short s_nSteamSprite;

unsigned int CHL1BaseGrenade::PhysicsSolidMaskForEntity(void) const
{
	return BaseClass::PhysicsSolidMaskForEntity() | CONTENTS_HITBOX;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHL1BaseGrenade::Precache()
{
	BaseClass::Precache();

	PrecacheScriptSound("HL1_BaseGrenade.Explode");

	s_nFireballSprite = PrecacheModel("sprites/hl1/zerogxplode.vmt");
	s_nWaterSprite = PrecacheModel("sprites/WXplo1.vmt");
	s_nSteamSprite = PrecacheModel("sprites / hl1 / steam1.vmt");
}


void CHL1BaseGrenade::Explode(trace_t* pTrace, int bitsDamageType)
{
	float		flRndSound;// sound randomizer

	SetModelName(NULL_STRING);//invisible
	AddSolidFlags(FSOLID_NOT_SOLID);

	m_takedamage = DAMAGE_NO;

	// Pull out of the wall a bit
	if (pTrace->fraction != 1.0)
	{
		SetLocalOrigin(pTrace->endpos + (pTrace->plane.normal * 0.6));
	}

	Vector vecAbsOrigin = GetAbsOrigin();
	int contents = UTIL_PointContents(vecAbsOrigin);

	int nSpriteIndex = !(contents & MASK_WATER) ? s_nFireballSprite : s_nWaterSprite;

	if (pTrace->fraction != 1.0)
	{
		Vector vecNormal = pTrace->plane.normal;
		const surfacedata_t* pdata = physprops->GetSurfaceData(pTrace->surface.surfaceProps);
		CPASFilter filter(vecAbsOrigin);

		// 1. On dessine MANUELLEMENT ton sprite rétro au centre de l'explosion
		te->Sprite(filter, 0.0,
			&vecAbsOrigin,
			nSpriteIndex,
			m_DmgRadius * 0.015f, // Taille du sprite (tu peux ajuster ce chiffre)
			255 // Luminosité maximale
		);

		// 2. On lance l'explosion invisible pour garder la lumière dynamique, les dégâts et les secousses
		te->Explosion(filter, 0.0,
			&vecAbsOrigin,
			nSpriteIndex,
			m_DmgRadius * .03,
			25,
			TE_EXPLFLAG_NOFIREBALL | TE_EXPLFLAG_NOPARTICLES | TE_EXPLFLAG_ROTATE, // On coupe totalement le visuel de HL2
			m_DmgRadius,
			m_flDamage,
			&vecNormal,
			(char)pdata->game.material);

	}
	else
	{
		CPASFilter filter(vecAbsOrigin);

		// 1. On dessine MANUELLEMENT ton sprite rétro
		te->Sprite(filter, 0.0,
			&vecAbsOrigin,
			nSpriteIndex,
			m_DmgRadius * 0.015f,
			255
		);

		// 2. L'explosion invisible
		te->Explosion(filter, 0.0,
			&vecAbsOrigin,
			nSpriteIndex,
			m_DmgRadius * .03,
			25,
			TE_EXPLFLAG_NOFIREBALL | TE_EXPLFLAG_NOPARTICLES | TE_EXPLFLAG_ROTATE, // On coupe totalement le visuel de HL2
			m_DmgRadius,
			m_flDamage);
	}

	CSoundEnt::InsertSound(SOUND_COMBAT, GetAbsOrigin(), BASEGRENADE_EXPLOSION_VOLUME, 3.0);

	// Use the owner's position as the reported position
	Vector vecReported = GetThrower() ? GetThrower()->GetAbsOrigin() : vec3_origin;

	CTakeDamageInfo info(this, GetThrower(), GetBlastForce(), GetAbsOrigin(), m_flDamage, bitsDamageType, 0, &vecReported);

	RadiusDamage(info, GetAbsOrigin(), m_DmgRadius, CLASS_NONE, NULL);

	UTIL_DecalTrace(pTrace, "Scorch");

	flRndSound = random->RandomFloat(0, 1);

	EmitSound("HL1_BaseGrenade.Explode");

	SetTouch(NULL);

	AddEffects(EF_NODRAW);
	SetAbsVelocity(vec3_origin);

	SetThink(&CBaseGrenade::Smoke);
	SetNextThink(gpGlobals->curtime + 0.3);

	if (GetWaterLevel() == 0)
	{
		int sparkCount = random->RandomInt(0, 3);
		QAngle angles;
		VectorAngles(pTrace->plane.normal, angles);

		for (int i = 0; i < sparkCount; i++)
			Create("spark_shower", GetAbsOrigin(), angles, NULL);
	}
}
