#include "Magordito.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "PlayState.h"
#include "Collisions.h"

bool Magordito::update() {
	updateFrame();
	//Si Magordito muere
	if (currState_ == STATE::DYING) {
		//Desbloqueamos la �ltima isla
		GameManager::instance()->setUnlockedIslands(Island::Volcanic);
		CollisionCtrl::instance()->removeEnemy(this);
		dynamic_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return false;
	}
	if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	if (currState_ == STATE::ATTACKING) {
		//Si el player est� cerca y no tengo enfriamiento en el teleport
		if (TP_CD <= SDL_GetTicks() - lastTeleport_) {
			enemyIsTooClose();
		}
		if (onRange(KIRIN_RANGE_ATTACK)) {
			if (KIRIN_CD <= SDL_GetTicks() - lastKirin_ ) {
 				kirin();
			}
		}
	}

	if (currState_ == STATE::SWIMMING) {
		teleportAnim();
	}
	return false;
}

void Magordito::updateDirVisObjective(GameObject* objective)
{
	if (objective != nullptr) {
		Vector2D center = getCenter();		//Punto de referencia
		Vector2D enemyCenter = objective->getCenter();
		Vector2D dir = enemyCenter - center;		//Vector dirección
		dir.normalize();
		double angle = atan2(dir.getY(), dir.getX()) * 180 / M_PI;
		if (angle >= 0) {
			if (angle <= 90.0) currDir_ = DIR::RIGHT; //Para la derecha abajo
			else currDir_ = DIR::DOWN;	//Para abajo izquierda
		}
		else {
			if (angle >= -90.0) currDir_ = DIR::UP;	//Para la derecha arriba
			else currDir_ = DIR::LEFT;	//Para la izquierda arriba
		}
	}
}

void Magordito::initObject() {
	texture_ = app_->getTextureManager()->getTexture(Resources::Magordito);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initialStats();
	initAnims();
	currState_ = STATE::IDLE;
	player_ = GameManager::instance()->getPlayer();
	tag_ = "Magordito";
}

void Magordito::initAnims() {
	//Idle
	//Derecha arriba																					
	idleAnims_.push_back(Anim(IDLE_FRAMES, W_H_FRAME, W_H_FRAME, IDLE_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoIdleTopRight));
	//Derecha abajo
	idleAnims_.push_back(Anim(IDLE_FRAMES, W_H_FRAME, W_H_FRAME, IDLE_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoIdleRight));
	//Izquierda abajo																							
	idleAnims_.push_back(Anim(IDLE_FRAMES, W_H_FRAME, W_H_FRAME, IDLE_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoIdleLeft));
	//Izquierda arriba																				
	idleAnims_.push_back(Anim(IDLE_FRAMES, W_H_FRAME, W_H_FRAME, IDLE_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoIdleTopLeft));

	//Viaje Astral
	//Derecha arriba																					
	tpAnims_.push_back(Anim(TP_FRAMES, W_H_FRAME, W_H_FRAME, TP_FRAME_RATE, false));
	tpTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoTpTopRight));
	//Derecha abajo
	tpAnims_.push_back(Anim(TP_FRAMES, W_H_FRAME, W_H_FRAME, TP_FRAME_RATE, false));
	tpTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoTpRight));
	//Izquierda abajo																							
	tpAnims_.push_back(Anim(TP_FRAMES, W_H_FRAME, W_H_FRAME, TP_FRAME_RATE, false));
	tpTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoTpLeft));
	//Izquierda arriba																				
	tpAnims_.push_back(Anim(TP_FRAMES, W_H_FRAME, W_H_FRAME, TP_FRAME_RATE, false));
	tpTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoTpTopLeft));

	//Inicializamos con la animación del idle
	currDir_ = DIR::DOWN;
	initIdle();
}

void Magordito::kirin()
{
	if (currEnemy_ != nullptr) {
		lastKirin_ = SDL_GetTicks();
		auto enem = dynamic_cast<Player*>(currEnemy_);
		enem->receiveDamage(KIRIN_DMG);
	}
}

void Magordito::initKirinAnim()
{

}

inline bool Magordito::enemyIsTooClose()
{
	if (currEnemy_ != nullptr) {
		Vector2D center = getCenter();
		auto enem = dynamic_cast<Collider*>(currEnemy_);
		Vector2D enemCenter = currEnemy_->getCenter();
		if (RectRect(center.getX(), center.getY(), RANGE_TO_TP * 2, RANGE_TO_TP * 2,
			enemCenter.getX(), enemCenter.getY(), enem->getColliderScale().getX(), enem->getColliderScale().getY())) {
			initTeleport();
			//teleport();
			return true;
		}
	}
	return false;
}

void Magordito::initialStats()
{
	rangeVision_ = 200;
	HEALTH = 100;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 750;
	DIST_DMG = 300;
	CRIT = 0;
	MELEE_RANGE = 200;
	DIST_RANGE = 350;
	MOVE_SPEED = 100;
	MELEE_RATE = 1;
	DIST_RATE = 2500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

//TODO
void Magordito::teleport()
{
	lastTeleport_ = SDL_GetTicks();
	cout << "TP \n";
	auto choice = app_->getRandom()->nextInt(0, altars.size());
	pos_.setVec(altars[choice]->getPos());
	auto clon = dynamic_cast<Clon*>(currEnemy_);
	if(clon != nullptr){ altars[choice]->setEnemyToMobs(clon); }
	altars[choice]->activeResurrect();
}

void Magordito::lostAggro()
{
	currEnemy_ = GameManager::instance()->getPlayer(); 
}

void Magordito::initIdle()
{
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Magordito::initTeleport()
{
	currState_ = STATE::SWIMMING;
	texture_ = tpTx_[(int)currDir_];
	currAnim_ = tpAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Magordito::teleportAnim()
{
	if (currAnim_.currFrame_ >= TP_FRAMES) {
		teleport();
		updateDirVisObjective(currEnemy_);
		initIdle();
	}
}

void Magordito::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}
