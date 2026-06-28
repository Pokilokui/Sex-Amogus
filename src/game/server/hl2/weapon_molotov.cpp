//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: This is the molotov weapon
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include	"npcevent.h"
#include	"basehlcombatweapon.h"
#include	"basecombatcharacter.h"
#include	"ai_basenpc.h"
#include	"AI_Memory.h"
#include	"player.h"
#include	"gamerules.h"		// For g_pGameRules
#include	"weapon_molotov.h"
#include	"grenade_molotov.h"
#include	"in_buttons.h"
#include	"game.h"	
#include	"gamestats.h"
#include "vstdlib/random.h"
#include "movevars_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_DATADESC(CWeaponMolotov)

/*	DEFINE_FIELD(m_nNumAmmoTypes, FIELD_INTEGER),
	DEFINE_FIELD( m_bNeedDraw, FIELD_BOOLEAN ),
	DEFINE_FIELD( m_iThrowBits, FIELD_INTEGER ),
	DEFINE_FIELD( m_fNextThrowCheck, FIELD_TIME ),*/
	DEFINE_FIELD(m_bRedraw, FIELD_BOOLEAN),
	DEFINE_FIELD(m_vecTossVelocity, FIELD_VECTOR),

	// Function Pointers
	//DEFINE_FUNCTION( MolotovTouch ),

	END_DATADESC()


	IMPLEMENT_SERVERCLASS_ST(CWeaponMolotov, DT_WeaponMolotov)
	END_SEND_TABLE()

	LINK_ENTITY_TO_CLASS(weapon_molotov, CWeaponMolotov);
PRECACHE_WEAPON_REGISTER(weapon_molotov);

acttable_t	CWeaponMolotov::m_acttable[] =
{
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_THROW, true },

	{ ACT_HL2MP_IDLE,                    ACT_HL2MP_IDLE_GRENADE,                    false },
	{ ACT_HL2MP_RUN,                    ACT_HL2MP_RUN_GRENADE,                    false },
	{ ACT_HL2MP_IDLE_CROUCH,            ACT_HL2MP_IDLE_CROUCH_GRENADE,            false },
	{ ACT_HL2MP_WALK_CROUCH,            ACT_HL2MP_WALK_CROUCH_GRENADE,            false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK,    ACT_HL2MP_GESTURE_RANGE_ATTACK_GRENADE,    false },
	{ ACT_HL2MP_GESTURE_RELOAD,            ACT_HL2MP_GESTURE_RELOAD_GRENADE,        false },
	{ ACT_HL2MP_JUMP,						ACT_HL2MP_JUMP_GRENADE,			false },
};
IMPLEMENT_ACTTABLE(CWeaponMolotov);


void CWeaponMolotov::Precache(void)
{
	//	PrecacheModel("models/props_junk/w_garb_beerbottle.mdl");	//<<TEMP>> need real model
	PrecacheModel("models/weapons/w_molotov.mdl");
	UTIL_PrecacheOther("grenade_molotov");
	PrecacheScriptSound("Weapon_Molotov.Special1");
	BaseClass::Precache();
}

bool CWeaponMolotov::Deploy()
{
	m_bRedraw = false;
	return BaseClass::Deploy();
}

bool CWeaponMolotov::Holster(CBaseCombatWeapon* pSwitchingTo)
{
	m_bRedraw = false;
	return BaseClass::Holster(pSwitchingTo);
}

void CWeaponMolotov::Spawn(void)
{
	// Call base class first
	BaseClass::Spawn();

	//	m_bNeedDraw		= true;

	//	SetModel( GetWorldModel() );
	//	UTIL_SetSize(this, Vector( -6, -6, -2), Vector(6, 6, 2));
}

//------------------------------------------------------------------------------
// Purpose : Override to use molotovs pickup touch function
// Input   :
// Output  :
//------------------------------------------------------------------------------

/*void CWeaponMolotov::SetPickupTouch(void)
{
	SetTouch(MolotovTouch);
}*/


//-----------------------------------------------------------------------------
// Purpose: Override so give correct ammo
// Input  : pOther - the entity that touched me
// Output :
//-----------------------------------------------------------------------------

/*void CWeaponMolotov::MolotovTouch(CBaseEntity* pOther)
{
	// ---------------------------------------------------
	//  First give weapon to touching entity if allowed
	// ---------------------------------------------------
	BaseClass::DefaultTouch(pOther);

	// ----------------------------------------------------
	//  Give molotov ammo if touching client
	// ----------------------------------------------------
	if (pOther->GetFlags() & FL_CLIENT)
	{
		// ------------------------------------------------
		//  If already owned weapon of this type remove me
		// ------------------------------------------------
		CBaseCombatCharacter* pBCC = ToBaseCombatCharacter( pOther );
		CWeaponMolotov* oldWeapon = (CWeaponMolotov*)pBCC->Weapon_OwnsThisType( GetClassname() );
		if (oldWeapon != this)
		{
			UTIL_Remove( this );
		}
		else
		{
			pBCC->GiveAmmo( 1, m_iSecondaryAmmoType );
			SetThink (NULL);
		}
	}
}*/


