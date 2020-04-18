#include "MonkeyCoco.h"
#include <iostream>
#include "GameManager.h"
#include "Resources.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "CaribbeanIslandState.h"
#include <string>



bool MonkeyCoco ::update() {
#ifdef _DEBUG

#endif // _DEBUG

	//Si el mono ha muerto
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte?
		//Cuando acabe la animación, lo mata
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el mono no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo más cercano
	if (currState_ == STATE::IDLE && getEnemy(currStats_.distRange_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si el mono tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		//Si el mono tiene un enemigo y lo tiene a rango
		if (onRange()) {
			changeAnim(attackAnim_);
			attack();
		}
		//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
		else if(getEnemy(currStats_.distRange_))
		{
			changeAnim(attackAnim_);
			attack();
		}
		//Tengo enemigo pero no a rango
		else
		{
			currState_ = STATE::IDLE;
			changeAnim(idleAnim_);
			currEnemy_ = nullptr;
		}
		lastHit = SDL_GetTicks();
	}
	
	updateAnim();
	return false;
}

//Devuelve true si el enemigo que tengo está a rango
bool MonkeyCoco::onRange() {
	if (currEnemy_ == nullptr) {
		return false;
	}
	SDL_Rect rangeAttack = { getPosX() - currStats_.distRange_ - (getScaleX() / 2)  ,
	getPosY() - currStats_.distRange_ - (getScaleY() / 2),currStats_.distRange_ * 2, currStats_.distRange_ * 2 };;
	if (currEnemy_ != nullptr && SDL_HasIntersection(&static_cast<Draw*>(currEnemy_)->getDestiny(), &rangeAttack)) {
		return true;
	}
	else
	{
		false;
	}
}

//Inicializa todas las animaciones
//void MonkeyCoco::initAnims()
//{
//	//Para la animación de ataque
//	attackAnim_ = Anim(NUM_FRAMES_ATK,NUM_FRAMES_ROW_ATK,W_FRAME_ATK,H_FRAME_ATK,FRAME_RATE_ATK,NAME_ATK);
//	//Para la animación de caminar
//	walkAnim_ = Anim(NUM_FRAMES_MOV,NUM_FRAMES_ROW_MOV,W_FRAME_MOV,H_FRAME_MOV,FRAME_RATE_MOV,NAME_MOV);
//	//Para la animación de parado
//	idleAnim_ = Anim(NUM_FRAMES_IDLE,NUM_FRAMES_ROW_ADLE,W_FRAME_IDLE,H_FRAME_IDLE,FRAME_RATE_IDLE,NAME_IDLE);
//}

//Actualiza la animación en función del frameRate de la actual animación
//void MonkeyCoco::updateAnim()
//{
//	if (currAnim_.frameRate_ <= SDL_GetTicks() - lasFrame_) {
//		lasFrame_ = SDL_GetTicks();
//		frame_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)currAnim_.widthFrame_,(int)currAnim_.heightFrame_ });
//	}
//}

//Cambia la actual animación del mono si no la tiene "equipada"
//void MonkeyCoco::changeAnim(Anim& newAnim) {
//	if (newAnim.name_ != currAnim_.name_) {
//		currAnim_ = newAnim;
//	}
//}

//Se encarga de crear el coco en dirección al enemigo
void MonkeyCoco::attack() {
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	Bullet* coco = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(pos_), dir, currStats_.distDmg_, COCO_LIFE, COCO_VEL, Vector2D(W_H_COCO, W_H_COCO));
	app_->getCurrState()->addRenderUpdateLists(coco);
	CollisionCtrl::instance()->addEnemyBullet(coco);
}

//Inicializa al mono
void MonkeyCoco::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	Enemy::initObject();
}


void MonkeyCoco::lostAgro()
{
	currEnemy_ = nullptr;
}

void MonkeyCoco::animationsvar()
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

void MonkeyCoco::initialStats()
{
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
	MELEE_RATE = 1;
	DIST_RATE = 2500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

