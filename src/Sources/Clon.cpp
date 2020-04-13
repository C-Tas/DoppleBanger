#include "Clon.h"
#include "PlayState.h"
#include "Player.h"
#include "GameManager.h"

bool Clon::update()
{
	if ((SDL_GetTicks() - spawnTime_) / 1000 < duration_) {
		if (ad_ > 0 && (objective_ == nullptr || objective_->getState() == STATE::DYING || Vector2D(abs(objective_->getPosX() - pos_.getX()), abs(objective_->getPosY() - pos_.getY())).magnitude() > range_))
			objective_ = static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_);

		else if (ad_ > 0 && ((SDL_GetTicks() - meleeTime_) / 1000) > meleeRate_)
		{
			objective_->receiveDamage(ad_);
			meleeTime_ = SDL_GetTicks();
		}
	}
	else player_->killClon();

	return false;
}

void Clon::initObject() {
	GameManager::instance()->setClon(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	spawnTime_ = SDL_GetTicks();
	duration_ = DURATION_;
	meleeRate_ = (player_->getStats().meleeRange_ / 2) * player_->getLiberation();
	ad_ = (player_->getStats().meleeDmg_ / 2) * player_->getLiberation();
	taunt();
}

void Clon::die()
{
	GameManager* gm = GameManager::instance();
	gm->setClon(nullptr);
	app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->lostAggro();
}

void Clon::taunt()
{
	enemies_ = CollisionCtrl::instance()->getEnemiesInArea(getVisPos(pos_), CLON_TAUNT_RANGE);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->newEnemy(this);
}