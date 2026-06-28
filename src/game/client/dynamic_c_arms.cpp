//
#include "cbase.h"
#include "c_baseplayer.h"
#include "c_baseviewmodel.h"
#include "c_basecombatweapon.h"

CON_COMMAND(cl_force_hands, "Force reload of hand model")
{
    C_BasePlayer* pPlayer = C_BasePlayer::GetLocalPlayer();
    if (!pPlayer)
        return;

    ConVar* cl_arms = cvar->FindVar("cl_armsmodel");

    C_BaseCombatWeapon* pWeapon = pPlayer->GetActiveWeapon();
    if (!pWeapon)
        return;

    C_BaseViewModel* pVM = pPlayer->GetViewModel(1);
    if (!pVM)
        return;

    pVM->SetModel(""); // reset
    //const char* model = "models/weapons/c_arms_chell.mdl"; // modèle testé
    const char* model = cl_arms->GetString();
    pVM->SetWeaponModel(model, pWeapon);
    //cl_arms->SetValue("models/weapons/c_arms_chell.mdl");

    if (pVM->GetModelPtr())
    {
        int seq = pVM->SelectWeightedSequence(ACT_VM_IDLE);
        if (seq != -1)
            pVM->ResetSequence(seq);
    }
}