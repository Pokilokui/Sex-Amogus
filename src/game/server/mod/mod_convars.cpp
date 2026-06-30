//
#include "cbase.h"
#include "convar.h"

ConVar cl_test("cl_test", 0, 0, "Example ConVar");

ConVar metropolice_skin("metropolice_skin", 0, FCVAR_ARCHIVE, "0 : male and female metropolice \n 1 : only male metropolice \n 2 : only female metropolice");

ConVar ghostbusters("ghostbusters", 0, FCVAR_ARCHIVE);

ConVar cacaaaa("cacaaaa", 0, FCVAR_ARCHIVE);

ConVar sv_autojump("sv_autojump", 0, FCVAR_ARCHIVE, "0 : normal jump \n 1 : Holding down the jump button will let you spam jump, can be useful for bhop");

ConVar mat_viewmodel_projected_textures ("mat_viewmodel_projected_textures", 0, FCVAR_ARCHIVE, "Enable shadow receiving on viewmodels");

ConVar mat_specular_seamless("mat_specular_seamless", 0, FCVAR_ARCHIVE, "Make cubemaps seamless");

ConVar friendly_fire("friendly_fire", 0, FCVAR_ARCHIVE, "0 : no friendly fire \n 1: friendly fire (works on almost all friendly npcs) \n 2: friendly fire + citizen betray (mostly broken, crashes A LOT)");

//ConVar cl_armsmodel("cl_armsmodel", 0, FCVAR_ARCHIVE);

//ConVar cl_playermodel("cl_playermodel", 0, FCVAR_ARCHIVE);

//ConVar cl_ragdoll_death_cam("cl_ragdoll_death_cam", 0, FCVAR_REPLICATED, "Attach the death cam to the player ragdoll");

//mat_player_shadow

//mat_viewmodel_projected_textures