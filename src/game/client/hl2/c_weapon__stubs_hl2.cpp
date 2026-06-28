//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "c_weapon__stubs.h"
#include "basehlcombatweapon_shared.h"
#include "c_basehlcombatweapon.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

STUB_WEAPON_CLASS( cycler_weapon, WeaponCycler, C_BaseCombatWeapon );

//STUB_WEAPON_CLASS( weapon_binoculars, WeaponBinoculars, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_bugbait, WeaponBugBait, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_flaregun, Flaregun, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_annabelle, WeaponAnnabelle, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_gauss, WeaponGaussGun, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_cubemap, WeaponCubemap, C_BaseCombatWeapon );
STUB_WEAPON_CLASS( weapon_alyxgun, WeaponAlyxGun, C_HLSelectFireMachineGun );
STUB_WEAPON_CLASS( weapon_citizenpackage, WeaponCitizenPackage, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_citizensuitcase, WeaponCitizenSuitcase, C_WeaponCitizenPackage );

#ifndef HL2MP
STUB_WEAPON_CLASS( weapon_ar2, WeaponAR2, C_HLMachineGun );
STUB_WEAPON_CLASS( weapon_frag, WeaponFrag, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_rpg, WeaponRPG, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_pistol, WeaponPistol, C_BaseHLCombatWeapon );
//STUB_WEAPON_CLASS( weapon_ak47, WeaponAk47, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_shotgun, WeaponShotgun, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_smg1, WeaponSMG1, C_HLSelectFireMachineGun );
STUB_WEAPON_CLASS( weapon_357, Weapon357, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_crossbow, WeaponCrossbow, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_slam, Weapon_SLAM, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_crowbar, WeaponCrowbar, C_BaseHLBludgeonWeapon );
#ifdef HL2_EPISODIC
STUB_WEAPON_CLASS( weapon_hopwire, WeaponHopwire, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_proto1, WeaponProto1, C_BaseHLCombatWeapon );
//STUB_WEAPON_CLASS(weapon_oldmanharpoon, WeaponOldManHarpoon, C_WeaponCitizenPackage);
#endif

//Beta
STUB_WEAPON_CLASS( weapon_molotov, WeaponMolotov, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS (weapon_binoculars, WeaponBinoculars, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_oicw, Weaponoicw, C_HLMachineGun );
STUB_WEAPON_CLASS( weapon_stickylauncher, Weaponstickylauncher, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_cguard, WeaponCGuard, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS(weapon_immolator, WeaponImmolator, C_BaseHLCombatWeapon);

//cstrike
STUB_WEAPON_CLASS(weapon_cstrike_frag, WeaponCstrikeFrag, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_mp5navy, WeaponMP5Navy, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_m4a1, WeaponM4A1, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_m3, WeaponM3, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_famas, WeaponFamas, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_m249, WeaponM249, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_fiveseven, WeaponFiveSeven, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_elite, WeaponElite, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_knife, WeaponKnife, C_BaseHLBludgeonWeapon);
STUB_WEAPON_CLASS(weapon_ak47, WeaponAK47, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_aug, WeaponAug, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_awp, WeaponAWP, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_deagle, WeaponDeagle, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_galil, WeaponGalil, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_g3sg1, WeaponG3SG1, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_cs_glock, WeaponGlock, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_mac10, WeaponMac10, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_p228, WeaponP228, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_p90, WeaponP90, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_sg550, WeaponSG550, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_sg552, WeaponSG552, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_scout, WeaponScout, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_tmp, WeaponTMP, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_ump45, WeaponUmp45, C_HLMachineGun);
STUB_WEAPON_CLASS(weapon_usp, WeaponUSP, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_xm1014, WeaponXM1014, C_BaseHLCombatWeapon);

//HL1
STUB_WEAPON_CLASS(weapon_hl1_glock, WeaponHL1glock, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_hl1_crowbar, WeaponHL1Crowbar, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_mp5, WeaponMP5, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_tripmine, WeaponTripmine, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_hl1_shotgun, WeaponHL1Shotgun, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_egon, WeaponEgon, C_BaseHLCombatWeapon);
//STUB_WEAPON_CLASS(weapon_hornetgun, WeaponHgun, C_BaseHLCombatWeapon); Fonctionne quand commenté ??????
STUB_WEAPON_CLASS(weapon_hl1_357, WeaponHL1357, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_handgrenade, WeaponHandGrenade, C_BaseHLCombatWeapon);

//others
STUB_WEAPON_CLASS(weapon_flash, WeaponFlash, C_BaseHLCombatWeapon);

#ifdef HL2_LOSTCOAST
//STUB_WEAPON_CLASS( weapon_oldmanharpoon, WeaponOldManHarpoon, C_WeaponCitizenPackage );
#endif
#endif


