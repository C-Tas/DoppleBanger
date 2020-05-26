#include "NPC.h"
#include "CollisionCtrl.h"

void NPC::initObject() {
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	CollisionCtrl::instance()->addNPC((CollisionCtrl::NPCsNames)npcType_, this);
	initAnims();
}

void NPC::initAnims() {
	double w, h, x, y;
	switch (npcType_) {
	case (int)CollisionCtrl::NPCsNames::ElderMan:
		npcIdle = { NUM_FRAMES_ELDERMAN_DRINK, 100, 100, FRAME_RATE_ELDERMAN, true };
		venancioPushStart = { NUM_FRAMES_ELDERMAN_PUSH0, 100, 200, FRAME_RATE_ELDERMAN, false };
		venancioPushBucle = { NUM_FRAMES_ELDERMAN_PUSH1, 500, 500, FRAME_RATE_ELDERMAN, true };
		venancioPushFinish = { NUM_FRAMES_ELDERMAN_PUSH2, W_FRAME_ELDERMAN, H_FRAME_ELDERMAN, FRAME_RATE_ELDERMAN, false };

		drinkTexture = texture_;
		pushStartTexture = app_->getTextureManager()->getTexture(Resources::VenancioPushStart);
		pushBucleTexture = app_->getTextureManager()->getTexture(Resources::VenancioPushBucle);
		pushFinishTexture = app_->getTextureManager()->getTexture(Resources::VenancioPushFinish);

		timeDrink_ = rand() % 15000 + 5000;
		timePush_ = rand() % 15000 + 5000;
		lastDrink_ = SDL_GetTicks();

		w = 1 / 3;
		h = 2 / 4;
		x = 1 / 3;
		y = 1 / 4;
		scaleCollision_.setVec(Vector2D(scale_.getX() * w, scale_.getY() * h));
		posCollision_ = Vector2D(scale_.getX() * x, scale_.getY() * y);
		collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
		break;
	case (int)CollisionCtrl::NPCsNames::Merchant:
		npcIdle = { NUM_FRAMES_MERCHANT, W_FRAME_MERCHANT, H_FRAME_MERCHANT, FRAME_RATE_MERCHANT, true };
		w = 1 / 3;
		h = 1 / 1;
		x = 1 / 3;
		y = 1 / 1;
		scaleCollision_.setVec(Vector2D(scale_.getX() * w, scale_.getY() * h));
		posCollision_ = Vector2D(scale_.getX() * x, scale_.getY() * y);
		collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
		break;
	case (int)CollisionCtrl::NPCsNames::Chef:
		npcIdle = { NUM_FRAMES_CHEF, W_FRAME_CHEF, H_FRAME_CHEF, FRAME_RATE_CHEF, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	case (int)CollisionCtrl::NPCsNames::Morty:
		npcIdle = { NUM_FRAMES_MORTY, W_FRAME_MORTY, H_FRAME_MORTY, FRAME_RATE_MORTY, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	case (int)CollisionCtrl::NPCsNames::Parrot:
		npcIdle = { NUM_FRAMES_PARROT, W_FRAME_PARROT, H_FRAME_PARROT, FRAME_RATE_PARROT, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	case (int)CollisionCtrl::NPCsNames::Skeleton:
		npcIdle = { NUM_FRAMES_SKELETON, W_FRAME_SKELETON, H_FRAME_SKELETON, FRAME_RATE_SKELETON, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	case (int)CollisionCtrl::NPCsNames::Cartographer:
		npcIdle = { NUM_FRAMES_CARTOGRAPHER, W_FRAME_CARTOGRAPHER, H_FRAME_CARTOGRAPHER, FRAME_RATE_CARTOGRAPHER, true };
		w = 1 / 5;
		h = 2 / 4;
		x = 1 / 5;
		y = 1 / 4;
		scaleCollision_.setVec(Vector2D(scale_.getX() * w, scale_.getY() * h));
		posCollision_ = Vector2D(scale_.getX() * x, scale_.getY() * y);
		collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
		break;
	case 7:
		npcIdle = { NUM_FRAMES_ELDERMAN_FUNERAL, W_FRAME_ELDERMAN_FUNERAL, H_FRAME_ELDERMAN_FUNERAL, FRAME_RATE_ELDERMAN_FUNERAL, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	case 8:
		npcIdle = { NUM_FRAMES_MERCHANT_FUNERAL, W_FRAME_MERCHANT_FUNERAL, H_FRAME_MERCHANT_FUNERAL, FRAME_RATE_MERCHANT_FUNERAL, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	}

	currAnim_ = npcIdle;
	frame_.x = frame_.y = 0;
	frame_.w = npcIdle.widthFrame_;
	frame_.h = npcIdle.heightFrame_;
}

void NPC::initDrink() {
	texture_ = drinkTexture;
	currAnim_ = npcIdle;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	lastDrink_ = SDL_GetTicks();
}

void NPC::initPushStart() {
	texture_ = pushStartTexture;
	currAnim_ = venancioPushStart;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void NPC::initPushBucle() {
	texture_ = pushBucleTexture;
	currAnim_ = venancioPushBucle;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	lastPush_ = SDL_GetTicks();
}

void NPC::initPushFinish() {
	texture_ = pushFinishTexture;
	currAnim_ = venancioPushFinish;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void NPC::drinkAnim() {
	if (SDL_GetTicks() - lastDrink_ >= timeDrink_ && currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {
		initPushStart();
		timeDrink_ = rand() % 15000 + 5000;
	}
}

void NPC::pushStartAnim() {
	if (currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {
		initPushBucle();
	}
}

void NPC::pushBucleAnim() {
	if (SDL_GetTicks() - lastPush_ >= timePush_ && currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {
		initPushFinish();
	}
}

void NPC::pushFinishAnim() {
	if (currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {
		initDrink();
		timePush_ = rand() % 15000 + 5000;
	}
}

bool NPC::update() {
	updateFrame();
	if (npcType_ == (int)CollisionCtrl::NPCsNames::ElderMan) {
		if (texture_ == drinkTexture) drinkAnim();
		else if (texture_ == pushStartTexture) pushStartAnim();
		else if (texture_ == pushBucleTexture) pushBucleAnim();
		else if (texture_ == pushFinishTexture) pushFinishAnim();
	}

	return false;
}