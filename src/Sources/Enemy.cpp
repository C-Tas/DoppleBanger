#include "Enemy.h"
#include "PlayState.h"

void Enemy::die() {
	static_cast<PlayState*>(app_->getGameStateMachine()->getState())->removeEnemy(this);
}