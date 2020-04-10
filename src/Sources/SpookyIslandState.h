#pragma once
#include "PlayState.h"
class SpookyIslandState : public PlayState
{
private:
	void initState();
public:
	SpookyIslandState(Application*);
	virtual ~SpookyIslandState() {};
};

