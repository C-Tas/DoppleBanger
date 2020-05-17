#include "Skeleton.h"
#include <iostream>
#include "Resources.h"
#include "BoneBullet.h"
#include "CollisionCtrl.h"
//#include "CaribbeanIslandState.h"


//Inicializa todas las animaciones
void Skeleton::initAnims()
{
	//Para la animaci�n de movimiento
	//moveAnim_ = Anim(NUM_FRAMES_MOV, NUM_FRAMES_ROW_MOV, W_FRAME_MOV, H_FRAME_MOV, FRAME_RATE_MOV, NAME_MOV);
	
}

void Skeleton::initialStats() {
	HEALTH = 100;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 0;
	DIST_DMG = 100;
	CRIT = 0;
	MELEE_RANGE = 20;
	DIST_RANGE = 250;
	MOVE_SPEED = 100;
	MELEE_RATE = 0;
	DIST_RATE = 2500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Skeleton::updateCooldowns()
{
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}


void Skeleton::attack() {
	if (!shootCD_.isCooldownActive()) {
		shootCD_.initCooldown(currStats_.distRate_);
		Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
		BoneBullet* bone = new BoneBullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
			getCenter(), dir, currStats_.distDmg_, BONE_LIFE, BONE_VEL, Vector2D(BONE_WIDTH, BONE_HEIGHT));
		app_->getCurrState()->addRenderUpdateLists(bone);
		CollisionCtrl::instance()->addEnemyBullet(bone);
	}
}

void Skeleton::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Skeleton));
	initialStats();
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnims();
}

void Skeleton::lostAggro()
{
	currEnemy_ = nullptr;
}

bool Skeleton::update() {
	updateFrame();
	updateCooldowns();

	//Si el esqueleto ha muerto
	if (currState_ == STATE::DYING) {
		// animaci�n de muerte si la tiene
		//Cuando acabe la animaci�n, lo mata
		applyRewards();
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el esqueleto no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo m�s cercano
	if (currState_ == STATE::IDLE && getEnemy(currStats_.distRange_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si el esqueleto tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING && !shootCD_.isCooldownActive()) {
		//Si el esqueeto tiene un enemigo y lo tiene a rango
		if (onRange()) {
			//changeAnim(attackAnim_);//animacion de ataque del esqueleto
			attack();
		}
		//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
		else if (getEnemy(currStats_.distRange_))
		{
			//changeAnim(attackAnim_);//animacion de ataque del esqueleto
			attack();
		}
		//Tengo enemigo pero no a rango
		else
		{
			currState_ == STATE::IDLE;
			//changeAnim(idleAnim_); animacion de idle del esqueleto
			currEnemy_ = nullptr;
		}
	}

	return false;
}

void Skeleton::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}