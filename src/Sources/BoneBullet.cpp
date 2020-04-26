#include "BoneBullet.h"
bool BoneBullet::update() {
	currTime_ = SDL_GetTicks();

	//Si ha pasado la mitad del tiempo de vida vuelve en direccion contraria
	if (((currTime_ - initTime_) / 1000 > lifeSpan_/2) && !returnBone) {
		dir_ = dir_ * -1;
		returnBone = true;
		//cuando el hueso vuelve puede volver a hacer daño al enemigo
		MakeDamage = true;
	}
	//Si se le ha acabado el tiempo de vida
	else if ((currTime_ - initTime_) / 1000 > lifeSpan_) {
		app_->getCurrState()->removeRenderUpdateLists(this);
	}
	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	}

	return false;
}
