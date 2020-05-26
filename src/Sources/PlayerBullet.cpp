#include "PlayerBullet.h"
#include "CollisionCtrl.h"
#include "Collisions.h"

bool PlayerBullet::update()
{
	bulletlifeCD_.updateCooldown();

	//Si se le ha acabado el tiempo de vida
	if (!bulletlifeCD_.isCooldownActive()) {
 		CollisionCtrl::instance()->removePlayerBullet(this);
		onCollider();
	}
	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	}

	return false;
}

void PlayerBullet::searchEnemy(list<Enemy*> enemies, Enemy* currEnemy)
{
 	bool founded = false;						//Para saber si se encuentra target
	Vector2D newTarget(-100, -100);				//El nuevo target
	if (currRico < NUM_RICO) {
		SDL_Rect enemyRect;							//Rectángulo del enemigo
		Vector2D centerBullet = getCenter();	//Centro de la bala

		for (auto it = enemies.begin(); it != enemies.end(); ++it) {
			enemyRect = (*it)->getCollider();
			enemyRect.x += enemyRect.w / 2;	//Centro de la x
			enemyRect.y += enemyRect.h / 2; //Centro de la y

			//Para detectar que no se el mismo enemigo que acaba de impactar y que esté dentro del radio de detección
			if ((*it) != currEnemy && RectBall((float)enemyRect.x, (float)enemyRect.y, (float)enemyRect.w, (float)enemyRect.h, (float)centerBullet.getX(), (float)centerBullet.getY(), RADIUS)) {
				founded = true;
				Vector2D enemyTarget(enemyRect.x, enemyRect.y);				//Posición del target encontrado
				newTarget = target_.getClosest(enemyTarget, newTarget);	//Se mira cuál es el más cercano si el anterior o el nuevo
			}
		}
	}

	//Si no ha encontrado target, se destruye la bala
	if (!founded) {
		onCollider();
		CollisionCtrl::instance()->removePlayerBullet(this);
	}
	else {
		move(newTarget);		//La bala se mueve en la nueva dirección
		currRico++;				//Se actualiza el número de rebotes que lleva
		bulletlifeCD_.initCooldown(lifeSpan_);	//Se resetea el tiempo de vida
	}
}
