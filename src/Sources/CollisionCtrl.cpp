#include "CollisionCtrl.h"
#include "Collisions.h"

void CollisionCtrl::update() {
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
				enem->stop();
				(ob)->onCollider();
			}
		}
	}
	//Colisión enemigo con jugador
	for (auto enem : enemies_) {
		if (Collisions::collides(enem->getPos(), enem->getScaleX(), enem->getScaleY(),
			player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
			enem->onCollider();
			player_->onCollider();
		}
	}
}