#pragma once
#include "PlayState.h"
class Player;

class CaribbeanIslandState : public PlayState
{
private:
	void initState();
public:
//<summary>Constructor de la isla caribeña</summary>
	CaribbeanIslandState(Application* app);
//<summary>Destructor de la isla caribeña</summary>
	virtual ~CaribbeanIslandState() {};
};

