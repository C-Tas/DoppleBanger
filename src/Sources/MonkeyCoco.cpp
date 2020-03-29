#include "MonkeyCoco.h"
#include <iostream>
#include "GameManager.h"
#include "Resources.h"
#include "Bullet.h"



bool MonkeyCoco ::update() {
#ifdef _DEBUG
	string estado;
	switch (currState_)
	{
	case STATE::ATTACKING:
		estado = "ataque";
		break;
		case STATE::DIYING:
		estado = "muriendo";
		break;
		case STATE::IDLE:
		estado = "parado";
		break;
	default:
		break;
	}
	cout << estado << endl;
#endif // _DEBUG
	
	if (currState_ == STATE::DIYING) {
		//collisionManager::instance()->removeEnemy(this);
		return true;
	}
	if (currState_ == STATE::IDLE && isPlayerInRange() || isClonInRange() ) {
		currState_ = STATE::ATTACKING;
	}
	if (currState_ == STATE::ATTACKING && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		lastHit = SDL_GetTicks();
		attack();
	}
	return false;
}

void MonkeyCoco::changeAnim() {
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

//Se encarga de crear el coco en dirección al enemigo
void MonkeyCoco::attack() {
	Bullet* coco = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		pos_, currEnemy_->getPos(), currStats_.distDmg_);
	app_->getCurrState()->addRenderUpdateLists(coco);
}

//Inicializa al monkeyCoco
void MonkeyCoco::initObject() {

	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE ,MOVE_SPEED, MELEE_RATE, DIST_RATE);
	scale_.setVec(START_SCALE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)START_SCALE.getX(),(int)START_SCALE.getY() });
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)BOX_COLLISION.getX(),(int)BOX_COLLISION.getY() });
	//Falta el frame y animaciones
}

//Devuelve true si el jugador está en el rango de ataque del monkeyCoco
bool MonkeyCoco::isPlayerInRange() {
	GameManager* gm = GameManager::instance();
	if (currEnemy_ != nullptr && gm->getPlayer() == nullptr) { return false; };
	Point2D playerPos = gm->getPlayerPos();
	if (playerPos.getX() <= pos_.getX() + currStats_.distRate_ && playerPos.getX() >= pos_.getX() - currStats_.distRate_
		&& playerPos.getY() <= pos_.getY() + currStats_.distRate_ && playerPos.getY() >= pos_.getY() - currStats_.distRate_) {
		if (currEnemy_ == nullptr) {
			currEnemy_ = gm->getPlayer();
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
	if (currEnemy_ != nullptr && gm->getClon() == nullptr) { return false; };
	Point2D clonPos = gm->getClon()->getPos();
	if (clonPos.getX() <= pos_.getX() + currStats_.distRate_ && clonPos.getX() >= pos_.getX() - currStats_.distRate_
		&& clonPos.getY() <= pos_.getY() + currStats_.distRate_ && clonPos.getY() >= pos_.getY() - currStats_.distRate_) {
		if (currEnemy_ == nullptr) {//gestión de agro?
			currEnemy_ = gm->getClon();
		}
		return true;
	}
	else
	{
		return false;
	}
}
