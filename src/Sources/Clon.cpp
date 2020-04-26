#include "Clon.h"
#include "PlayState.h"
#include "Player.h"
#include "GameManager.h"
#include "PlayerBullet.h"

bool Clon::update()
{
	if ((SDL_GetTicks() - spawnTime_) / 1000 < duration_) {
		Vector2D clonPos = getVisPos();
		if (meleeDmg_ > 0 && (objective_ == nullptr || objective_->getState() == STATE::DYING ||
			Vector2D(abs(objective_->getVisPos().getX() - clonPos.getX()), abs(objective_->getVisPos().getY() - clonPos.getY())).magnitude() > range_))
			objective_ = static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_);

		else if (meleeDmg_ > 0 && ((SDL_GetTicks() - meleeTime_) / 1000) > meleeRate_)
		{
			cout << "\nClon ataque\n";
			objective_->receiveDamage(meleeDmg_);
			if (objective_->getState() == STATE::DYING)
				enemies_.remove(static_cast<Enemy*>(objective_));
			meleeTime_ = SDL_GetTicks();
		}
	}
	else if (alive) player_->killClon();

	return false;
}

void Clon::initObject() {
	GameManager::instance()->setClon(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	spawnTime_ = SDL_GetTicks();
	duration_ = DURATION_;
	range_ = player_->getStats().meleeRange_ * 2;
	meleeRate_ = (player_->getStats().meleeRate_ / 2) * player_->getLiberation();
	meleeDmg_ = (player_->getStats().meleeDmg_ / 2) * player_->getLiberation();
	distDmg_ = (player_->getStats().distDmg_ / 2) * player_->getLiberation();
	distRange_ = (player_->getStats().distRange_ / 2) * player_->getLiberation();
	buletSpeed_ = player_->getInfoEquip().fireGun_->getSpeed();
	taunt();
}

void Clon::shoot(Vector2D dir)
{
	if (distDmg_ > 0)
	{
		//Se calcula la posici�n desde la cual se dispara la bala
		Vector2D shootPos;
		shootPos.setX(pos_.getX() + (scale_.getX() / 2));
		shootPos.setY(pos_.getY() + (scale_.getY() / 2));

		PlayerBullet* bullet = new PlayerBullet(app_, app_->getTextureManager()->getTexture(Resources::Bullet), shootPos, dir, distDmg_, distRange_, buletSpeed_);

		//Se añade a los bucles del juegos
		app_->getCurrState()->addRenderUpdateLists(bullet);
		CollisionCtrl::instance()->addPlayerBullet(bullet);
	}
}

void Clon::die()
{
	GameManager* gm = GameManager::instance();
	gm->setClon(nullptr);
	app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->lostAggro();
	alive = false;
}

void Clon::taunt()
{
	enemies_ = CollisionCtrl::instance()->getEnemiesInArea(getVisPos(), CLON_TAUNT_RANGE);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->newEnemy(this);
}