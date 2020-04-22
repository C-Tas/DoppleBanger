#include "Cleon.h"
#include "GameManager.h"
#include "CollisionCtrl.h"

bool Cleon::update() {
	//Si Magordito muere
	if (currState_ == STATE::DYING) {
		//Desbloqueamos la última isla
		GameManager::instance()->setUnlockedIslands(Island::Volcanic);
		CollisionCtrl::instance()->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return false;
	}
	updateAnim();
	return false;
}

void Cleon::initObject() {
	texture_ = app_->getTextureManager()->getTexture(Resources::Cleon);
	CollisionCtrl::instance()->addEnemy(this);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnim();
}

void Cleon::initAnims() {
	idleAnim_ = Anim(NUM_FRAMES_IDLE, NUM_FRAMES_ROW_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, NAME_IDLE);
	runAnim_ = Anim(NUM_FRAMES_RUN, NUM_FRAMES_ROW_RUN, W_FRAME_RUN, H_FRAME_RUN, FRAME_RATE_RUN, NAME_RUN);
	assaultAnim_ = Anim(NUM_FRAMES_ASSAULT, NUM_FRAMES_ROW_ASSAULT, W_FRAME_ASSAULT, H_FRAME_ASSAULT, FRAME_RATE_ASSAULT, NAME_ASSAULT);
	meleeAnim_ = Anim(NUM_FRAMES_MELEE, NUM_FRAMES_ROW_MELEE, W_FRAME_MELEE, H_FRAME_MELEE, FRAME_RATE_MELEE, NAME_MELEE);
	barrelAnim_ = Anim(NUM_FRAMES_BARREL, NUM_FRAMES_ROW_BARREL, W_FRAME_BARREL, H_FRAME_BARREL, FRAME_RATE_BARREL, NAME_BARREL);
}
