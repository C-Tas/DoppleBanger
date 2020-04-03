#include "Enemy.h"
#include "PlayState.h"

void Enemy::die()
{
	Actor::die();
	CollisionCtrl::instance()->addEnemiesToErase(this);
	static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}
