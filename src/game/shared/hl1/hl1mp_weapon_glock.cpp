//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:		Glock - hand gun
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "NPCEvent.h"
#include "basehlcombatweapon_shared.h"
//#include "basecombatcharacter.h"
//#include "AI_BaseNPC.h"
#ifdef CLIENT_DLL
#include "c_baseplayer.h"
#else
#include "player.h"
#endif
#include "gamerules.h"
#include "in_buttons.h"
#ifdef CLIENT_DLL
#else
#include "soundent.h"
#include "game.h"
#endif
#include "vstdlib/random.h"
#include "engine/IEngineSound.h"

#ifdef CLIENT_DLL
#define CWeaponHL1Glock C_WeaponHL1Glock
#endif

class CWeaponHL1Glock : public CBaseHLCombatWeapon
{
	DECLARE_CLASS( CWeaponHL1Glock, CBaseHLCombatWeapon );

	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_ACTTABLE();

public:

	CWeaponHL1Glock(void);

	void	Precache( void );
	void	PrimaryAttack( void );
	void	SecondaryAttack( void );
	bool	Reload( void );
	void	WeaponIdle( void );
	void	DryFire( void );

private:
	void	GlockFire( float flSpread , float flCycleTime, bool fUseAutoAim );
};

acttable_t CWeaponHL1Glock::m_acttable[] =
{
	{ ACT_HL2MP_IDLE,                    ACT_HL2MP_IDLE_PISTOL,                    false },
	{ ACT_HL2MP_RUN,                    ACT_HL2MP_RUN_PISTOL,                    false },
	{ ACT_HL2MP_IDLE_CROUCH,            ACT_HL2MP_IDLE_CROUCH_PISTOL,            false },
	{ ACT_HL2MP_WALK_CROUCH,            ACT_HL2MP_WALK_CROUCH_PISTOL,            false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK,    ACT_HL2MP_GESTURE_RANGE_ATTACK_PISTOL,    false },
	{ ACT_HL2MP_GESTURE_RELOAD,            ACT_HL2MP_GESTURE_RELOAD_PISTOL,        false },
	{ ACT_HL2MP_JUMP,                    ACT_HL2MP_JUMP_PISTOL,                    false },
	{ ACT_RANGE_ATTACK1,                ACT_RANGE_ATTACK_PISTOL,                false },
};

IMPLEMENT_ACTTABLE(CWeaponHL1Glock);

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponHL1Glock, DT_WeaponHL1Glock );

BEGIN_NETWORK_TABLE( CWeaponHL1Glock, DT_WeaponHL1Glock )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_hl1_glock, CWeaponHL1Glock );

BEGIN_PREDICTION_DATA( CWeaponHL1Glock )
END_PREDICTION_DATA()

PRECACHE_WEAPON_REGISTER( weapon_hl1_glock );


CWeaponHL1Glock::CWeaponHL1Glock( void )
{
	m_bReloadsSingly	= false;
	m_bFiresUnderwater	= true;
}


void CWeaponHL1Glock::Precache( void )
{

	BaseClass::Precache();
}


void CWeaponHL1Glock::DryFire( void )
{
	WeaponSound( EMPTY );
	SendWeaponAnim( ACT_VM_DRYFIRE );
		
	m_flNextPrimaryAttack = gpGlobals->curtime + 0.2;
}


void CWeaponHL1Glock::PrimaryAttack( void )
{
	GlockFire( 0.01, 0.3, TRUE );
}


void CWeaponHL1Glock::SecondaryAttack( void )
{
	GlockFire( 0.1, 0.2, FALSE );
}


void CWeaponHL1Glock::GlockFire( float flSpread , float flCycleTime, bool fUseAutoAim )
{
	// Only the player fires this way so we can cast
	CBasePlayer *pPlayer = ToBasePlayer( GetOwner() );

	if ( !pPlayer )
	{
		return;
	}

	if ( m_iClip1 <= 0 )
	{
		if ( !m_bFireOnEmpty )
		{
			Reload();
		}
		else
		{
			DryFire();
		}

		return;
	}

	WeaponSound( SINGLE );

	pPlayer->DoMuzzleFlash();

	m_iClip1--;

	if ( m_iClip1 == 0 )
		SendWeaponAnim( ACT_GLOCK_SHOOTEMPTY );
	else
		SendWeaponAnim( ACT_VM_PRIMARYATTACK );

	pPlayer->SetAnimation( PLAYER_ATTACK1 );

	m_flNextPrimaryAttack	= gpGlobals->curtime + flCycleTime;
	m_flNextSecondaryAttack	= gpGlobals->curtime + flCycleTime;

	Vector vecSrc = pPlayer->Weapon_ShootPosition();
	Vector vecAiming;
	
	if ( fUseAutoAim )
	{
		vecAiming = pPlayer->GetAutoaimVector( AUTOAIM_10DEGREES );	
	}
	else
	{
		vecAiming = pPlayer->GetAutoaimVector( 0 );	
	}

//	pPlayer->FireBullets( 1, vecSrc, vecAiming, Vector( flSpread, flSpread, flSpread ), MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 0 );
	FireBulletsInfo_t info( 1, vecSrc, vecAiming, Vector( flSpread, flSpread, flSpread ), MAX_TRACE_LENGTH, m_iPrimaryAmmoType );
	info.m_pAttacker = pPlayer;
	pPlayer->FireBullets( info );

	EjectShell( pPlayer, 0 );

	pPlayer->ViewPunch( QAngle( -2, 0, 0 ) );
#if !defined(CLIENT_DLL)
	pPlayer->SetMuzzleFlashTime( gpGlobals->curtime + 0.5 );

	CSoundEnt::InsertSound( SOUND_COMBAT, GetAbsOrigin(), 400, 0.2 );
#endif

	if ( !m_iClip1 && pPlayer->GetAmmoCount( m_iPrimaryAmmoType ) <= 0 )
	{
		// HEV suit - indicate out of ammo condition
		pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	SetWeaponIdleTime( gpGlobals->curtime + random->RandomFloat( 10, 15 ) );
}


bool CWeaponHL1Glock::Reload( void )
{
	bool iResult;

	if ( m_iClip1 == 0 )
		iResult = DefaultReload( GetMaxClip1(), GetMaxClip2(), ACT_GLOCK_SHOOT_RELOAD );
	else
		iResult = DefaultReload( GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD );

	return iResult;
}



void CWeaponHL1Glock::WeaponIdle( void )
{
	CBasePlayer *pPlayer = ToBasePlayer( GetOwner() );
	if ( pPlayer )
	{
		pPlayer->GetAutoaimVector( AUTOAIM_10DEGREES );
	}

	// only idle if the slid isn't back
	if ( m_iClip1 != 0 )
	{
		BaseClass::WeaponIdle();
	}
}
