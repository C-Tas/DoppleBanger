#include "Chest.h"
#include "HandleEvents.h"
#include "CollisionCtrl.h"

void Chest::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Chest));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addChest(this);
	
	initAnim();
}

void Chest::initAnim() {
	//Para la animación de abrir
	openAnim_ = Anim(NUM_FRAMES_OPEN, W_FRAME_OPEN, H_FRAME_OPEN, FRAME_RATE_OPEN, false);

	texture_ = app_->getTextureManager()->getTexture(Resources::Chest);
	currAnim_ = openAnim_;

	//Se inicia el frame
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

bool Chest::update() {
	if (open) {
		updateFrame();

		if (currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {
			if (gold_ == 0) GameManager::instance()->addToInventory(rN.genEquip());
			else GameManager::instance()->addInventoryGold(gold_);

			app_->getCurrState()->removeRenderUpdateLists(this);
			CollisionCtrl::instance()->removeChest(this);
		}
	}
	return false;
}

void Chest::onCollider() {
	open = true;	
	app_->getAudioManager()->playChannel(Resources::ChestOpeningAudio, 0, Resources::ChestChannelChannel);
}