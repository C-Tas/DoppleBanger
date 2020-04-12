#include "PlayerBullet.h"
#include "CollisionCtrl.h"
#include "Collisions.h"

void PlayerBullet::searchEnemy(list<Enemy*> enemies, Enemy* currEnemy)
{
 	bool founded = false;						//Para saber si se encuentra target
	Vector2D newTarget(-100, -100);				//El nuevo target
	if (currRico < NUM_RICO) {
		SDL_Rect enemyRect;							//Rect�ngulo del enemigo
		Vector2D centerBullet = getCenter(pos_);	//Centro de la bala

		for (auto it = enemies.begin(); it != enemies.end(); ++it) {
			enemyRect = (*it)->getCollider();
			enemyRect.x += enemyRect.w / 2;	//Centro de la x
			enemyRect.y += enemyRect.h / 2; //Centro de la y

			//Para detectar que no se el mismo enemigo que acaba de impactar y que est� dentro del radio de detecci�n
			if ((*it) != currEnemy && RectBall(enemyRect.x, enemyRect.y, enemyRect.w, enemyRect.h, centerBullet.getX(), centerBullet.getY(), RADIUS)) {
				founded = true;
				Vector2D enemyTarget(enemyRect.x, enemyRect.y);				//Posici�n del target encontrado
				newTarget = target_.getClosest(enemyTarget, newTarget);	//Se mira cu�l es el m�s cercano si el anterior o el nuevo
			}
		}
	}

	//Si no ha encontrado target, se destruye la bala
	if (!founded) {
		onCollider();
		CollisionCtrl::instance()->removePlayerBullet(this);
	}
	else {
		move(newTarget);		//La bala se mueve en la nueva direcci�n
		currRico++;				//Se actualiza el n�mero de rebotes que lleva
		initTime_ = currTime_;	//Se resetea el tiempo de vida
	}
}