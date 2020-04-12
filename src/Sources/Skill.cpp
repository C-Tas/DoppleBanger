#include "Skill.h"

bool Skill::isCD()
{
	cout << cooldown_ << endl;
	if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0) {
		return false;
	}
	return true;
}
