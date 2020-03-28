#include "MonkeyCoco.h"
#include <iostream>
#include "GameManager.h"
#include "Resources.h"

bool MonkeyCoco ::update() {
#ifdef _DEBUG

#endif // _DEBUG
	
	if (currState_ == STATE::DIYING) {
		return true;
	}

	if (currState_ == STATE::IDLE && isPlayerInRange() || isClonInRange() ) {
		currState_ = STATE::ATTACKING;
	}
	if (currState_ == STATE::ATTACKING && target_ != nullptr && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		lastHit = SDL_GetTicks();
		attack();
		if (dynamic_cast<Player*>(target_)) {
			//GameManager::instance()->getPlayer()->reciveDMG(currStats_.ad_); gestión de ataques?
		}
	}
	return false;
}

void MonkeyCoco::animator() {
	switch (currState_)
	{
	case STATE::ATTACKING:
		//cambiar las diferentes animaciones
		break;
	case STATE::DIYING:
		break;
	case STATE::IDLE:
		break;
	default:
		break;
	}
}

//Se encarga de crear el coco falta ataque a distancia
void MonkeyCoco::attack() {

}

//Inicializa al monkeyCoco
void MonkeyCoco::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyCoco));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	scale_.setVec(START_SCALE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)START_SCALE.getX(),(int)START_SCALE.getY() });
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)BOX_COLLISION.getX(),(int)BOX_COLLISION.getY() });
	numberFrames_ = NUM_FRAMES;
	//Falta el frame
}

//Devuelve true si el jugador está en el rango de ataque del monkeyCoco
bool MonkeyCoco::isPlayerInRange() {
	GameManager* gm = GameManager::instance();
	if (target_ != nullptr || gm->getPlayer() == nullptr) { return false; };
	Point2D playerPos = gm->getPlayerPos();
	if (playerPos.getX() <= pos_.getX() + currStats_.distRate_ && playerPos.getX() >= pos_.getX() - currStats_.distRate_
		&& playerPos.getY() <= pos_.getY() + currStats_.distRate_ && playerPos.getY() >= pos_.getY() - currStats_.distRate_) {
		if (target_ == nullptr) {
			target_ = gm->getPlayer();
		}
		return true;
	}
	else
	{
		return false;
	}
}

//Devuelve true si el jugador está en el rango de ataque del monkeyCoco
bool MonkeyCoco::isClonInRange() {
	GameManager* gm = GameManager::instance();
	if (target_ != nullptr || gm->getClon() == nullptr) { return false; };
	Point2D clonPos = gm->getClon()->getPos();
	if (clonPos.getX() <= pos_.getX() + currStats_.distRate_ && clonPos.getX() >= pos_.getX() - currStats_.distRate_
		&& clonPos.getY() <= pos_.getY() + currStats_.distRate_ && clonPos.getY() >= pos_.getY() - currStats_.distRate_) {
		if (target_ == nullptr) {//gestión de agro?
			target_ = gm->getClon();
		}
		return true;
	}
	else
	{
		return false;
	}
}
