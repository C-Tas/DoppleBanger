#include "Skill.h"

bool Skill::isCD()
{
	if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0) {
		return false;
	}
	return true;
}
