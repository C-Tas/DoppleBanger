#include "Bullet.h"
#include "Enemy.h"
#include "PlayState.h"

void Bullet::init(Vector2D pos, Vector2D dir)
{
	initTime_ = SDL_GetTicks();

	//Se corrige la posición de la bala sustrayendo el offset de la escala
	pos_.setX(pos_.getX() - (scale_.getX() / 2));
	pos_.setY(pos_.getY() - (scale_.getY() / 2));

	//Se corrige la dirección para que la bala vaya centrada
	move(getCenter(dir));
}

bool Bullet::update()
{
	currTime_ = SDL_GetTicks();

	//Si se le ha acabado el tiempo de vida o se ha chocado con algo
	if ((currTime_ - initTime_) / 1000 > lifeSpan_) //|| colisión con paredes)
		app_->getCurrState()->removeRenderUpdateLists(this);

	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));

		Enemy* obj = static_cast<PlayState*>(app_->getStateMachine()->getState())->collidesWithEnemy(pos_, scale_);
		if (obj != nullptr)
		{
			obj->reciveDmg(damage_);
			app_->getStateMachine()->getState()->removeRenderUpdateLists(this);
		}
	}

	return false;
}