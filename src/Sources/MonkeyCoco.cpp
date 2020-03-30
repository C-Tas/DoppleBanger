#include "MonkeyCoco.h"
#include <iostream>
#include "GameManager.h"
#include "Resources.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "CaribbeanIslandState.h"



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
		//Tendría que hacer la animación de muerte
		CollisionCtrl::instance()->addEnemiesToErase(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
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

void MonkeyCoco::onCollider()
{
	dynamic_cast<CaribbeanIslandState*>(app_->getCurrState())->addKills();
}

//Devuelve true si el jugador está en el rango de ataque del monkeyCoco
bool MonkeyCoco::isPlayerInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return false; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + currStats_.distRange_ && playerPos.getX() >= pos_.getX() - currStats_.distRange_
		&& playerPos.getY() <= pos_.getY() + currStats_.distRange_ && playerPos.getY() >= pos_.getY() - currStats_.distRange_) {
		currEnemy_ = gm->getPlayer();
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
	if (gm->getClon() == nullptr) { return false; }
	else if (currEnemy_ != nullptr){
		Point2D clonPos = gm->getClon()->getPos();
		if (clonPos.getX() <= pos_.getX() + currStats_.distRange_ && clonPos.getX() >= pos_.getX() - currStats_.distRange_
			&& clonPos.getY() <= pos_.getY() + currStats_.distRange_ && clonPos.getY() >= pos_.getY() - currStats_.distRange_) {
			currEnemy_ = gm->getClon();
			return true;
		}
	}
	else
	{
		return false;
	}
}
