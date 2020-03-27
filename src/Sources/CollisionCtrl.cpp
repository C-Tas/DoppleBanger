#include "CollisionCtrl.h"
#include "Collisions.h"
#include "GameManager.h"

unique_ptr<CollisionCtrl> CollisionCtrl::instance_;

void CollisionCtrl::islandCollisions() {
	//Colisiones con obst�culos
	for (auto ob : obstacles_) {
		if (Collisions::collides(player_->getPos(), player_->getScaleX(), player_->getScaleY(),
			(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
			player_->stop();
			(ob)->onCollider();
		}
		for (auto enem : enemies_) {
			if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//Llamar a m�todo que recalcule la trayectoria del enemigo (con pathfinding no ser�a necesario hacer este for)
				(ob)->onCollider();
			}
		}
	}
	//Colisi�n enemigo con jugador o con balas del jugador
	for (auto enem : enemies_) {
		if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			enem->onCollider();
			player_->onCollider();
		}
		//for (auto bullet : playerBullets_) {
		//	if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
		//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
		//		enem.receiveDamge(bullets.getDamage());
		//		removePlayerBullet(bullet);
		//	}
		//}
	}
	//Colisi�n cofres con jugador
	//for (auto chest : chests_) {
	//	if (Collisions::collides(chest->getPos(), chest->getScaleX(), chest->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		chest->onCollider();
	//	}
	//}
	//Colisi�n bala del enemigo con jugador
	//for (auto bullet : enemyBullets_) {
	//	if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		player_.receiveDamge(bullet.getDamage());
	//		removeEnemyBullet(bullet);
	//	}
	//}
	//Colisi�n bala del jugador con enemigo
	//for (auto bullets : playerBullets_) {
	//	if (Collisions::collides(bullets->getPos(), bullets->getScaleX(), bullets->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		/*Se llama al m�todo correspondiente*/
	//	}
	//}
}

void CollisionCtrl::shipCollisions() {	//Est� comentado porque falta a�adir la clase ShipObject
	//Colisi�n con los objetos del barco
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
    //                ob.object->onColliderWheel(GameManager::instance()->getCurrIsland());
    //                break;
    //            case Exit:
    //                ob.object->onColliderExit();
    //                break;
    //            }
    //        }
    //    }
    //}

	//Colisi�n con los NPCs desbloqueados
}

//Enemigos --
//NPC
//Cofres --
//Obst�culos --
//Balas --
//Triggers

//ShipObject --
//NPC