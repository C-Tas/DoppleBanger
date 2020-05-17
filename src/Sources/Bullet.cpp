#include "Bullet.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

void Bullet::initObject(Vector2D pos, Vector2D dir)
{
	bulletlifeCD_.initCooldown(lifeSpan_);
	cout << "INICIADO con lifespan " << lifeSpan_ << endl;

	//Se corrige la posición de la bala sustrayendo el offset de la escala
	pos_.setX(pos_.getX() - (scale_.getX() / 2));
	pos_.setY(pos_.getY() - (scale_.getY() / 2));

	//Se corrige la dirección para que la bala vaya centrada
	move(dir);
}

bool Bullet::update()
{
	bulletlifeCD_.updateCooldown();

	//Si se le ha acabado el tiempo de vida
	if (!bulletlifeCD_.isCooldownActive()) { 
		CollisionCtrl::instance()->removeEnemyBullet(this);
		onCollider();
	}
	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	}

	return false;
}
