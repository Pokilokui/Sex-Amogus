//The following include files are necessary to allow your MyPanel.cpp to compile.
#include "cbase.h"
#include "IMyPanel.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/Button.h>

class CPlayerModelPanel : public vgui::Frame
{
    DECLARE_CLASS_SIMPLE(CPlayerModelPanel, vgui::Frame);
    //CMyPanel : This Class / vgui::Frame : BaseClass

	CPlayerModelPanel(vgui::VPANEL parent); 	// Constructor
    ~CPlayerModelPanel() {};				// Destructor

protected:
    //VGUI overrides:
    virtual void OnTick();
    virtual void OnCommand(const char* pcCommand);

private:
    //Other used VGUI control Elements:
	Button* m_pCloseButton;
	Button* m_pMale07Button;
	Button* m_pGordonButton;
	Button* m_pMetrocopButton;

};

// Constuctor: Initializes the Panel
CPlayerModelPanel::CPlayerModelPanel(vgui::VPANEL parent)
	: BaseClass(NULL, "PlayerModelPanel")
{
	SetParent(parent);

	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);

	SetProportional(false);
	SetTitleBarVisible(true);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(true);
	SetVisible(true);

	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

	LoadControlSettings("resource/ui/playermodelpanel.res");

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

}


class CPlayerModelPanelInterface : public IMyPanel
{
private:
	CPlayerModelPanel* PlayerModelPanel;
public:
	CPlayerModelPanelInterface()
	{
		PlayerModelPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		PlayerModelPanel = new CPlayerModelPanel(parent);
	}
	void Destroy()
	{
		if (PlayerModelPanel)
		{
			PlayerModelPanel->SetParent((vgui::Panel*)NULL);
			delete PlayerModelPanel;
		}
	}
	void Activate(void)
	{
		if (PlayerModelPanel)
		{
			PlayerModelPanel->Activate();
		}
	}
};
static CPlayerModelPanelInterface g_PlayerModelPanel;
IMyPanel* PlayerModelPanel = (IMyPanel*)&g_PlayerModelPanel;

ConVar cl_showplayermodelpanel("cl_showplayermodelpanel", "0", FCVAR_CLIENTDLL, "Sets the state of myPanel <state>");

void CPlayerModelPanel::OnTick()
{
	BaseClass::OnTick();
	SetVisible(cl_showplayermodelpanel.GetBool()); //CL_SHOWMYPANEL / 1 BY DEFAULT
}

CON_COMMAND(ToggleMyPanel, "Toggles myPanel on or off")
{
	cl_showplayermodelpanel.SetValue(!cl_showplayermodelpanel.GetBool());
	PlayerModelPanel->Activate();
};

void CPlayerModelPanel::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);
	if (!Q_stricmp(pcCommand, "turnoff"))
		cl_showplayermodelpanel.SetValue(0);

	if (!Q_stricmp(pcCommand, "male_07"))
	{
		engine->ClientCmd("cl_playermodel models/playermodels/male_07.mdl");
		engine->ClientCmd("setmodel playermodels/male_07");
	}


	if (!Q_stricmp(pcCommand, "gordon"))
	{
		engine->ClientCmd("cl_playermodel models/playermodels/gordon.mdl");
		engine->ClientCmd("setmodel playermodels/gordon");
	}
		

	if (!Q_stricmp(pcCommand, "metrocop"))
	{
		engine->ClientCmd("cl_playermodel models/playermodels/police.mdl");
		engine->ClientCmd("setmodel playermodels/police");
	}
		

	//Male 07
	m_pMale07Button = new Button(this, "Button", "", this, "male_07");
	m_pMale07Button->SetPos(20, 50);
	m_pMale07Button->SetDepressedSound("common/bugreporter_succeeded.wav");
	m_pMale07Button->SetReleasedSound("ui/buttonclick.wav");

	//Gordon
	m_pGordonButton = new Button(this, "Button", "", this, "gordon");
	m_pGordonButton->SetPos(95, 50);
	m_pGordonButton->SetDepressedSound("common/bugreporter_succeeded.wav");
	m_pGordonButton->SetReleasedSound("ui/buttonclick.wav");

	//Metrocop
	m_pMetrocopButton = new Button(this, "Button", "", this, "metrocop");
	m_pMetrocopButton->SetPos(170, 50);
	m_pMetrocopButton->SetDepressedSound("common/bugreporter_succeeded.wav");
	m_pMetrocopButton->SetReleasedSound("ui/buttonclick.wav");

	m_pCloseButton = new Button(this, "Button", "Close", this, "turnoff");
	m_pCloseButton->SetPos(227, 117);
	m_pCloseButton->SetDepressedSound("common/bugreporter_succeeded.wav");
	m_pCloseButton->SetReleasedSound("ui/buttonclick.wav");

}