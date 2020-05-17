#include "Blunderbuss.h"

Blunderbuss::Blunderbuss(Application* app, Texture* tex, Vector2D pos, Vector2D dir, int damage,double lifeSpan, double bulletSpeed) : GameObject(), app_(app)
{
	collisionCtrol = CollisionCtrl::instance();
	auto playerScale = GameManager::instance()->getPlayer()->getScale();
	auto distanceX = (NUM_BULLETS / 2) * DEVIATION_X;
	auto distanceY = (NUM_BULLETS / 2) * DEVIATION_Y;
	Vector2D dist = { abs(pos.getX() - dir.getX()) ,abs(pos.getY() - dir.getY()) };
	Vector2D firstBullet = { dir.getX() + distanceX ,dir.getY() + distanceY };

	if (dist.getX() < playerScale.getX() * 0.1 && dist.getY() < playerScale.getY() * 0.1) {
		//arriba a la derecha
		if (pos.getX() < dir.getX() && pos.getY() > dir.getY()) {
			dir.setVec({ pos.getX() + playerScale.getX(), pos.getY() - playerScale.getY() });
		}
		//arriba a la izquierda
		else if (pos.getX() > dir.getX() && pos.getY() > dir.getY()) {
			dir.setVec({ pos.getX() - playerScale.getX(), pos.getY() - playerScale.getY() });
		}
		//Abajo a la izquierda
		else if (pos.getX() > dir.getX() && pos.getY() < dir.getY()) {
			dir.setVec({ pos.getX() - playerScale.getX(), pos.getY() + playerScale.getY() });

		}
		//Abajo a la derecha
		else if (pos.getX() < dir.getX() && pos.getY() < dir.getY()) {
			dir.setVec({ pos.getX() + playerScale.getX(), pos.getY() + playerScale.getY() });
		}
		
	}else
	//Establece la posición inicial en función de la cantidad de balas que tiene para generara el cono 
	//arriba a la derecha
	if (pos.getX() < dir.getX() && pos.getY() > dir.getY()) {
		firstBullet = { dir.getX() + distanceX ,dir.getY() + distanceY };
	}
	//arriba a la izquierda
	else if (pos.getX() > dir.getX() && pos.getY() > dir.getY()) {
		firstBullet = { dir.getX() + distanceX ,dir.getY() - distanceY };
	}
	//Abajo a la izquierda
	else if (pos.getX() > dir.getX() && pos.getY() < dir.getY()) {
		firstBullet = { dir.getX() - distanceX ,dir.getY() - distanceY };
	}
	//Abajo a la derecha
	else if (pos.getX() < dir.getX() && pos.getY() < dir.getY()) {
		firstBullet = { dir.getX() - distanceX ,dir.getY() + distanceY };
	}


	for (int i = 0; i < NUM_BULLETS; i++) {
		PlayerBullet* currBullet = new PlayerBullet(app, tex, pos, firstBullet, damage, lifeSpan, bulletSpeed);
		app->getCurrState()->addRenderUpdateLists(currBullet);
		collisionCtrol->addPlayerBullet(currBullet);
		bullets_.push_back(currBullet);
		//modificar la siguiente
		if (pos.getX() < dir.getX() && pos.getY() > dir.getY()) {
			firstBullet.setX(firstBullet.getX() - DEVIATION_X);
			firstBullet.setY(firstBullet.getY() - DEVIATION_Y);
		}
		//arriba a la izquierda
		else if (pos.getX() > dir.getX() && pos.getY() > dir.getY()) {
			firstBullet.setX(firstBullet.getX() - DEVIATION_X);
			firstBullet.setY(firstBullet.getY() + DEVIATION_Y);
		}
		//Abajo a la izquierda
		else if (pos.getX() > dir.getX() && pos.getY() < dir.getY()) {
			firstBullet.setX(firstBullet.getX() + DEVIATION_X);
			firstBullet.setY(firstBullet.getY() + DEVIATION_Y);
		}
		//Abajo a la derecha
		else if (pos.getX() < dir.getX() && pos.getY() < dir.getY()) {
			firstBullet.setX(firstBullet.getX() + DEVIATION_X);
			firstBullet.setY(firstBullet.getY() - DEVIATION_Y);
		}
	}
}

void Blunderbuss::activatePerforate()
{
	for (auto i : bullets_) {
		i->setPerforate(true);
	}
}

void Blunderbuss::activateRicochet()
{
	for (auto i : bullets_) {
		i->setRicochet(true);
	}
}

const int Blunderbuss::getCurrBullets()
{
	auto aux = 0;
	for (auto i : bullets_) {
		if (i != nullptr) aux++;
	}
	return aux;
}
