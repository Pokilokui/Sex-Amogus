//
#include "cbase.h"

typedef enum
{
	SPAWN_OFF = 0,
	SPAWN_FALCON2,
	SPAWN_DY357,
	SPAWN_SHOTGUN,
	SPAWN_AR34,
	SPAWN_CALLISTO,
	SPAWN_RCP120,
} WeaponsToSpawn;

ConVar	mp_pdweapon1( "mp_pdweapon1", "1", FCVAR_NOTIFY|FCVAR_REPLICATED, "Weapon to create at weapon 1 areas" );
ConVar	mp_pdweapon2( "mp_pdweapon2", "1", FCVAR_NOTIFY|FCVAR_REPLICATED, "Weapon to create at weapon 2 areas" );
ConVar	mp_pdweapon3( "mp_pdweapon3", "1", FCVAR_NOTIFY|FCVAR_REPLICATED, "Weapon to create at weapon 3 areas" );
ConVar	mp_pdweapon4( "mp_pdweapon4", "1", FCVAR_NOTIFY|FCVAR_REPLICATED, "Weapon to create at weapon 4 areas" );
ConVar	mp_pdweapon5( "mp_pdweapon5", "1", FCVAR_NOTIFY|FCVAR_REPLICATED, "Weapon to create at weapon 5 areas" );
ConVar	mp_pdweapon6( "mp_pdweapon6", "1", FCVAR_NOTIFY|FCVAR_REPLICATED, "Weapon to create at weapon 6 areas" );

#ifdef CLIENT_DLL
	#define CWeaponSpawner C_WeaponSpawner 
	#define CAmmoSpawner C_AmmoSpawner
#endif


/*====================================================================

							WEAPON SPAWNER

/*====================================================================*/

class CWeaponSpawner : public CBaseAnimating
{
	DECLARE_CLASS( CWeaponSpawner, CBaseAnimating );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	int m_iWeaponSlot;

public:

	void Spawn( void )
	{
		Precache( );
		
		BaseClass::Spawn( );
		AddEffects( EF_NODRAW );
		SetMoveType( MOVETYPE_NONE );
		SetSolid( SOLID_NONE );
		SetThink( &CWeaponSpawner::Think );
		SetNextThink( gpGlobals->curtime + 3 );
	}
	void Precache( void )
	{
		PrecacheModel ("models/w_crowbar.mdl");//set a different model, something you have :)
		//Precache all entities spawned at these, to prevent late caching(ingame stutters suck)
		UTIL_PrecacheOther("weapon_stunstick");
		UTIL_PrecacheOther("weapon_physcannon");
		UTIL_PrecacheOther("weapon_physgun");
		UTIL_PrecacheOther("weapon_pistol");
		UTIL_PrecacheOther("weapon_357");
		UTIL_PrecacheOther("weapon_alyxgun");
		UTIL_PrecacheOther("weapon_flaregun");
		UTIL_PrecacheOther("weapon_smg1");
		UTIL_PrecacheOther("weapon_ar2");
		UTIL_PrecacheOther("weapon_ak47");
		UTIL_PrecacheOther("weapon_shotgun");
		UTIL_PrecacheOther("weapon_crossbow");
		UTIL_PrecacheOther("weapon_gauss");
		UTIL_PrecacheOther("weapon_egon");
		UTIL_PrecacheOther("weapon_frag");
		UTIL_PrecacheOther("weapon_slam");
		UTIL_PrecacheOther("weapon_rpg");
		UTIL_PrecacheOther("weapon_hopwire");
		UTIL_PrecacheOther("weapon_molotov");
		UTIL_PrecacheOther("weapon_bugbait");
	}

