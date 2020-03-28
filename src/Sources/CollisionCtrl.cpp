#include "CollisionCtrl.h"
#include "Collisions.h"
#include "GameManager.h"

unique_ptr<CollisionCtrl> CollisionCtrl::instance_;

void CollisionCtrl::islandCollisions() {
	//Colisiones con obstáculos
	for (auto ob : obstacles_) {
		//Con jugador
		if (Collisions::collides(player_->getPos(), player_->getScaleX(), player_->getScaleY(),
			(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
			player_->stop();
			(ob)->onCollider();
		}

		//Con enemigos
		for (auto enem : enemies_) {
			if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//Llamar a método que recalcule la trayectoria del enemigo (con pathfinding no sería necesario hacer este for)
				(ob)->onCollider();
			}
		}
		
		//Con balas del jugador
		//for (auto bullet : playerBullets_) {
		//	if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
		//		(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
		//		Método para destruir bala
		//		removePlayerBullet(bullet);
		//	}
		//}

		//Con balas de los enemigos
		//for (auto bullet : enemyBullets_) {
		//	if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
		//		(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
		//		Método para destruir bala
		//		removeEnemyBullet(bullet);
		//	}
		//}
	}

	//Colisión enemigo con jugador o con balas del jugador
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

	//Colisión bala del enemigo con jugador
	//for (auto bullet : enemyBullets_) {
	//	if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		player_.receiveDamge(bullet.getDamage());
	//		removeEnemyBullet(bullet);
	//	}
	//}

	//Colisión NPC con jugador
	if (npc_.object != nullptr) {
		if (Collisions::collides(npc_.object->getPos(), npc_.object->getScaleX(), npc_.object->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			switch (npc_.id) {
			case ElderMan:
				//npc_.object->getTextBox().dialogElderMan(-1);
				break;
			case Merchant:
				//npc_.object->getTextBox().dialogMerchant();
				break;
			case Chef:
				//npc_.object->getTextBox().dialogChef(true);
				break;
			case Morty:
				//npc_.object->getTextBox().dialogMorty(true);
				break;
			case Parrot:
				//npc_.object->getTextBox().dialogParrot();
				break;
			}
		}
	}

	//Colisión cofres con jugador
	//for (auto chest : chests_) {
	//	if (Collisions::collides(chest->getPos(), chest->getScaleX(), chest->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		chest->onCollider();
	//		removeChest(chest);
	//	}
	//}

	//Jugador con triggers
	for (auto trigg : triggers_) {
		if (player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
			trigg->getPosX() + trigg->getScaleX() / 2, trigg->getPosY() + trigg->getScaleY() / 2, trigg->getScaleX(), trigg->getScaleY()) {
			trigg->onOverlap();
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
	//                ob.object->onColliderWheel(GameManager::instance()->getCurrIsland());
	//                break;
	//            case Exit:
	//                ob.object->onColliderExit();
	//                break;
    //            }
    //        }
    //    }
    //}

	//Colisión con los NPCs desbloqueados
	for (auto npc : npcs_) {
		if (RectRect(player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
			npc.object->getPosX() + npc.object->getScaleX() / 2, npc.object->getPosY() + npc.object->getScaleY() / 2, npc.object->getScaleX(), npc.object->getScaleY() / 10)) {
			player_->stop();

	        switch (npc.id) {
	        case Chef:
				//npc.object->getTextBox().dialogChef(false);
	            break;
	        case Morty:
				//npc.object->getTextBox().dialogMorty(false);
	            break;
			case Parrot:
				//npc.object->getTextBox().dialogParrot();
				break;
			}
		}
	}
}