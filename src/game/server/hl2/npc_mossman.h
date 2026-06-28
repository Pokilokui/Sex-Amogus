//
#include "ai_baseactor.h"
#include "npc_playercompanion.h"
#include "ai_behavior_holster.h"
#include "ai_behavior_functank.h"
#include "soundenvelope.h"

class CNPC_Mossman : public  CAI_PlayerAlly
{
public:
	DECLARE_CLASS(CNPC_Mossman, CAI_PlayerAlly);

	void	Spawn(void);
	void	Precache(void);
	Class_T Classify(void);
	void	HandleAnimEvent(animevent_t* pEvent);
	int		GetSoundInterests(void);
	bool	CreateBehaviors(void);
	int		SelectSchedule(void);
	void SelectModel();


		END_DATADESC();
};