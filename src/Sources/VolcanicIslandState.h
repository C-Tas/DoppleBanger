#pragma once
#include "PlayState.h"
class VolcanicIslandState : public PlayState
{
private:
	void initState();
public:
	VolcanicIslandState(Application* app);
	virtual ~VolcanicIslandState() {};
};