//-----------------------------------------------------------------------------
// Purpose: Gets event from anim stream and throws the object
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CWeaponMolotov::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
{
	//CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	bool fThrewMolotov = false;
	switch (pEvent->event)
	{
	case EVENT_WEAPON_THROW:
		ThrowMolotov(pOperator);
		//pOwner->RemoveAmmo(1, m_iSecondaryAmmoType);
		fThrewMolotov = true;
		break;

	default:
		BaseClass::Operator_HandleAnimEvent(pEvent, pOperator);
		break;
	}

#define RETHROW_DELAY 1.0f;
	if (fThrewMolotov)
	{
		m_flNextPrimaryAttack = gpGlobals->curtime + RETHROW_DELAY;
	}

}

void CWeaponMolotov::CheckThrowPosition(CBasePlayer* pPlayer, const Vector& vecEye, Vector& vecSrc)
{
	trace_t tr;
	UTIL_TraceHull(vecEye, vecSrc, -Vector(6, 6, 6), Vector(6, 6, 6), pPlayer->PhysicsSolidMaskForEntity(),
		pPlayer, pPlayer->GetCollisionGroup(), &tr);

	if (tr.DidHit())
	{
		vecSrc = tr.endpos;
	}
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CWeaponMolotov::ThrowMolotov(CBaseCombatCharacter *pThrower)
{
	Vector vecEye = pThrower->EyePosition();
	Vector vForward, vRight,vUp, vecSrc, vecThrow;

	if (pThrower->IsPlayer())
	{
		CBasePlayer* pPlayer = ToBasePlayer(pThrower);
		if (!pPlayer)
			return;

		pPlayer->EyeVectors(&vForward, &vRight, NULL);
		vecSrc = vecEye + vForward * 18.0f + vRight * 8.0f;
		CheckThrowPosition(pPlayer, vecEye, vecSrc);
		vForward[2] += 0.1f;

		pPlayer->GetVelocity(&vecThrow, NULL);
		vecThrow += vForward * 1200;

		gamestats->Event_WeaponFired(pPlayer, true, GetClassname());
	}
	else
	{
		pThrower->GetAttachment("anim_attachment_RH", vecSrc);
		Vector vecTarget = pThrower->GetEnemy()->GetAbsOrigin();
		vecThrow = VecCheckThrow(pThrower, vecSrc, vecTarget, 650, 1.0);
		if (vecThrow == vec3_origin)
		{
			vecThrow = VecCheckToss(pThrower, vecSrc, vecTarget, -1, 1.0, true);
			if (vecThrow == vec3_origin)
			{
				GetVectors(&vForward, NULL, &vUp);
				vecThrow = vForward * 750 + vUp * 175;
			}
		}
	}

	CGrenade_Molotov* pMolotov = (CGrenade_Molotov*)Create("grenade_molotov", vecSrc, vec3_angle, GetOwner());

	m_bRedraw = true;

	pMolotov->SetAbsVelocity(vecThrow);

	// Tumble through the air
	QAngle angVel(random->RandomFloat(-100, -500), random->RandomFloat(-100, -500), random->RandomFloat(-100, -500));
	pMolotov->SetLocalAngularVelocity(angVel);
	pMolotov->SetThrower(GetOwner());
	pMolotov->SetOwnerEntity((CBaseEntity*)GetOwner());
	m_iPrimaryAttacks++;
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CWeaponMolotov::PrimaryAttack(void)
{
	if (m_bRedraw)
		return;

	CBaseCombatCharacter* pOwner = GetOwner();
	if (!pOwner)
		return;

	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	//ThrowMolotov(pPlayer); Function called in Operator_HandleAnimEvent
	pOwner->RemoveAmmo(1, m_iSecondaryAmmoType);
	SendWeaponAnim(ACT_VM_THROW);
	m_flNextPrimaryAttack = gpGlobals->curtime + 0.75;

	if (!HasSecondaryAmmo())
		pPlayer->SwitchToNextBestWeapon(this);
}

//-----------------------------------------------------------------------------
// Purpose: Override so shotgun can do mulitple reloads in a row
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CWeaponMolotov::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
	{
		return;
	}


	if ((pOwner->m_afButtonPressed & IN_ATTACK) && m_flNextSecondaryAttack <= gpGlobals->curtime)
	{
		PrimaryAttack();
	}

	if (m_bRedraw)
	{
		Reload();
		return;
	}

	BaseClass::ItemPostFrame();
}

bool CWeaponMolotov::Reload()
{
	if (!HasSecondaryAmmo())
		return false;		

	if (m_bRedraw && m_flNextPrimaryAttack <= gpGlobals->curtime)
	{
		SendWeaponAnim(ACT_VM_DRAW);

		m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
		m_flTimeWeaponIdle = gpGlobals->curtime + SequenceDuration();

		m_bRedraw = false;
	}
	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponMolotov::CWeaponMolotov() :
	CBaseHLCombatWeapon(),
	m_bRedraw(false)
{
	NULL;
}