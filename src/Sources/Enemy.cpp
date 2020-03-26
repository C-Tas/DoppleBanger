#include "Enemy.h"
#include "PlayState.h"

void Enemy::die() {
	static_cast<PlayState*>(app_->getStateMachine()->getState())->removeEnemy(this);
	delete this;
}