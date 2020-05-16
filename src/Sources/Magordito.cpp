#include "Magordito.h"
#include "GameManager.h"
#include "CollisionCtrl.h"

bool Magordito::update() {
	updateFrame();
	//Si Magordito muere
	if (currState_ == STATE::DYING) {
		//Desbloqueamos la �ltima isla
		GameManager::instance()->setUnlockedIslands(Island::Volcanic);
		CollisionCtrl::instance()->removeEnemy(this);
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

void Magordito::initAnims() {
	kirinAnim_ = Anim(KIRIN_FRAMES, W_FRAME_KIRIN, H_FRAME_KIRIN, KIRIN_FRAME_RATE, false);
	kirinTx_.push_back(app_->getTextureManager()->getTexture(Resources::Kirin));
}

void Magordito::updateCooldowns()
{
}

void Magordito::kirin()
{
	if (currEnemy_ != nullptr) {
		lastKirin_ = SDL_GetTicks();
		auto kirinRect = SDL_Rect{ (int)currEnemy_->getPosX(),(int)currEnemy_->getPosY(),(int)AREA_DMG_W,(int)AREA_DMG_H };
		if (SDL_HasIntersection(&kirinRect, &player_->getDestiny())) {
			auto enem = dynamic_cast<Player*>(currEnemy_);
			if (enem) {
				player_->receiveDamage(KIRIN_DMG);
				cout << "KIRIN!" << endl;
			}

		}
	}

}

void Magordito::initKirinAnim()
{

}

inline bool Magordito::enemyIsTooClose()
{
	SDL_Rect range = { (int)(getPosX() - RANGE_TO_TP) ,(int)(getPosY() - RANGE_TO_TP) , (int)(RANGE_TO_TP * 2) , (int)(RANGE_TO_TP * 2) };
	auto enem = dynamic_cast<Draw*>(currEnemy_);
	if (SDL_HasIntersection(&range, &enem->getDestiny())) {
		teleport();
		return true;
	}
	else
	{
		return false;
	}
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

void Magordito::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}
