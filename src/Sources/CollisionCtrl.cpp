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
	for (auto it = chestsToErase_.begin(); it != chestsToErase_.end(); ++it) {
		chests_.remove(*it);
	}
	chestsToErase_.clear();
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
		
		//Con balas del jugador
		for (auto bullet : playerBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//M�todo para destruir bala
				removePlayerBullet(bullet);
				bullet->onCollider();
			}
		}

		//Con balas de los enemigos
		for (auto bullet : enemyBullets_) {
			if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
				(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
				//M�todo para destruir bala
				removeEnemyBullet(bullet);
				bullet->onCollider();
			}
		}
	}

	for (auto ob : obstacleWithRotation_) {
		if (Collisions::collidesWithRotation(player_->getColliderPos(), player_->getColliderScale().getX(), player_->getColliderScale().getY(),
			player_->getCollisionRot(), (ob)->getColliderPos(), (ob)->getColliderScale().getX(), (ob)->getColliderScale().getY(), ob->getCollisionRot())) {
			player_->stop();
			(ob)->onCollider();
			player_->setPos(player_->getPreviousPos());
		}
	}

	//Colisi�n enemigo con jugador o con balas del jugador
	for (auto enem : enemies_) {
		if (Collisions::collidesWithRotation(enem->getPos(), enem->getScaleX(), enem->getScaleY(), enem->getCollisionRot(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY(), player_->getCollisionRot())) {
			enem->onCollider();
			//Cuando el jugador colisiona con el enemigo recibe da�o
			//Falta a�adir el m�todo correspondiente
		}
		if (enem != nullptr) {
			for (auto bullet : playerBullets_) {
				if (Collisions::collidesWithRotation(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(), bullet->getCollisionRot(),
					enem->getPos(), enem->getScaleX(), enem->getScaleY(), enem->getCollisionRot())) {
					enem->receiveDamage(bullet->getDamage());
					if (bullet->getRicochet()) {	//Cuando esté rebotando
						bullet->searchEnemy(enemies_, enem);
					}
					else if (!bullet->getPerforate()) {	//Cuando no esté perforando
						removePlayerBullet(bullet);
						bullet->onCollider();
					}
				}
			}
		}
	}

	//Colisi�n bala del enemigo con jugador
	for (auto bullet : enemyBullets_) {
		if (Collisions::collides(bullet->getPos(), bullet->getScaleX(), bullet->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			// si la bala puede hacer da�o al jugador
			if (bullet->doDamage()) {
				player_->receiveDamage(bullet->getDamage());//el jugador recibe da�o
				bullet->collisionDetected();//restamos uno al numero de golpes que puede realizar la bala
				bullet->setDoDamage(false);// ya no puede atacar al player hasta el siguiente golpe
			}
			//si ya no le quedan colisiones a la bala la borramos
			if (bullet->numCollisions() == 0 ){
				removeEnemyBullet(bullet);
				bullet->onCollider();
			}
		}
	}

	//Colisi�n NPC con jugador -- Como mucho habrá uno por zona
	if (npcs_.size() > 0) {
		if (Collisions::collides(npcs_[0].object->getPos(), npcs_[0].object->getScaleX() * 1.1, npcs_[0].object->getScaleY() * 1.1,
			player_->getPos(), player_->getScaleX() * 1.1, player_->getScaleY() * 1.1)) {
			if (Collisions::collides(npcs_[0].object->getPos(), npcs_[0].object->getScaleX(), npcs_[0].object->getScaleY(),
				player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
				player_->stop();
				player_->setPos(player_->getPreviousPos());
			}

			onShip = false;
			npcCollision.object = npcs_[0].object;
			switch (npcs_[0].id) {
			case NPCsNames::Chef:
				npcCollision.id = NPCsNames::Chef;
				break;
			case NPCsNames::Morty:
				npcCollision.id = NPCsNames::Morty;
				break;
			case NPCsNames::Parrot:
				npcCollision.id = NPCsNames::Parrot;
				break;
			case NPCsNames::Skeleton:
				npcCollision.id = NPCsNames::Skeleton;
				break;
			case NPCsNames::Cartographer:
				npcCollision.id = NPCsNames::Cartographer;
				break;
			}
		}
	}

	//Colisi�n cofres con jugador
	for (auto chest : chests_) {
		if (Collisions::collides(chest->getPos(), chest->getScaleX(), chest->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			chest->onCollider();
			removeChest(chest);	//Para que no pueda volver a abrirse el mismo cofre
		}
	}

	//Jugador con triggers
	/*for (auto trigg : triggers_) {
		if (player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
			trigg->getPosX() + trigg->getScaleX() / 2, trigg->getPosY() + trigg->getScaleY() / 2, trigg->getScaleX(), trigg->getScaleY()) {
			trigg->onOverlap();
		}
	}*/

	//Colisi�n colliders con jugador
	for (auto collider : colliders_) {
		if (Collisions::collides(collider->getPos(), collider->getScaleX(), collider->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			collider->onCollider();
		}
	}
}

void CollisionCtrl::shipCollisions() {	//Est� comentado porque falta a�adir la clase ShipObject
	Vector2D mousePos = input_->getRelativeMousePos();	//Guardamos la posici�n del rat�n
	//Comprobamos si se ha hecho click
	if (input_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		SDL_Point mouse = { (int)mousePos.getX(), (int)mousePos.getY() };
		//Las ponemos todas a false por si no se ha pulsado ninguno de los objetos
		for (int i = 0; i < shipObjects_.size(); i++) {
			shipObjects_[i].click = false;
		}

		//Si se ha clickado alguna, se pone en true
		if (SDL_PointInRect(&mouse, &shipObjects_[(int)ShipObjectsNames::Stash].object->getDestiny())) shipObjects_[(int)ShipObjectsNames::Stash].click = true;
		else if (SDL_PointInRect(&mouse, &shipObjects_[(int)ShipObjectsNames::Door].object->getDestiny())) shipObjects_[(int)ShipObjectsNames::Door].click = true;
		else if (SDL_PointInRect(&mouse, &shipObjects_[(int)ShipObjectsNames::Wheel].object->getDestiny())) shipObjects_[(int)ShipObjectsNames::Wheel].click = true;
		else if (SDL_PointInRect(&mouse, &shipObjects_[(int)ShipObjectsNames::Exit].object->getDestiny())) shipObjects_[(int)ShipObjectsNames::Exit].click = true;
		else
		{
			for (int i = 0; i < shipObjects_.size(); i++) {
				shipObjects_[i].click = false;
			}
		}
	}

	//Colisi�n con los objetos del barco
	for (int i = 0; i < shipObjects_.size(); i++) {
		if (RectRect(player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getColliderScale().getX(), player_->getScaleY() / 10,
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
		if (Collisions::collides(npc.object->getPos(), npc.object->getScaleX() * 1.1, npc.object->getScaleY() * 1.1,
			player_->getPos(), player_->getScaleX() * 1.1, player_->getScaleY() * 1.1)) {

			//RectRect(player_->getPosX() + player_->getScaleX() / 2, player_->getPosY() + player_->getScaleY() / 2, player_->getScaleX(), player_->getScaleY() / 10,
			//npc.object->getPosX() + npc.object->getScaleX() / 2, npc.object->getPosY() + npc.object->getScaleY() / 2, npc.object->getScaleX() * 1.1, npc.object->getScaleY() * 0.11)) {

			if (Collisions::collides(npc.object->getColliderPos(), npc.object->getColliderScale().getX(), npc.object->getColliderScale().getY(),
				player_->getColliderPos(), player_->getColliderScale().getX(), player_->getColliderScale().getY())) {
					player_->stop();
					player_->setPos(player_->getPreviousPos());
			}

			onShip = true;
			npcCollision.object = npc.object;

	        switch (npc.id) {
			case NPCsNames::ElderMan:
				npcCollision.id = NPCsNames::ElderMan;
				break;
			case NPCsNames::Merchant:
				npcCollision.id = NPCsNames::Merchant;
				break;
	        case NPCsNames::Chef:
				npcCollision.id = NPCsNames::Chef;
	            break;
	        case NPCsNames::Morty:
				npcCollision.id = NPCsNames::Morty;
	            break;
			case NPCsNames::Parrot:
				npcCollision.id = NPCsNames::Parrot;
				break;
			case NPCsNames::Skeleton:
				npcCollision.id = NPCsNames::Skeleton;
				break;
			case NPCsNames::Cartographer:
				npcCollision.id = NPCsNames::Cartographer;
				break;
			}
		}
	}

	///Colision con las paredes del barco
	for (auto ob : obstacles_) {
		//Con jugador
		if (Collisions::collides(player_->getColliderPos(), player_->getColliderScale().getX(), player_->getColliderScale().getY(),
			(ob)->getPos(), (ob)->getScaleX(), (ob)->getScaleY())) {
			player_->stop();
			(ob)->onCollider();
			player_->setPos(player_->getPreviousPos());
		}
	}
}

list<Enemy*> CollisionCtrl::getEnemiesInArea(Point2D center, int radius)
{
	list<Enemy*> enemiesWithin;
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
	{
		SDL_Rect coll = (*it)->getCollider();
		if (RectBall(coll.x + coll.w / 2, coll.y + coll.h / 2, coll.w, coll.h, center.getX(), center.getY(), radius)) {
			enemiesWithin.push_back((*it));
		}
	}
	return enemiesWithin;
}

void CollisionCtrl::drawTextBox() {
	//Generamos un textbox si se ha dado alguna colisión con un NPC
	switch (npcCollision.id) {
	case NPCsNames::ElderMan:
		npcCollision.object->getTextBox()->dialogElderMan(-1);
		break;
	case NPCsNames::Merchant:
		npcCollision.object->getTextBox()->dialogMerchant();
		break;
	case NPCsNames::Chef:
		npcCollision.object->getTextBox()->dialogChef(onShip, numConversation_);
		break;
	case NPCsNames::Morty:
		npcCollision.object->getTextBox()->dialogMorty(onShip, numConversation_);
		break;
	case NPCsNames::Parrot:
		npcCollision.object->getTextBox()->dialogParrot();
		break;
	case NPCsNames::Skeleton:
		npcCollision.object->getTextBox()->dialogSkeleton(onShip);
	case NPCsNames::Cartographer:
		npcCollision.object->getTextBox()->dialogCartographer(onShip);
	default:
		numConversation_ = 0;
	}
	npcCollision.id = NPCsNames::Nobody;
	npcCollision.object = nullptr;
}