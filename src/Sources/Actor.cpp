#include "Actor.h"

void Actor::initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, int range, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, ad, ap, crit, range, moveSpeed, meleeRate, distRate);
}
void Actor::changeTexture(bool condition, int animation) {
	if (condition) {
		texture_ = textures_[animation];
		numberFrames_ = framesVector_[animation];
	}
	else
	{
		texture_ = textures_[0];
		numberFrames_ = framesVector_[0];
	}
}