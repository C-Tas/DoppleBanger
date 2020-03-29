#include "Clon.h"
#include "PlayState.h"
#include "Player.h"

/*bool Clon::update()
{
	if ((SDL_GetTicks() - spawnTime_) / 1000 < duration_) {
		if (ad_ > 0 && (objective_ == nullptr || objective_->getState() == STATE::DIYING || Vector2D(abs(objective_->getPosX() - pos_.getX()), abs(objective_->getPosY() - pos_.getY())).magnitude() > range_))
			objective_ = static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_);

		else if (ad_ > 0 && ((SDL_GetTicks() - meleeTime_) / 1000) > meleeRate_)
		{
			objective_->reciveDmg(ad_);
			meleeTime_ = SDL_GetTicks();
		}
	}
	else if (explotion_) explode();
	else die();

	return false;
}

void Clon::initObject() {
	spawnTime_ = SDL_GetTicks();
	duration_ = DURATION_;
	meleeRate_ = (player_->getStats().meleeRange_ / 2) * player_->getLiberation();
	explotion_ = player_->getExplotion();
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	ad_ = (player_->getStats().meleeDmg_ / 2) * player_->getLiberation();
}

void Clon::die()
{
	app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
}