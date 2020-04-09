#include "Bullet.h"
#include "Enemy.h"
#include "PlayState.h"
#include "Collisions.h"

void Bullet::init(Vector2D pos, Vector2D dir)
{
	initTime_ = SDL_GetTicks();

	//Se corrige la posici�n de la bala sustrayendo el offset de la escala
	pos_.setX(pos_.getX() - (scale_.getX() / 2));
	pos_.setY(pos_.getY() - (scale_.getY() / 2));

	//Se corrige la direcci�n para que la bala vaya centrada
	move(dir);
}

bool Bullet::update()
{
	currTime_ = SDL_GetTicks();

	//Si se le ha acabado el tiempo de vida
	if ((currTime_ - initTime_) / 1000 > lifeSpan_) { 
		app_->getCurrState()->removeRenderUpdateLists(this);
	}
	else {
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (speed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (speed_ * delta)));
	}

	return false;
}

//Se le pasa la lista de enemigos actual y el currEnemy
//es para descartarlo y que no repita target
void Bullet::searchEnemy(list<Enemy*> enemies, Enemy* currEnemy)
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
		app_->getCurrState()->removeRenderUpdateLists(this);
		CollisionCtrl::instance()->addPlayerBulletToErase(this);
	}
	else {
		move(newTarget);		//La bala se mueve en la nueva direcci�n
		currRico++;				//Se actualiza el n�mero de rebotes que lleva
		initTime_ = currTime_;	//Se resetea el tiempo de vida
	}
}
