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
	move(dir);
}

bool Bullet::update()
{
	currTime_ = SDL_GetTicks();

	//Si se le ha acabado el tiempo de vida o se ha chocado con algo
	//if ((currTime_ - initTime_) / 1000 > lifeSpan_) { //|| colisión con paredes)
	//	if (enemyBullet_) CollisionCtrl::instance()->addEnemyBulletToErase(this);
	//	else CollisionCtrl::instance()->addPlayerBulletToErase(this);
	//	app_->getCurrState()->removeRenderUpdateLists(this);
	//}
	//else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	//}

	return false;
}

void Bullet::move(Point2D target)
{
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(target);
	dir_.setX(target_.getX() - getCenter(pos_).getX());
	dir_.setY(target_.getY() - getCenter(pos_).getY());
	dir_.normalize();
}
