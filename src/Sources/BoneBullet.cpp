#include "BoneBullet.h"
bool BoneBullet::update() {
	currTime_ = SDL_GetTicks();
	updateFrame();
	//Si ha pasado la mitad del tiempo de vida vuelve en direccion contraria
	if ((bulletlifeCD_.getDuration() <= lifeSpan_/2) && !returnBone) {
		dir_ = dir_ * -1;
		returnBone = true;
		//cuando el hueso vuelve puede volver a hacer daño al enemigo
		MakeDamage = true;
	}
	//Si se le ha acabado el tiempo de vida
	else if (!bulletlifeCD_.isCooldownActive()) {
		app_->getCurrState()->removeRenderUpdateLists(this);
	}
	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	}

	return false;
}

void BoneBullet::initObject()
{
	//Anim Hueso
	currAnim_ = Anim(BONE_FRAMES, W_BONE_FRAME, H_BONE_FRAME, BONE_FRAME_RATE, true);
	//Textura Bone
	texture_ = app_->getTextureManager()->getTexture(Resources::Bone);

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
