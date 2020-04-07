#pragma once
#include "GameState.h"
class SkillState : public GameState
{
public:
	//<summary>Constructora generica</summary>
	SkillState(Application* app) : GameState(app) { initState(); };
	virtual ~SkillState() {};

protected:
	virtual void initState();
	static void goToGame(Application* app);
};

