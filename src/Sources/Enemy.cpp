#include "Enemy.h"
#include "PlayState.h"

void Enemy::die()
{
	Actor::die();
	CollisionCtrl::instance()->removeEnemy(this);
	static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

Vector2D Enemy::isPlayerInRange(double n)
{
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return NOPE; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + (getScaleX() / 2) + n && playerPos.getX() >= pos_.getX() - n
		&& playerPos.getY() <= pos_.getY() + (getScaleY() / 2) + n && playerPos.getY() >= pos_.getY() -n) {
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
	if (gm->getClon() == nullptr) { return NOPE ; }

	Point2D clonPos = gm->getClon()->getPos();
	if (currEnemy_ == nullptr &&
		clonPos.getX() <= pos_.getX() + (getScaleX() / 2) + n && clonPos.getX() >= pos_.getX() - n
		&& clonPos.getY() <= pos_.getY() + (getScaleY() / 2) + n && clonPos.getY() >= pos_.getY() - n) {
		static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
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
	if (playerPos == Vector2D(NOPE)&& clonPos == Vector2D(NOPE)) {
		currEnemy_ = nullptr;
		return false;
	}

	Vector2D closesetEnemy;
	closesetEnemy = pos_.getClosest(playerPos, clonPos);
	closesetEnemy == playerPos ? currEnemy_ = gm->getPlayer() : currEnemy_ = gm->getClon();
	return true;
}

void Enemy::updateAnim()
{
	if (currAnim_.frameRate_ <= SDL_GetTicks() - lastFrame_) {
		lastFrame_ = SDL_GetTicks();
		frame_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)currAnim_.widthFrame_,(int)currAnim_.heightFrame_ });
	}
}

void Enemy::initObject()
{
	initialStats();
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	animationsvar();
	initAnim();
}

void Enemy::initAnim()
{
	//Para la animaci�n de ataque
	attackAnim_ = Anim(NUM_FRAMES_ATK, NUM_FRAMES_ROW_ATK, W_FRAME_ATK, H_FRAME_ATK, FRAME_RATE_ATK, NAME_ATK);
	//Para la animaci�n de caminar
	walkAnim_ = Anim(NUM_FRAMES_MOV, NUM_FRAMES_ROW_MOV, W_FRAME_MOV, H_FRAME_MOV, FRAME_RATE_MOV, NAME_MOV);
	//Para la animaci�n de parado
	idleAnim_ = Anim(NUM_FRAMES_IDLE, NUM_FRAMES_ROW_ADLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, NAME_IDLE);
}

void Enemy::changeAnim(Anim& newAnim)
{
	//if (newAnim.name_ != currAnim_.name_) {
	//	currAnim_ = newAnim;
	//}
}

