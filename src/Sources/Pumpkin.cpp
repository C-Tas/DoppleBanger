#include "Pumpkin.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "Collisions.h"

bool Pumpkin::onDistRange() {

	if (currEnemy_ != nullptr) {
		Point2D center = getCenter(pos_);
		Point2D currEnemyCenter = getCenter(currEnemy_->getPos());
		if (RectBall(currEnemyCenter.getX(), currEnemyCenter.getY(), currEnemy_->getScaleX(), currEnemy_->getScaleY(),
			center.getX(), center.getY(), currStats_.distRange_))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool Pumpkin::onMeleeRange() {
	if (currEnemy_ != nullptr ) {
		Point2D center = getCenter(pos_);
		Point2D currEnemyCenter = getCenter(currEnemy_->getPos());
		if (RectBall(currEnemyCenter.getX(), currEnemyCenter.getY(), currEnemy_->getScaleX(), currEnemy_->getScaleY(),
			center.getX(), center.getY(), currStats_.meleeRange_)) {
			return true;
		}
		else return false;
	}

	else
	{
		return false;
	}
}
bool Pumpkin::update() {
#ifdef _DEBUG

#endif // _DEBUG

	//Si la calabaza ha muerto
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte?
		//Cuando acabe la animación, lo mata
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si la calabaza no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo más cercano
	if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si la calabaza tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING ) {
		//Si la calabaza tiene un enemigo y lo tiene a rango
		if ( onMeleeRange()) {
			currState_ = STATE::FOLLOWING;
		}
		else {
			if (onDistRange() && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
				changeAnim(attackAnim_);
				disAttack();
				lastHit = SDL_GetTicks();
			}


			//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
			else if (getEnemy(rangeVision_) && currStats_.distRate_ <= SDL_GetTicks() - lastHit)
			{
				changeAnim(attackAnim_);
				disAttack();
				lastHit = SDL_GetTicks();
			}

			//Tengo enemigo pero no a rango
			else
			{
				currState_ = STATE::IDLE;
				changeAnim(idleAnim_);
				currEnemy_ = nullptr;
			}
		}
	}
	if (currState_ == STATE::FOLLOWING) {
		changeAnim(walkAnim_);
		follow();
	}
	updateAnim();
	return false;
}
void Pumpkin::disAttack() {
#ifdef _DEBUG
	cout << "hey";
#endif // _DEBUG

	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	Bullet* seed = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(pos_), dir, currStats_.distDmg_, seedLife, seedVel, Vector2D(wHSeed, wHSeed));
	app_->getCurrState()->addRenderUpdateLists(seed);
	CollisionCtrl::instance()->addEnemyBullet(seed);
}
void Pumpkin::follow() {
	if (currEnemy_ != nullptr) {
		move(currEnemy_->getPos());
	}
	else {
		explote();
	}
}
void Pumpkin::explote() {
	auto dmg = dynamic_cast<Player*>(currEnemy_);
	if (dmg != nullptr) {
		dmg->receiveDamage(currStats_.meleeDmg_);
	}
	changeAnim(explotingAnim_);
	currState_ = STATE::DYING;
}
void Pumpkin::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	Enemy::initObject();
}
void Pumpkin::lostAgro()
{
	currEnemy_ = nullptr;
}

void Pumpkin::animationsvar()
{
	NUM_FRAMES_ATK = 10;
	NUM_FRAMES_ROW_ATK = 3;
	W_FRAME_ATK = 200;
	H_FRAME_ATK = 200;
	FRAME_RATE_ATK = 100;
	NAME_ATK = "attack";
	//Para el movimiento
	NUM_FRAMES_MOV = 10;
	NUM_FRAMES_ROW_MOV = 3;
	W_FRAME_MOV = 200;
	H_FRAME_MOV = 200;
	FRAME_RATE_MOV = 100;
	NAME_MOV = "walk";
	//Para estar parado
	NUM_FRAMES_IDLE = 10;
	NUM_FRAMES_ROW_ADLE = 3;
	W_FRAME_IDLE = 200;
	H_FRAME_IDLE = 200;
	FRAME_RATE_IDLE = 100;
	NAME_IDLE = "idle";
}

void Pumpkin::initialStats()
{
	rangeVision_ = 500;
	HEALTH = 100;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 0;
	DIST_DMG = 300;
	CRIT = 0;
	MELEE_RANGE = 100;
	DIST_RANGE = 500;
	MOVE_SPEED = 100;
	MELEE_RATE = 1;
	DIST_RATE = 2500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}
void Pumpkin::move(Point2D posToReach) {
	target_.setVec(posToReach);
	dir_.setX(posToReach.getX() - getCenter(pos_).getX());
	dir_.setY(posToReach.getY() - getCenter(pos_).getY());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}