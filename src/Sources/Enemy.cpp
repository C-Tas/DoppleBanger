#include "Enemy.h"
#include "PlayState.h"
#include "GameManager.h"

void Enemy::die()
{
	static_cast<Player*>(GameManager::instance()->getPlayer())->isEnemyDead(this);
	Actor::die();
	CollisionCtrl::instance()->removeEnemy(this);
	static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

//Actualiza la animación en función del frameRate de la actual animación
void Enemy::updateAnim()
{
	if (currAnim_.frameRate_ < (SDL_GetTicks() - lastFrame_) / 1000) {
		lastFrame_ = SDL_GetTicks();
		frame_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)currAnim_.widthFrame_,(int)currAnim_.heightFrame_ });
	}
}

//Devuelve true si el enemigo que tengo está a rango
bool Enemy::onRange(bool melee) {
	if (currEnemy_ == nullptr) {
		return false;
	}
	int range = currStats_.meleeRange_; if (!melee) range = currStats_.distRange_;
	SDL_Rect rangeAttack = { getPosX(), getPosY(), range * 2, range * 2 };
	if (currEnemy_ != nullptr && SDL_HasIntersection(&static_cast<Draw*>(currEnemy_)->getDestiny(), &rangeAttack)) {
		return true;
	}
	else {
		false;
	}
}

//Devuelve true si encontro un enemigo cerca y lo asigna a currEnemy_
bool Enemy::getEnemy(bool melee) {
	int range = currStats_.meleeRange_; if (!melee) range = currStats_.distRange_;
	auto gm = GameManager::instance();
	Vector2D playerPos = isPlayerInRange(range);
	if (playerPos == Vector2D{ -1,-1 }) {
		currEnemy_ = nullptr;
		return false;
	}

	currEnemy_ = gm->getPlayer();
	return true;
}

void Enemy::newEnemy(GameObject* obj) {
	currEnemy_ = obj;
};

//Devuelve la posición del player si está a rango 
Vector2D Enemy::isPlayerInRange(int range) {
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return { -1,-1 }; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + range && playerPos.getX() >= pos_.getX() - range
		&& playerPos.getY() <= pos_.getY() + range && playerPos.getY() >= pos_.getY() - range) {
		return playerPos;
	}
	else
	{
		return  { -1,-1 };
	}
}