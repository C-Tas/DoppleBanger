#include "Clon.h"
#include "PlayState.h"

bool Clon::update()
{
	if ((SDL_GetTicks() - spawnTime_) / 1000 < duration_) {
		if (ad_ > 0 && (objective_ == nullptr || !objective_->isAlive() || Vector2D(abs(objective_->getPosX() - pos_.getX()), abs(objective_->getPosY() - pos_.getY())).magnitude() > range_))
			objective_ = static_cast<PlayState*>(app_->getStateMachine()->getState())->findClosestEnemy(pos_);

		else if (ad_ > 0 && ((SDL_GetTicks() - meleeTime_) / 1000) > meleeRate_)
		{
			objective_->takeDamage(ad_);
			meleeTime_ = SDL_GetTicks();
		}
	}
	else if (explotion_) explode();
	else die();

	return false;
}

void Clon::die()
{
	app_->getStateMachine()->getState()->removeRenderUpdateLists(this);
}