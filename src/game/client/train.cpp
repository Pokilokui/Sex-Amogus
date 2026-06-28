//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
//
// Train.cpp
//
// implementation of CHudAmmo class
//
#include "cbase.h"
#include "hudelement.h"
#include "hud_macros.h"
#include "iclientmode.h"
//HL1
#include "materialsystem/IMaterialSystem.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/IMaterialVar.h"
#include "hl1/hud_numbers.h"
//
#include <vgui_controls/Controls.h>
#include <vgui_controls/Panel.h>
#include <vgui/ISurface.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;

//class CHudTrain: public CHudElement, public vgui::Panel
class CHudTrain : public CHudElement, public CHudNumbers
{
	//DECLARE_CLASS_SIMPLE( CHudTrain, vgui::Panel );
	DECLARE_CLASS_SIMPLE(CHudTrain, CHudNumbers);
public:
	CHudTrain( const char *pElementName );
	void Init( void );
	void VidInit( void );
	bool ShouldDraw( void );
	//virtual void	ApplySchemeSettings( vgui::IScheme *scheme );
	//virtual void	Paint( void );
	void MsgFunc_Train(bf_read &msg);

private:
	void	Paint(void);
	void	ApplySchemeSettings(vgui::IScheme* scheme);

private:
	int m_iPos;
	CHudTexture* icon_train;
};

//
//-----------------------------------------------------
//

DECLARE_HUDELEMENT( CHudTrain );
DECLARE_HUD_MESSAGE( CHudTrain, Train )

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
/*CHudTrain::CHudTrain(const char* pElementName) :
	CHudElement( pElementName ), BaseClass( NULL, "HudTrain" )
{
	vgui::Panel *pParent = g_pClientMode->GetViewport();
	SetParent( pParent );
	
	SetHiddenBits( HIDEHUD_MISCSTATUS );
}*/

CHudTrain::CHudTrain(const char* pElementName) : CHudElement(pElementName), BaseClass(NULL, "HudTrain")
{
	SetHiddenBits(HIDEHUD_MISCSTATUS);
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *scheme - 
//-----------------------------------------------------------------------------
void CHudTrain::ApplySchemeSettings( IScheme *scheme )
{
	BaseClass::ApplySchemeSettings( scheme );

	SetPaintBackgroundEnabled( false );

}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudTrain::Init(void)
{
	HOOK_HUD_MESSAGE( CHudTrain, Train );

	m_iPos = 0;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudTrain::VidInit(void)
{
	
	HOOK_HUD_MESSAGE(CHudTrain, Train);

	m_iPos = 0;

	CHudNumbers::VidInit();
	
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CHudTrain::ShouldDraw( void )
{
	return ( CHudElement::ShouldDraw() && m_iPos );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudTrain::Paint()
{
	// FIXME:  Rewrite using vgui materials if we still do this type of train UI!!!
	
	//HL1
	if (!icon_train)
	{
		icon_train = gHUD.GetIcon("train");
	}

	if (!icon_train)
	{
		return;
	}

	int		r, g, b, a;
	//int		x, y;
	Color	clrTrain;

	(gHUD.m_clrYellowish).GetColor(r, g, b, a);
	clrTrain.SetColor(r, g, b, a);

	/*int nHudElemWidth, nHudElemHeight;
	GetSize(nHudElemWidth, nHudElemHeight);

	y = nHudElemHeight - icon_train->Height() - GetNumberFontHeight();
	x = nHudElemWidth / 3 + icon_train->Width() / 4;*/

	int screenW, screenH;
	vgui::surface()->GetScreenSize(screenW, screenH);

	int y = screenH - icon_train->Height() - GetNumberFontHeight() - 5;
	int x = (screenW / 3) + (icon_train->Width() / 4);

	IMaterial* material = materials->FindMaterial(icon_train->szTextureFile, TEXTURE_GROUP_VGUI);
	if (material)
	{
		bool found;
		IMaterialVar* pFrameVar = material->FindVar("$frame", &found, false);
		if (found)
		{
			//pFrameVar->SetFloatValue(m_iPos - 1);
			int nFrame = m_iPos - 1;
			if (nFrame < 0)
			{
				nFrame = 0;
			}

			pFrameVar->SetFloatValue(nFrame);
		}
	}

	icon_train->DrawSelf(x, y, clrTrain);
	//
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudTrain::MsgFunc_Train( bf_read &msg )
{
	// update Train data
	m_iPos = msg.ReadByte();
}
