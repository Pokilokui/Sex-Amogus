//HealthKit
#include "cbase.h"
#include "dlight.h"
#include "r_efx.h"
#include "tier0/memdbgon.h"

class C_HealthKit : public C_BaseAnimating
{
public:
	DECLARE_CLASS(C_HealthKit, C_BaseAnimating);
	DECLARE_CLIENTCLASS();

	void OnDataChanged(DataUpdateType_t updateType);
	void ClientThink(void);

private:
	Vector healthKitPos;
};

IMPLEMENT_CLIENTCLASS_DT(C_HealthKit, DT_HealthKit, CHealthKit)
RecvPropVector(RECVINFO_NAME(healthKitPos, healthKitPos)),
END_RECV_TABLE()

void C_HealthKit::OnDataChanged(DataUpdateType_t updateType)
{
	BaseClass::OnDataChanged(updateType);
	SetNextClientThink(CLIENT_THINK_ALWAYS);
}

void C_HealthKit::ClientThink(void)
{
	dlight_t* dl = effects->CL_AllocDlight(index);
	dl->origin = healthKitPos;
	dl->color.r = 39;
	dl->color.g = 148;
	dl->color.b = 23;
	dl->color.exponent = -1;
	dl->die = gpGlobals->curtime + 0.05f;
	dl->radius = random->RandomFloat(75.0f, 86.0f);
	dl->decay = 512.0f;

	return BaseClass::ClientThink();
}

//HealthVial

class C_HealthVial : public C_BaseAnimating
{
public:
	DECLARE_CLASS(C_HealthVial, C_BaseAnimating);
	DECLARE_CLIENTCLASS();

	void OnDataChanged(DataUpdateType_t updateType);
	void ClientThink(void);

private:
	Vector healthVialPos;
};

IMPLEMENT_CLIENTCLASS_DT(C_HealthVial, DT_HealthVial, CHealthVial)
RecvPropVector(RECVINFO_NAME(healthVialPos, healthVialPos)),
END_RECV_TABLE()

void C_HealthVial::OnDataChanged(DataUpdateType_t updateType)
{
	BaseClass::OnDataChanged(updateType);
	SetNextClientThink(CLIENT_THINK_ALWAYS);
}

void C_HealthVial::ClientThink(void)
{
	dlight_t* dl = effects->CL_AllocDlight(index);
	dl->origin = healthVialPos;
	dl->color.r = 39;
	dl->color.g = 148;
	dl->color.b = 23;
	dl->color.exponent = -1;
	dl->die = gpGlobals->curtime + 0.05f;
	dl->radius = random->RandomFloat(55.0f, 66.0f);
	dl->decay = 512.0f;

	return BaseClass::ClientThink();
}
