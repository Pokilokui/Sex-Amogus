//
#include "cbase.h"
#include "dlight.h"
#include "r_efx.h"
#include "tier0/memdbgon.h"

class C_ItemBattery : public C_BaseAnimating
{
public:
	DECLARE_CLASS(C_ItemBattery, C_BaseAnimating);
	DECLARE_CLIENTCLASS();

	void OnDataChanged(DataUpdateType_t updateType);
	void ClientThink(void);

private:
	Vector batteryPos;
};

IMPLEMENT_CLIENTCLASS_DT(C_ItemBattery, DT_ItemBattery, CItemBattery)
RecvPropVector(RECVINFO_NAME(batteryPos, batteryPos)),
END_RECV_TABLE()

void C_ItemBattery::OnDataChanged(DataUpdateType_t updateType)
{
	BaseClass::OnDataChanged(updateType);
	SetNextClientThink(CLIENT_THINK_ALWAYS);
}

void C_ItemBattery::ClientThink(void)
{
	dlight_t* dl = effects->CL_AllocDlight(index);
	dl->origin = batteryPos;
	dl->color.r = 16;
	dl->color.g = 252;
	dl->color.b = 248;
	dl->color.exponent = -1;
	dl->die = gpGlobals->curtime + 0.05f;
	dl->radius = random->RandomFloat(75.0f, 86.0f);
	dl->decay = 512.0f;

	return BaseClass::ClientThink();
}