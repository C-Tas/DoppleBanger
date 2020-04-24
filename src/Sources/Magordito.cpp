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
	return false;
}

void Magordito::initObject() {
	texture_ = app_->getTextureManager()->getTexture(Resources::Magordito);
	CollisionCtrl::instance()->addEnemy(this);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnims();
}

void Magordito::initAnims() {
	idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true);
	teleportAnim_ = Anim(NUM_FRAMES_TELEPORT, W_FRAME_TELEPORT, H_FRAME_TELEPORT, FRAME_RATE_TELEPORT, false);
	kirinAnim_ = Anim(NUM_FRAMES_KIRIN, W_FRAME_KIRIN, H_FRAME_KIRIN, FRAME_RATE_KIRIN, false);
}