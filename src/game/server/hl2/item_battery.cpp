//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Handling for the suit batteries.
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hl2_player.h"
#include "basecombatweapon.h"
#include "gamerules.h"
#include "items.h"
#include "engine/IEngineSound.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CItemBattery : public CItem
{
public:
		DECLARE_CLASS( CItemBattery, CItem );
		DECLARE_SERVERCLASS()
		DECLARE_DATADESC()

		void Spawn( void )
	{ 
			Precache( );
			SetModel( "models/items/battery.mdl" );
			batteryPos = GetAbsOrigin();
			SetThink(&CItemBattery::Think);
			SetNextThink(gpGlobals->curtime);
			BaseClass::Spawn( );
		}
		void Precache( void )
		{
			PrecacheModel ("models/items/battery.mdl");

			PrecacheScriptSound( "ItemBattery.Touch" );

		}
		bool MyTouch( CBasePlayer *pPlayer )
		{
			CHL2_Player *pHL2Player = dynamic_cast<CHL2_Player *>( pPlayer );
			return ( pHL2Player && pHL2Player->ApplyBattery() );
		}
		void Think(void)
		{
			batteryPos = GetAbsOrigin();
			float distance = CollisionProp()->CalcDistanceFromPoint(UTIL_GetLocalPlayer()->GetAbsOrigin());
			if (distance < 20)
			{
				bool IsTouching = MyTouch(UTIL_GetLocalPlayer());
				if (IsTouching)
				{
					UTIL_Remove(this);
					SetNextThink(NULL);
				}
			}
			SetNextThink(gpGlobals->curtime + TICK_INTERVAL);
		}

		CNetworkVar(Vector, batteryPos);
};

LINK_ENTITY_TO_CLASS(item_battery, CItemBattery);
PRECACHE_REGISTER(item_battery);

BEGIN_DATADESC(CItemBattery)
DEFINE_FIELD(batteryPos, FIELD_POSITION_VECTOR),
DEFINE_THINKFUNC(Think),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CItemBattery, DT_ItemBattery)
SendPropVector(SENDINFO(batteryPos), -1, SPROP_COORD),
END_SEND_TABLE()

//-----------------------------------------------------------------------------
// HL1 Battery
//-----------------------------------------------------------------------------


class CHL1ItemBattery : public CItem
{
public:
	DECLARE_CLASS(CHL1ItemBattery, CItem);

	void Spawn(void)
	{
		Precache();
		SetModel("models/w_battery.mdl");
		BaseClass::Spawn();
	}
	void Precache(void)
	{
		PrecacheModel("models/w_battery.mdl");

		PrecacheScriptSound("Item.Pickup");

	}
	bool MyTouch(CBasePlayer* pPlayer)
	{
		ConVar* sk_battery = cvar->FindVar("sk_battery");

		if ((pPlayer->ArmorValue() < MAX_NORMAL_BATTERY) && pPlayer->IsSuitEquipped())
		{
			int pct;
			char szcharge[64];

			pPlayer->IncrementArmorValue(sk_battery->GetFloat(), MAX_NORMAL_BATTERY);

			CPASAttenuationFilter filter(pPlayer, "Item.Pickup");
			EmitSound(filter, pPlayer->entindex(), "Item.Pickup");

			CSingleUserRecipientFilter user(pPlayer);
			user.MakeReliable();

			UserMessageBegin(user, "ItemPickup");
			WRITE_STRING(GetClassname());
			MessageEnd();

			pct = (int)((float)(pPlayer->ArmorValue() * 100.0) * (1.0 / MAX_NORMAL_BATTERY) + 0.5);
			pct = (pct / 5);
			if (pct > 0)
				pct--;

			Q_snprintf(szcharge, sizeof(szcharge), "!HEV_%1dP", pct);

			pPlayer->SetSuitUpdate(szcharge, FALSE, SUIT_NEXT_IN_30SEC);
			return true;
		}
		return false;
	}
};

LINK_ENTITY_TO_CLASS(item_hl1_battery, CHL1ItemBattery);
PRECACHE_REGISTER(item_hl1_battery);