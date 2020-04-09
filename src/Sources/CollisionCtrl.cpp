#include "CollisionCtrl.h"
#include "Collisions.h"
#include "GameManager.h"

unique_ptr<CollisionCtrl> CollisionCtrl::instance_;

void CollisionCtrl::islandCollisions() {
	//Quitamos a los enemigos de la lista
	for (auto it = enemiesToErase_.begin(); it != enemiesToErase_.end(); ++it) {
		enemies_.remove(*it);
	}
	enemiesToErase_.clear();
	//Quitamos a los cofres de la lista
	//for (auto it = chestsToErase_.begin(); it != chestsToErase_.end(); ++it) {
	//	chests_.remove(*it);
	//}
	//chestsToErase_.clear();
	//Quitamos a las balas de las listas
	for (auto it = playerBulletsToErase_.begin(); it != playerBulletsToErase_.end(); ++it) {
		playerBullets_.remove(*it);
	}
	playerBulletsToErase_.clear();
	for (auto it = enemyBulletsToErase_.begin(); it != enemyBulletsToErase_.end(); ++it) {
		enemyBullets_.remove(*it);
	}
	enemyBulletsToErase_.clear();
	//Quitamos a los triggers de la lista
	for (auto it = triggersToErase_.begin(); it != triggersToErase_.end(); ++it) {
		triggers_.remove(*it);
	}
	triggersToErase_.clear();

	//Colisiones con obst�culos
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
				//Llamar a m�todo que recalcule la trayectoria del enemigo (con pathfinding no ser�a necesario hacer este for)
				(ob)->onCollider();
			}
		}
		
		//Con balas del jugador
		for (auto bullet : playerBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//M�todo para destruir bala
				removePlayerBullet(bullet);
			}
		}

		//Con balas de los enemigos
		for (auto bullet : enemyBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//M�todo para destruir bala
				removeEnemyBullet(bullet);
			}
		}
	}

	//Colisi�n enemigo con jugador o con balas del jugador
	for (auto enem : enemies_) {
		if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			enem->onCollider();
			//Cuando el jugador colisiona con el enemigo recibe da�o
			//Falta a�adir el m�todo correspondiente
		}
		for (auto bullet : playerBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				enem->getPos(), enem->getScaleX(), enem->getScaleY())) {
				enem->receiveDamage(bullet->getDamage());
				removePlayerBullet(bullet);
				bullet->onCollider();
			}
		}
	}

	//Colisi�n bala del enemigo con jugador
	for (auto bullet : enemyBullets_) {
		if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			player_->receiveDamage(bullet->getDamage());
			removeEnemyBullet(bullet);
		}
	}

	//Colisi�n NPC con jugador
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

	//Colisi�n cofres con jugador
	//for (auto chest : chests_) {
	//	if (Collisions::collides(chest->getPos(), chest->getScaleX(), chest->getScaleY(),
	//		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
	//		chest->onCollider();
	//		removeChest(chest);	//Para que no pueda volver a abrirse el mismo cofre
	//	}++
	//}

	//Jugador con triggers
	/*for (auto trigg : triggers_) {
		if (player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
			trigg->getPosX() + trigg->getScaleX() / 2, trigg->getPosY() + trigg->getScaleY() / 2, trigg->getScaleX(), trigg->getScaleY()) {
			trigg->onOverlap();
		}
	}*/
}

void CollisionCtrl::shipCollisions() {	//Est� comentado porque falta a�adir la clase ShipObject
	Vector2D mousePos = input_->getMousePos();	//Guardamos la posici�n del rat�n
	//Comprobamos si se ha hecho click
	if (input_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		SDL_Point mouse = { (int)mousePos.getX(), (int)mousePos.getY() };
		//Las ponemos todas a false por si no se ha pulsado ninguno de los objetos
		for (int i = 0; i < shipObjects_.size(); i++) {
			shipObjects_[i].click = false;
		}

		//Si se ha clickado alguna, se pone en true
		if (SDL_PointInRect(&mouse, &shipObjects_[Stash].object->getDestiny())) shipObjects_[Stash].click = true;
		else if (SDL_PointInRect(&mouse, &shipObjects_[Door].object->getDestiny())) shipObjects_[Door].click = true;
		else if (SDL_PointInRect(&mouse, &shipObjects_[Wheel].object->getDestiny())) shipObjects_[Wheel].click = true;
		else if (SDL_PointInRect(&mouse, &shipObjects_[Exit].object->getDestiny())) shipObjects_[Exit].click = true;
		else
		{
			for (int i = 0; i < shipObjects_.size(); i++) {
				shipObjects_[i].click = false;
			}
		}
	}

	//Colisi�n con los objetos del barco

	for (int i = 0; i < shipObjects_.size(); i++) {
		if (RectRect(player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
			shipObjects_[i].object->getPosX() + shipObjects_[i].object->getScaleX() / 2, shipObjects_[i].object->getPosY() + 
			shipObjects_[i].object->getScaleY() / 2, shipObjects_[i].object->getScaleX(), shipObjects_[i].object->getScaleY())) {
			player_->stop();
			player_->setPos(player_->getPreviousPos());

			//Si el objeto en concreto hab�a sido pulsado
			if (shipObjects_[i].click) {
				shipObjects_[i].click = false;
				shipObjects_[i].object->onCollider();
			}
		}
	}

	//Colisi�n con los NPCs desbloqueados
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