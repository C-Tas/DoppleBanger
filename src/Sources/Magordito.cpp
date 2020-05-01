#include "Magordito.h"
#include "GameManager.h"
#include "CollisionCtrl.h"

bool Magordito::update() {
	updateFrame();
	//Si Magordito muere
	if (currState_ == STATE::DYING) {
		//Desbloqueamos la última isla
		GameManager::instance()->setUnlockedIslands(Island::Volcanic);
		CollisionCtrl::instance()->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return false;
	}
	if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	if (currState_ == STATE::ATTACKING) {
		//A falta de cambiar el orden en función de la importancia de los ataques
		if (onRange(KIRIN_RANGE_ATTACK)) {
			if (KIRIN_CD <= SDL_GetTicks() - lastKirin_ ) {
				kirin();
			}
			
		}
		else
		{
			//teleport?
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
}

void Magordito::initAnims() {
	kirinAnim_ = Anim(KIRIN_FRAMES, W_FRAME_KIRIN, H_FRAME_KIRIN, KIRIN_FRAME_RATE, false);
	kirinTx_.push_back(app_->getTextureManager()->getTexture(Resources::Kirin));
}

void Magordito::kirin()
{
	lastKirin_ = SDL_GetTicks();
	auto kirinRect = SDL_Rect{ (int)player_->getPosX(),(int)player_->getPosY(),(int)AREA_DMG_W,(int)AREA_DMG_H };
	if (SDL_HasIntersection(&kirinRect, &player_->getDestiny())) {
		player_->receiveDamage(KIRIN_DMG);
		cout << "KIRIN!" << endl;
	}
}

void Magordito::initKirinAnim()
{

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
