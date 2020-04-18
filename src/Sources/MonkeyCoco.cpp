#include "MonkeyCoco.h"
#include <iostream>
#include "GameManager.h"
#include "Resources.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "CaribbeanIslandState.h"
#include <string>

bool MonkeyCoco ::update() {

	//Si el mono ha muerto
	if (currState_ == STATE::DYING) {
		//Tendr�a que hacer la animaci�n de muerte?
		//Cuando acabe la animaci�n, lo mata
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el mono no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo m�s cercano
	if (currState_ == STATE::IDLE && getEnemy(false)) {
		currState_ = STATE::ATTACKING;
	}
	//Si el mono tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		//Si el mono tiene un enemigo y lo tiene a rango
		if (onRange(false)) {
			changeAnim(attackAnim_);
			attack();
		}
		//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
		else if(getEnemy(false))
		{
			changeAnim(attackAnim_);
			attack();
		}
		//Tengo enemigo pero no a rango
		else
		{
			currState_ == STATE::IDLE;
			changeAnim(idleAnim_);
			currEnemy_ = nullptr;
		}
		lastHit = SDL_GetTicks();
	}
	
	updateAnim();
	return false;
}


//Inicializa todas las animaciones
void MonkeyCoco::initAnims()
{
	//Para la animaci�n de ataque
	attackAnim_ = Anim(NUM_FRAMES_ATK,NUM_FRAMES_ROW_ATK,W_FRAME_ATK,H_FRAME_ATK,FRAME_RATE_ATK,NAME_ATK);
	//Para la animaci�n de caminar
	walkAnim_ = Anim(NUM_FRAMES_MOV,NUM_FRAMES_ROW_MOV,W_FRAME_MOV,H_FRAME_MOV,FRAME_RATE_MOV,NAME_MOV);
	//Para la animaci�n de parado
	idleAnim_ = Anim(NUM_FRAMES_IDLE,NUM_FRAMES_ROW_ADLE,W_FRAME_IDLE,H_FRAME_IDLE,FRAME_RATE_IDLE,NAME_IDLE);
}

//Se encarga de crear el coco en direcci�n al enemigo
void MonkeyCoco::attack() {
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	Bullet* coco = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(), dir, currStats_.distDmg_, COCO_LIFE, COCO_VEL, Vector2D(W_H_COCO, W_H_COCO));
	app_->getCurrState()->addRenderUpdateLists(coco);
	CollisionCtrl::instance()->addEnemyBullet(coco);
}

//Inicializa al mono
void MonkeyCoco::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	initAnim();
}

//Gesti�n de las colisiones
void MonkeyCoco::onCollider()
{}