	void Think( void )
	{
		#ifndef CLIENT_DLL
		CBaseEntity * pEntity = NULL;
		int BoundWeapon = 0;
		switch (m_iWeaponSlot)
		{
			case 1: 
				BoundWeapon = mp_pdweapon1.GetInt();
				break;
			case 2: 
				BoundWeapon = mp_pdweapon2.GetInt();
				break;
			case 3: 
				BoundWeapon = mp_pdweapon3.GetInt();
				break;
			case 4: 
				BoundWeapon = mp_pdweapon4.GetInt();
				break;
			case 5: 
				BoundWeapon = mp_pdweapon5.GetInt();
				break;
			case 6: 
				BoundWeapon = mp_pdweapon6.GetInt();
				break;
		}
		switch (BoundWeapon)
		{
			case SPAWN_FALCON2:
				pEntity = CBaseEntity::Create( "weapon_falcon2", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_DY357:
				pEntity = CBaseEntity::Create( "weapon_dy357", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_SHOTGUN:
				pEntity = CBaseEntity::Create( "weapon_shotgun", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_AR34:
				pEntity = CBaseEntity::Create( "weapon_ar34", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_CALLISTO:
				pEntity = CBaseEntity::Create( "weapon_callisto", GetLocalOrigin(), GetLocalAngles() );
				break;	
			case SPAWN_RCP120:
				pEntity = CBaseEntity::Create( "weapon_rcp120", GetLocalOrigin(), GetLocalAngles() );
				break;
		}
		pEntity->RemoveSpawnFlags( SF_NORESPAWN );
		#endif
	}
};

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponSpawner, DT_WeaponSpawner )

BEGIN_NETWORK_TABLE( CWeaponSpawner, DT_WeaponSpawner )

END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponSpawner )
END_PREDICTION_DATA()

BEGIN_DATADESC( CWeaponSpawner )

	DEFINE_KEYFIELD( m_iWeaponSlot, FIELD_INTEGER, "ForWeapon" ),

#ifndef CLIENT_DLL
	DEFINE_THINKFUNC( Think ),
#endif

END_DATADESC()

LINK_ENTITY_TO_CLASS(pd_weaponspawner, CWeaponSpawner);
PRECACHE_REGISTER(pd_weaponspawner);

/*====================================================================

							AMMO SPAWNER

====================================================================*/

class CAmmoSpawner : public CBaseAnimating
{
	DECLARE_CLASS( CAmmoSpawner, CBaseAnimating );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	int m_iWeaponSlot;

public:

	void Spawn( void )
	{
		Precache( );
		
		BaseClass::Spawn( );
		AddEffects( EF_NODRAW );
		SetMoveType( MOVETYPE_NONE );
		SetSolid( SOLID_NONE );
		SetThink( &CWeaponSpawner::Think );
		SetNextThink( gpGlobals->curtime + 3 );
	}
	void Precache( void )
	{
		PrecacheModel ("models/w_rcp120.mdl");//invisible, so lets just use the rcp120 world model :)
	}

	void Think( void )
	{
		#ifndef CLIENT_DLL
		CBaseEntity * pEntity = NULL;
		int BoundWeapon = 0;
		switch (m_iWeaponSlot)
		{
			case 1: 
				BoundWeapon = mp_pdweapon1.GetInt();
				break;
			case 2: 
				BoundWeapon = mp_pdweapon2.GetInt();
				break;
			case 3: 
				BoundWeapon = mp_pdweapon3.GetInt();
				break;
			case 4: 
				BoundWeapon = mp_pdweapon4.GetInt();
				break;
			case 5: 
				BoundWeapon = mp_pdweapon5.GetInt();
				break;
			case 6: 
				BoundWeapon = mp_pdweapon6.GetInt();
				break;
		}
		switch (BoundWeapon)
		{
			case SPAWN_FALCON2:
				pEntity = CBaseEntity::Create( "item_pistolammo", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_DY357:
				pEntity = CBaseEntity::Create( "item_357ammo", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_SHOTGUN:
				pEntity = CBaseEntity::Create( "item_shellsammo", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_AR34:
				pEntity = CBaseEntity::Create( "item_smgammo", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_CALLISTO:
				pEntity = CBaseEntity::Create( "item_smgammo", GetLocalOrigin(), GetLocalAngles() );
				break;
			case SPAWN_RCP120:
				pEntity = CBaseEntity::Create( "item_smgammo", GetLocalOrigin(), GetLocalAngles() );
				break;
		}
		pEntity->RemoveSpawnFlags( SF_NORESPAWN );
		#endif
	}
};

IMPLEMENT_NETWORKCLASS_ALIASED( AmmoSpawner, DT_AmmoSpawner )

BEGIN_NETWORK_TABLE( CAmmoSpawner, DT_AmmoSpawner )

END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CAmmoSpawner )
END_PREDICTION_DATA()

BEGIN_DATADESC( CAmmoSpawner )

	DEFINE_KEYFIELD( m_iWeaponSlot, FIELD_INTEGER, "ForWeapon" ),

#ifndef CLIENT_DLL
	DEFINE_THINKFUNC( Think ),
#endif

END_DATADESC()

LINK_ENTITY_TO_CLASS(pd_ammospawner, CAmmoSpawner);
PRECACHE_REGISTER(pd_ammospawner);