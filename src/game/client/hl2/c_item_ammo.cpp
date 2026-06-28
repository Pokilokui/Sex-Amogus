//
#include "cbase.h"
#include "dlight.h"
#include "r_efx.h"
#include "tier0/memdbgon.h"

class C_ItemAR2AltFireRound : public C_BaseAnimating
{
public:
	DECLARE_CLASS(C_ItemAR2AltFireRound, C_BaseAnimating);
	DECLARE_CLIENTCLASS();

	void OnDataChanged(DataUpdateType_t updateType);
	void ClientThink(void);

private:
	Vector ar2altfireroundPos;
};

IMPLEMENT_CLIENTCLASS_DT(C_ItemAR2AltFireRound, DT_ItemAR2AltFireRound, CItem_AR2AltFireRound)
RecvPropVector(RECVINFO_NAME(ar2altfireroundPos, ar2altfireroundPos)),
END_RECV_TABLE()

void C_ItemAR2AltFireRound::OnDataChanged(DataUpdateType_t updateType)
{
	BaseClass::OnDataChanged(updateType);
	SetNextClientThink(CLIENT_THINK_ALWAYS);
}

void C_ItemAR2AltFireRound::ClientThink(void)
{
	dlight_t* dl = effects->CL_AllocDlight(index);
	dl->origin = ar2altfireroundPos;
	dl->color.r = 223;
	dl->color.g = 133;
	dl->color.b = 45;
	dl->color.exponent = -1;
	dl->die = gpGlobals->curtime + 0.05f;
	dl->radius = random->RandomFloat(75.0f, 86.0f);
	dl->decay = 512.0f;

	//return BaseClass::ClientThink();
}