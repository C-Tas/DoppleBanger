#include "NPC.h"
#include "CollisionCtrl.h"


void NPC::initObject() {
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	CollisionCtrl::instance()->addNPC((CollisionCtrl::NPCsNames)npcType_, this);
	initAnims();
}

void NPC::initAnims() {
	switch (npcType_) {
	case (int)CollisionCtrl::NPCsNames::ElderMan:
		npcIdle = { NUM_FRAMES_ELDERMAN, W_FRAME_ELDERMAN, H_FRAME_ELDERMAN, FRAME_RATE_ELDERMAN, true };
		break;
	case (int)CollisionCtrl::NPCsNames::Merchant:
		npcIdle = { NUM_FRAMES_MERCHANT, W_FRAME_MERCHANT, H_FRAME_MERCHANT, FRAME_RATE_MERCHANT, true };
		posCollision_ = { scale_.getX() / 5, scale_.getY() / 5 };
		scaleCollision_ = { 7 * (scale_.getX() / 10), 3 * (scale_.getX() / 5) };
		break;
	case (int)CollisionCtrl::NPCsNames::Chef:
		npcIdle = { NUM_FRAMES_CHEF, W_FRAME_CHEF, H_FRAME_CHEF, FRAME_RATE_CHEF, true };
		break;
	case (int)CollisionCtrl::NPCsNames::Morty:
		npcIdle = { NUM_FRAMES_MORTY, W_FRAME_MORTY, H_FRAME_MORTY, FRAME_RATE_MORTY, true };
		break;
	case (int)CollisionCtrl::NPCsNames::Parrot:
		npcIdle = { NUM_FRAMES_PARROT, W_FRAME_PARROT, H_FRAME_PARROT, FRAME_RATE_PARROT, true };
		break;
	case (int)CollisionCtrl::NPCsNames::Skeleton:
		npcIdle = { NUM_FRAMES_SKELETON, W_FRAME_SKELETON, H_FRAME_SKELETON, FRAME_RATE_SKELETON, true };
		break;
	case (int)CollisionCtrl::NPCsNames::Cartographer:
		npcIdle = { NUM_FRAMES_CARTOGRAPHER, W_FRAME_CARTOGRAPHER, H_FRAME_CARTOGRAPHER, FRAME_RATE_CARTOGRAPHER, true };
		break;
	}
	currAnim_ = npcIdle;
	frame_.x = frame_.y = 0;
	frame_.w = npcIdle.widthFrame_;
	frame_.h = npcIdle.heightFrame_;
}