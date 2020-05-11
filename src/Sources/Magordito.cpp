#include "Magordito.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "PlayState.h"
#include "Collisions.h"
#include "Skeleton.h"
#include "Kirin.h"

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
		if ((SDL_GetTicks() - lastTeleport_) / 1000 > TP_CD) {
			enemyIsTooClose();
		}
 		double aux = SDL_GetTicks() - lastKirin_;
		if ((SDL_GetTicks() - lastKirin_) / 1000 > KIRIN_CD && onRange(KIRIN_RANGE_ATTACK)) {
			initKirinAnim();
		}
	}

	if (currState_ == STATE::SWIMMING) {
		teleportAnim();
	}
	else if (currState_ == STATE::FOLLOWING) {
		kirinAnim();
	}
	return false;
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

	//Kirin
	//Derecha arriba																					
	kirinAnims_.push_back(Anim(KIRIN_FRAMES, W_H_FRAME, W_H_FRAME, KIRIN_FRAME_RATE, false));
	kirinTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoKirinTopRight));
	//Derecha abajo
	kirinAnims_.push_back(Anim(KIRIN_FRAMES, W_H_FRAME, W_H_FRAME, KIRIN_FRAME_RATE, false));
	kirinTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoKirinRight));
	//Izquierda abajo																							
	kirinAnims_.push_back(Anim(KIRIN_FRAMES, W_H_FRAME, W_H_FRAME, KIRIN_FRAME_RATE, false));
	kirinTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoKirinLeft));
	//Izquierda arriba																				
	kirinAnims_.push_back(Anim(KIRIN_FRAMES, W_H_FRAME, W_H_FRAME, KIRIN_FRAME_RATE, false));
	kirinTx_.push_back(app_->getTextureManager()->getTexture(Resources::MagorditoKirinTopLeft));

	//Inicializamos con la animación del idle
	currDir_ = DIR::DOWN;
	initIdle();
}

void Magordito::kirin()
{
	if (currEnemy_ != nullptr) {
		double newX = currEnemy_->getCenter().getX() - scale_.getX() * 1.5 / 2;
		double newY = currEnemy_->getPos().getY() + currEnemy_->getScaleY() - scale_.getY() * 1.5;
		Kirin* kirin = new Kirin(app_, Vector2D(newX, newY), Vector2D(scale_.getX() * 1.5, scale_.getY() * 1.5));
	}
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

			return true;
		}
	}
	return false;
}

void Magordito::initialStats()
{
	rangeVision_ = 200;
	HEALTH = 4000;
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

void Magordito::teleport()
{
	lastTeleport_ = SDL_GetTicks();
	auto choice = app_->getRandom()->nextInt(0, altars.size());
	double newX = altars[choice]->getCenter().getX() - scale_.getX() / 2;
	double newY = altars[choice]->getPos().getY();
	pos_.setVec(Vector2D(newX, newY));
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

void Magordito::initKirinAnim()
{
	kirined_ = false;
	updateDirVisObjective(currEnemy_);
	currState_ = STATE::FOLLOWING;
	currAnim_ = kirinAnims_[(int)currDir_];
	texture_ = kirinTx_[(int)currDir_];

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

void Magordito::kirinAnim()
{
	if (!kirined_ && currAnim_.currFrame_ == KIRIN_ACTION) {
		kirined_ = true;
		kirin();
		lastKirin_ = SDL_GetTicks();
	}
	else if (currAnim_.currFrame_ >= KIRIN_FRAMES) {
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
