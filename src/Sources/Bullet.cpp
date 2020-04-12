#include "Bullet.h"
#include "Enemy.h"
#include "PlayState.h"

void Bullet::initObject(Vector2D pos, Vector2D dir)
{
	initTime_ = SDL_GetTicks();

	//Se corrige la posición de la bala sustrayendo el offset de la escala
	pos_.setX(pos_.getX() - (scale_.getX() / 2));
	pos_.setY(pos_.getY() - (scale_.getY() / 2));

	//Se corrige la dirección para que la bala vaya centrada
	move(dir);
}

bool Bullet::update()
{
	currTime_ = SDL_GetTicks();

	//Si se le ha acabado el tiempo de vida
	if ((currTime_ - initTime_) / 1000 > lifeSpan_) { 
		onCollider();
	}
	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	}

	return false;
}
