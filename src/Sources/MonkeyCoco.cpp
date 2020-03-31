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
	string estado;
	switch (currState_)
	{
	case STATE::ATTACKING:
		estado = "ataque";
		break;
		case STATE::DYING:
		estado = "muriendo";
		break;
		case STATE::IDLE:
		estado = "parado";
		break;
		case STATE::MOVING:
			estado = "Moviendose";
			break;
	default:
		break;
	}
	cout << estado << endl;
	/*if (currEnemy_ != nullptr){
		cout << "( " << currEnemy_->getPos().getX() << " , " << currEnemy_->getPos().getY() << " )" << endl;
		cout << "( " << pos_.getX() << " , " <<pos_.getY() << " )" << endl;

	}*/
#endif // _DEBUG
	
	//Si el mono ha muerto
	if (currState_ == STATE::DYING) {
		//collisionManager::instance()->removeEnemy(this);
		//Tendría que hacer la animación de muerte
		CollisionCtrl::instance()->addEnemiesToErase(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si no tengo enemigo al que atacar me quedo en modo IDLE
	if (currEnemy_ == nullptr) {
		currState_ = STATE::IDLE;
	}
	//Si el mono no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el player
	if (currState_ == STATE::IDLE && (isPlayerInRange() || isClonInRange())) {
		currState_ = STATE::ATTACKING;
	}
	//Si el mono tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		//Si el mono tiene un enemigo y lo tiene a rango
		if (onRange()) {
			lastHit = SDL_GetTicks();
			attack();
		}
		//Si no tiene enemigo al que atacar, se pone en modo IDLE
		else
		{
			currState_ == STATE::IDLE;
			currEnemy_ = nullptr;
		}
	}
	return false;
}

bool MonkeyCoco::onRange() {
	if (currEnemy_ == nullptr) {
		return false;
	}
	SDL_Rect rangeAttack = { getPosX(),getPosY(),currStats_.distRange_ * 2, currStats_.distRange_ * 2 };
	if (currEnemy_ != nullptr && SDL_HasIntersection(&currEnemy_->getDestiny(), &rangeAttack)) {
		return true;
	}
	else
	{
		false;
	}
}

//Cambia la actual animación del mono
void MonkeyCoco::changeAnim(Anim& newAnim) {
	currAnim_ = newAnim;
}

//Se encarga de crear el coco en dirección al enemigo
void MonkeyCoco::attack() {
	Bullet* coco = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(pos_), currEnemy_->getPos(), currStats_.distDmg_, true);
	app_->getCurrState()->addRenderUpdateLists(coco);
	CollisionCtrl::instance()->addEnemyBullet(coco);
}

//Inicializa al monkeyCoco
void MonkeyCoco::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)BOX_COLLISION.getX(),(int)BOX_COLLISION.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	//Falta el frame y animaciones
	
}

//Esto es un apaño, se eliminara cuando este completa la gestión de muertes
void MonkeyCoco::onCollider()
{
	dynamic_cast<CaribbeanIslandState*>(app_->getCurrState())->addKills();
}

//Devuelve true si el jugador está en el rango de ataque del monkeyCoco y lo asigna a currEnemy_ si es así
bool MonkeyCoco::isPlayerInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return false; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + currStats_.distRange_ && playerPos.getX() >= pos_.getX() - currStats_.distRange_
		&& playerPos.getY() <= pos_.getY() + currStats_.distRange_ && playerPos.getY() >= pos_.getY() - currStats_.distRange_) {
		changeAgro(gm->getPlayer());
		return true;
	}
	else
	{
		return false;
	}	
}

//Devuelve true si el clon está en el rango de ataque del monkeyCoco y lo asigna a currEnemy_ si es así
bool MonkeyCoco::isClonInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getClon() == nullptr) { return false; }

	Point2D clonPos = gm->getClon()->getPos();
	if (currEnemy_ == nullptr && 
		clonPos.getX() <= pos_.getX() + currStats_.distRange_ && clonPos.getX() >= pos_.getX() - currStats_.distRange_
		&& clonPos.getY() <= pos_.getY() + currStats_.distRange_ && clonPos.getY() >= pos_.getY() - currStats_.distRange_){
		changeAgro(gm->getClon());
		static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
		return true;
	}
	else
	{
		return false;
	}
}
