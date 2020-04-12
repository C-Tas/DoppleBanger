#include "NPC.h"
#include "CollisionCtrl.h"


void NPC::initObject() {
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	CollisionCtrl::instance()->addNPC((CollisionCtrl::NPCsNames)npcType_, this);
	initAnim();
}

void NPC::initAnim() {
	switch (npcType_) {
	case (int)CollisionCtrl::NPCsNames::ElderMan:
		npcIdle = { NUM_FRAMES_ELDERMAN, W_FRAME_ELDERMAN, H_FRAME_ELDERMAN, FRAME_RATE_ELDERMAN, NAME };
		break;
	case (int)CollisionCtrl::NPCsNames::Merchant:
		npcIdle = { NUM_FRAMES_MERCHANT, W_FRAME_MERCHANT, H_FRAME_MERCHANT, FRAME_RATE_MERCHANT, NAME };
		break;
	case (int)CollisionCtrl::NPCsNames::Chef:
		npcIdle = { NUM_FRAMES_CHEF, W_FRAME_CHEF, H_FRAME_CHEF, FRAME_RATE_CHEF, NAME };
		break;
	case (int)CollisionCtrl::NPCsNames::Morty:
		npcIdle = { NUM_FRAMES_MORTY, W_FRAME_MORTY, H_FRAME_MORTY, FRAME_RATE_MORTY, NAME };
		break;
	case (int)CollisionCtrl::NPCsNames::Parrot:
		npcIdle = { NUM_FRAMES_PARROT, W_FRAME_PARROT, H_FRAME_PARROT, FRAME_RATE_PARROT, NAME };
		break;
	}
	currAnim_ = npcIdle;
	frame_.x = frame_.y = 0;
	frame_.w = npcIdle.widthFrame_;
	frame_.h = npcIdle.heightFrame_;
}