#include "Enemy.h"
#include "PlayState.h"
#include "GameManager.h"
#include "Collisions.h"

void Enemy::die()
{
	static_cast<Player*>(GameManager::instance()->getPlayer())->isEnemyDead(this);
	Actor::die();
	//CollisionCtrl::instance()->removeEnemy(this);
	//static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

Vector2D Enemy::isPlayerInRange(double rangeAttack)
{
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return NOPE; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + (getScaleX() / 2) + rangeAttack && playerPos.getX() >= pos_.getX() - rangeAttack
		&& playerPos.getY() <= pos_.getY() + (getScaleY() / 2) + rangeAttack && playerPos.getY() >= pos_.getY() - rangeAttack) {
		return playerPos;
	}
	else
	{
		return  NOPE;
	}
}

Vector2D Enemy::isClonInRange(double n)
{
	GameManager* gm = GameManager::instance();
	if (gm->getClon() == nullptr) { return NOPE; }

	Point2D clonPos = gm->getClon()->getPos();
	if (currEnemy_ == nullptr &&
		clonPos.getX() <= pos_.getX() + (getScaleX() / 2) + n && clonPos.getX() >= pos_.getX() - n
		&& clonPos.getY() <= pos_.getY() + (getScaleY() / 2) + n && clonPos.getY() >= pos_.getY() - n) {
		//static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
		return clonPos;
	}
	else
	{
		return NOPE;
	}
}

bool Enemy::getEnemy(double n)
{
	auto gm = GameManager::instance();
	Vector2D playerPos = isPlayerInRange(n);
	Vector2D clonPos = isClonInRange(n);
	if (playerPos == Vector2D(NOPE) && clonPos == Vector2D(NOPE)) {
		currEnemy_ = nullptr;
		return false;
	}

	Vector2D closesetEnemy;
	closesetEnemy = pos_.getClosest(playerPos, clonPos);
	closesetEnemy == playerPos ? currEnemy_ = gm->getPlayer() : currEnemy_ = gm->getClon();
	return true;
}


void Enemy::initObject()
{
	initialStats();
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnims();
}

Vector2D Enemy::PosToTile(Vector2D pos)
{
	return Vector2D(round((pos.getX() - iniPosMap_.getX() + 2 * (pos.getY() - iniPosMap_.getY())) / GameManager::instance()->getTileSize()),
					round(((pos.getX() - iniPosMap_.getX()) - 2 * (pos.getY() - iniPosMap_.getY())) / (-1 * GameManager::instance()->getTileSize())));
}

Vector2D Enemy::TileToPos(Vector2D tile)
{
	return Vector2D((iniPosMap_.getX() - ((double)(GameManager::instance()->getTileSize() / 2) * tile.getY()) + ((double)(GameManager::instance()->getTileSize() / 2) * (double)tile.getX())),
					(iniPosMap_.getY() + ((double)(GameManager::instance()->getTileSize() / 4) * tile.getY()) + ((double)(GameManager::instance()->getTileSize() / 4) * (double)tile.getX())));
}

void Enemy::applyRewards()
{
	GameManager::instance()->addInventoryGold(goldPoints_);
	GameManager::instance()->addArchievementPoints(achievementPoints_);
}

//Devuelve true si el enemigo que tengo está a rango
bool Enemy::onRange() {
	if (currEnemy_ != nullptr) {
		Point2D center = getCenter();
		Point2D currEnemyCenter = currEnemy_->getCenter();
		if (RectBall(currEnemyCenter.getX(), currEnemyCenter.getY(), currEnemy_->getScaleX(), currEnemy_->getScaleY(),
			center.getX(), center.getY(), currStats_.distRange_))
		{
			return true;
		}
	}
	return false;
}

bool Enemy::onRange(double range) {
	if (currEnemy_ == nullptr) {
		return false;
	}
	auto enem = static_cast<Collider*>(currEnemy_);
	Vector2D center = getCenter();
	Vector2D enemCenter = enem->getCenter();
	Vector2D enemScale = enem->getColliderScale();
	if (RectBall(enemCenter.getX(), enemCenter.getY(), enemScale.getX(), enemScale.getY(),
		center.getX(), center.getY(), range)){
		return true;
	}
	else
	{
		return false;
	}
}
