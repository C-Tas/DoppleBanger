#include "Enemy.h"
#include "PlayState.h"
#include "GameManager.h"
#include "Collisions.h"

void Enemy::die()
{
	GameManager::instance()->getPlayer()->isEnemyDead(this);
	CollisionCtrl::instance()->removeEnemy(this);
	static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

Vector2D Enemy::isPlayerInRange(double rangeAttack)
{
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return NOPE; }

	Vector2D playerPos = gm->getPlayer()->getCenter();
	Vector2D scalePlayer = gm->getPlayer()->getColliderScale();
	Vector2D center = getCenter();

	if (currEnemy_ == nullptr &&
		RectBall((float)playerPos.getX(), (float)playerPos.getY(), (float)scalePlayer.getX(), (float)scalePlayer.getY(),
			(float)center.getX(), (float)center.getY(), (float)rangeAttack)){
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
		RectBall((float)clonPos.getX(), (float)clonPos.getY(), (float)scaleClon.getX(), (float)scaleClon.getY(),
			(float)center.getX(), (float)center.getY(), (float)n)) {
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

void Enemy::receiveDamage(double damage) {
	currStats_.health_ -= damage;
	if (currStats_.health_ <= 0) {
		Player* player_ = GameManager::instance()->getPlayer();
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
	posCollision_ = Vector2D(0, 0);
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
	Clon* clon = static_cast<Clon*>(GameManager::instance()->getClon());
	if (clon != nullptr) {
		clon->enemyToRemove(this);
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
		if (RectBall((float)currEnemyCenter.getX(), (float)currEnemyCenter.getY(), (float)currEnemy_->getScaleX(), (float)currEnemy_->getScaleY(),
			(float)center.getX(), (float)center.getY(), (float)rangeVision_))
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

	if (RectBall((float)enemCenter.getX(), (float)enemCenter.getY(), (float)enemScale.getX(), (float)enemScale.getY(),
		(float)center.getX(), (float)center.getY(), (float)range)){
		return true;
	}
	else
	{
		return false;
	}
}
