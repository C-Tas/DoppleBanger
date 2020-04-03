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
	updateVisPos();

	//Si el mono ha muerto
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte?
		//Cuando acabe la animación, lo mata
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el mono no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo más cercano
	if (currState_ == STATE::IDLE && getEnemy()) {
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
		else if(getEnemy())
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

//Devuelve true si el enemigo que tengo está a rango
bool MonkeyCoco::onRange() {
	if (currEnemy_ == nullptr) {
		return false;
	}
	SDL_Rect rangeAttack = { getPosX(),getPosY(),currStats_.distRange_ * 2, currStats_.distRange_ * 2 };
	if (currEnemy_ != nullptr && SDL_HasIntersection(&static_cast<Draw*>(currEnemy_)->getDestiny(), &rangeAttack)) {
		return true;
	}
	else
	{
		false;
	}
}

//Inicializa todas las animaciones
void MonkeyCoco::initAnims()
{
	//Para la animación de ataque
	attackAnim_ = Anim(NUM_FRAMES_ATK,NUM_FRAMES_ROW_ATK,W_FRAME_ATK,H_FRAME_ATK,FRAME_RATE_ATK,NAME_ATK);
	//Para la animación de caminar
	walkAnim_ = Anim(NUM_FRAMES_MOV,NUM_FRAMES_ROW_MOV,W_FRAME_MOV,H_FRAME_MOV,FRAME_RATE_MOV,NAME_MOV);
	//Para la animación de parado
	idleAnim_ = Anim(NUM_FRAMES_IDLE,NUM_FRAMES_ROW_ADLE,W_FRAME_IDLE,H_FRAME_IDLE,FRAME_RATE_IDLE,NAME_IDLE);
}

//Actualiza la animación en función del frameRate de la actual animación
void MonkeyCoco::updateAnim()
{
	if (currAnim_.frameRate_ <= SDL_GetTicks() - lasFrame_) {
		lasFrame_ = SDL_GetTicks();
		frame_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)currAnim_.widthFrame_,(int)currAnim_.heightFrame_ });
	}
}

//Cambia la actual animación del mono si no la tiene "equipada"
void MonkeyCoco::changeAnim(Anim& newAnim) {
	if (newAnim.name_ != currAnim_.name_) {
		currAnim_ = newAnim;
	}
}

//Se encarga de crear el coco en dirección al enemigo
void MonkeyCoco::attack() {
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	Bullet* coco = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(pos_), dir, currStats_.distDmg_, true, COCO_LIFE, COCO_VEL, Vector2D(W_H_COCO, W_H_COCO));
	app_->getCurrState()->addRenderUpdateLists(coco);
}

//Inicializa al monkeyCoco
void MonkeyCoco::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	boxCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)boxCollision_.getX(),(int)boxCollision_.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	initAnim();
}

//Esto es un apaño, se eliminara cuando este completa la gestión de muertes
void MonkeyCoco::onCollider()
{}

//Devuelve true si encontro un enemigo cerca y lo asigna a currEnemy_
bool MonkeyCoco::getEnemy() {
	auto gm = GameManager::instance();
	Vector2D playerPos = isPlayerInRange();
	Vector2D clonPos = isClonInRange();
	if (playerPos == Vector2D{ -1,-1 } && clonPos == Vector2D{ -1,-1 }) {
		currEnemy_ = nullptr;
		return false;
	}
	
	Vector2D closesetEnemy;
	closesetEnemy = pos_.getClosest(playerPos,clonPos);
	closesetEnemy == playerPos ? currEnemy_ = gm->getPlayer() : currEnemy_ = gm->getClon();
	return true;
}

//Devuelve la posición del player si está a rango 
Vector2D MonkeyCoco::isPlayerInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return { -1,-1 }; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + currStats_.distRange_ && playerPos.getX() >= pos_.getX() - currStats_.distRange_
		&& playerPos.getY() <= pos_.getY() + currStats_.distRange_ && playerPos.getY() >= pos_.getY() - currStats_.distRange_) {
		return playerPos;
	}
	else
	{
		return  { -1,-1 };
	}	
}

//Devuelve la posición del clon si está a rango
Vector2D MonkeyCoco::isClonInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getClon() == nullptr) {  return { -1,-1 }; }

	Point2D clonPos = gm->getClon()->getPos();
	if (currEnemy_ == nullptr && 
		clonPos.getX() <= pos_.getX() + currStats_.distRange_ && clonPos.getX() >= pos_.getX() - currStats_.distRange_
		&& clonPos.getY() <= pos_.getY() + currStats_.distRange_ && clonPos.getY() >= pos_.getY() - currStats_.distRange_){
		static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
		return clonPos;
	}
	else
	{
		return { -1,-1 };
	}
}
