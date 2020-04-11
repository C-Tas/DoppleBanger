#include "CollisionCtrl.h"
#include "Collisions.h"
#include "GameManager.h"

unique_ptr<CollisionCtrl> CollisionCtrl::instance_;

void CollisionCtrl::islandCollisions() {

	for (auto it = enemyBulletsToErase_.begin(); it != enemyBulletsToErase_.end(); ++it) {
		enemyBullets_.remove(*it);
	}
	enemyBulletsToErase_.clear();

	for (auto it = playerBulletsToErase_.begin(); it != playerBulletsToErase_.end(); ++it) {
		playerBullets_.remove(*it);
	}
	playerBulletsToErase_.clear();

	for (auto it = enemiesToErase_.begin(); it != enemiesToErase_.end(); ++it) {
		enemies_.remove(*it);
	}
	enemiesToErase_.clear();

	//Colisiones con obstáculos
	for (auto ob : obstacles_) {
		if (Collisions::collides(player_->getPos(), player_->getScaleX(), player_->getScaleY(),
			(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
			player_->stop();
			(ob)->onCollider();
		}
		for (auto enem : enemies_) {
			if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//Llamar a método que recalcule la trayectoria del enemigo (con pathfinding no sería necesario hacer este for)
				(ob)->onCollider();
			}
		}
		for (auto bullet : enemyBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				(ob)->onCollider();
				addEnemyBulletToErase(bullet);
				bullet->onCollider();
			}
		}
		for (auto bullet : playerBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				(ob)->onCollider();
				addPlayerBulletToErase(bullet);
				bullet->onCollider();
			}
		}
	}

	//Colisión enemigo con jugador o con balas del jugador
	for (auto enem : enemies_) {
		if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			enem->onCollider();
			//Cuando el jugador colisiona con el enemigo recibe daño
			//Falta añadir el método correspondiente
		}
		for (auto bullet : playerBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				enem->getPos(), enem->getScaleX(), enem->getScaleY())) {
				enem->reciveDmg(bullet->getDamage());
				addPlayerBulletToErase(bullet);
				bullet->onCollider();
			}
		}
	}
	//Colisión cofres con jugador
	//for (auto chest : chests_) {
	//	if (Collisions::collides(chest->getPos(), chest->getScaleX(), chest->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		chest->onCollider();
	//	}
	//}

	//Colisión bala del enemigo con jugador
	for (auto bullet : enemyBullets_) {
		if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			// si la bala puede hacer daño al jugador
			if (bullet->doDamage()) {
				player_->reciveDmg(bullet->getDamage());//el jugador recibe daño
				bullet->collisionDetected();//restamos uno al numero de golpes que puede realizar la bala
				bullet->setDoDamage(false);// ya no puede atacar al player hasta el siguiente golpe
			}
			//si ya no le quedan colisiones a la bala la borramos
			if (bullet->numCollisions() == 0 ){
				addEnemyBulletToErase(bullet);
				bullet->onCollider();
			}
		}
	}
}

void CollisionCtrl::shipCollisions() {	//Está comentado porque falta añadir la clase ShipObject
	//Colisión con los objetos del barco
    //for (auto ob : shipObjects_) {
    //    if (RectRect(player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
    //        ob.object->getPosX() + ob.object->getWidth() / 2, ob.object->getPosY() + ob.object->getHeight() / 2, ob.object->getScaleX(), ob.object->getScaleY())) {
    //        player_->stop();
    //        if (ob.click) {
    //            ob.click = false;
    //            switch (ob.id) {
    //            case Stash:
    //                ob.object->onColliderStash();
    //                break;
    //            case Door:
    //                ob.object->onColliderDoor();
    //                break;
    //            case Wheel:
    //                ob.object->onColliderWheel();
    //                break;
    //            case Exit:
    //                ob.object->onColliderExit();
    //                break;
    //            }
    //        }
    //    }
    //}

	//Colisión con los NPCs desbloqueados
}

//Enemigos --
//NPC
//Cofres --
//Obstáculos --
//Balas --
//Triggers

//ShipObject --
//NPC