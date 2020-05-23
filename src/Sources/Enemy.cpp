#include "Enemy.h"
#include "PlayState.h"
#include "GameManager.h"
#include "Collisions.h"

void Enemy::die()
{
	static_cast<Player*>(GameManager::instance()->getPlayer())->isEnemyDead(this);
	//CollisionCtrl::instance()->removeEnemy(this);
	//static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

Vector2D Enemy::isPlayerInRange(double rangeAttack)
{
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return NOPE; }

	Vector2D playerPos = gm->getPlayer()->getCenter();
	Vector2D scalePlayer = gm->getPlayer()->getScale();
	Vector2D center = getCenter();

	if (currEnemy_ == nullptr &&
		RectBall(playerPos.getX(), playerPos.getY(),  scalePlayer.getX(), scalePlayer.getY(),
			center.getX(), center.getY(), rangeAttack)){
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

	Vector2D clonPos = gm->getClon()->getCenter();
	Vector2D scaleClon = gm->getClon()->getScale();
	Vector2D center = getCenter();

	if (currEnemy_ == nullptr &&
		RectBall(clonPos.getX(), clonPos.getY(), scaleClon.getX(), scaleClon.getY(),
			center.getX(), center.getY(), n)) {
		return clonPos;
	}
	else
	{
		return  NOPE;
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

void Enemy::receiveDamage(int damage) {
	/*double finalDamage = (currStats_.armor_ * damage) / 100;
	currStats_.health_ -= finalDamage;*/
	currStats_.health_ -= damage;
	if (currStats_.health_ <= 0) {
		Player* player_ = dynamic_cast<Player*>(currEnemy_);
		initDie();
		if (player_ != nullptr && player_ -> getEnemy() != nullptr && player_ -> getEnemy() == this )
		{
			player_->setEnemy(nullptr);
		}
	}
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

void Enemy::initDie()
{
	Actor::initDie();
	CollisionCtrl::instance()->removeEnemy(this);
	auto aux = dynamic_cast <PlayState*>(app_->getCurrState());
	if (aux) {
		aux->removeEnemy(this);
	}
	applyRewards();
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
			center.getX(), center.getY(), rangeVision_))
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
