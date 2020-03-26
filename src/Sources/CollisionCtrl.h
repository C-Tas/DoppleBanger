#pragma once
#include "Player.h"
#include "NPC.h"
#include "Obstacle.h"
#include "Enemy.h"
//#include "Chest.h"
//#include "Bullet.h"
#include "Trigger.h"
//#include "ShipObject.h"
#include <list>
#include <vector>


class CollisionCtrl {
private:
	enum ShipObjectsNames : int {
		Stash = 0,
		Door,
		Wheel,
		Exit
	};

	struct ShipObjectsInfo {
		ShipObjectsNames id;
		//ShipObject* object;
		bool click = false;
	};
	
	Player* player_ = nullptr;

	//Islas
	NPC* npc_ = nullptr;	//El NPC no necesita ser una lista, hay como mucho uno por zona
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;
	//list<Chest*> chests_;
	//list<Bullet*> playerBullets_;
	//list<Bullet*> enemyBullets_;
	list<Trigger*> triggers_;

	//Barco
	list<NPC*> npcs_;	//Para los NPCs desbloqueados del barco
	vector<ShipObjectsInfo> shipObjects_;

	static unique_ptr<CollisionCtrl> instance_;

public:
	CollisionCtrl() {};	//Todos los elementos de colisión deben pasarse con los setters
	~CollisionCtrl() {};

	///<summary>Instanciamos el CollisionCtrl o creamos uno</summary>
	static CollisionCtrl* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new CollisionCtrl());
		}
		return instance_.get();
	}

	///<summary>Comprueba las colisiones</summary>
	void islandCollisions();
	void shipCollisions();

#pragma region Removes
	///<summary>Quita las colisiones con el NPC (si el NPC se desbloquea y deja de aparecer en la isla)</summary>
	void removeNPC() { npc_ = nullptr; };
	///<summary>Quita un enemigo de la lista</summary>
	void removeEnemy(Enemy* enem) { enemies_.remove(enem); };
	///<summary>Quita una bala de la lista</summary>
	//void removePlayerBullet(Bullet* bullet) { playerBullets_.remove(bullet); };
	///<summary>Quita una bala de la lista</summary>
	//void removeEnemyBullet(Bullet* bullet) { enemyBullets_.remove(bullet); };
	///<summary>Quita un trigger de la lista</summary>
	void removeTrigger(Trigger* trigger) { triggers_.remove(trigger); };
#pragma endregion

#pragma region Setters
	///<summary>Setea el player</summary>
	void setPlayer(Player* player) { player_ = player; };
	///<summary>Setea el NPC de la zona</summary>
	void setNPC(NPC* npc) { npc_ = npc; };
	///<summary>Vacía la lista de obstáculos para setear una nueva</summary>
	void setObstacles(list<Obstacle*> obstacles) { obstacles_.clear(); obstacles_ = obstacles; };
	///<summary>Vacía la lista de enemigos para setear una nueva</summary>
	void setEnemies(list<Enemy*> enems) { enemies_.clear(); enemies_ = enems; };
	///<summary>Setea nuevos enemigos sin borrar los anteriores (para Magordito)</summary>
	void setMoreEnemies(list<Enemy*> enems) { enemies_.merge(enems); }
	///<summary>Vacía la lista de cofres y setea los nuevos</summary>
	//void setChests(list<Chest*> chests) { chests_.clear(); chests_ = chests; };
	///<summary>Añade una nueva bala a la lista</summary>
	//void setNewPlayerBullet(Bullet* bullet) { playerBullets_.push_back(bullet); }
	///<summary>Añade una nueva bala a la lista</summary>
	//void setNewEnemyBullet(Bullet* bullet) { enemyBullets_.push_back(bullet); }
	///<summary>Añade un nuevo trigger</summary>
	void setTriggers(Trigger* trigger) { triggers_.push_back(trigger); };
	///<summary>Guarda el alijo</summary>
	//void setStash(ShipObject* stash) { shipObjects_[Stash].object = stash; };
	///<summary>Guarda la puerta</summary>
	//void setDoor(ShipObject* door) { shipObjects_[Door].object = door; };
	///<summary>Guarda el timón</summary>
	//void setWheel(ShipObject* wheel) { shipObjects_[Wheel].object = wheel; };
	///<summary>Guarda el timón</summary>
	//void setExit(ShipObject* exit) { shipObjects_[Exit].object = exit; };
	///<summary>Indica si el alijo ha sido pulsado o no</summary>
	void setStashClick(bool click) { shipObjects_[Stash].click = click; };
	///<summary>Indica si la puerta ha sido pulsada o no</summary>
	void setDoorClick(bool click) { shipObjects_[Door].click = click; };
	///<summary>Indica si el timón ha sido pulsado o no</summary>
	void setWheelClick(bool click) { shipObjects_[Wheel].click = click; };
	///<summary>Indica si la salida ha sido pulsado o no</summary>
	void setExitClick(bool click) { shipObjects_[Exit].click = click; };
#pragma endregion
};