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
public:
	enum NPCsNames : int {
		ElderMan = 0,
		Merchant,
		Chef,
		Morty,
		Parrot
	};

	enum ShipObjectsNames : int {
		Stash = 0,
		Door,
		Wheel,
		Exit
	};

	///<summary>Constructora, todos los elementos de colisión deben pasarse con los setters</summary>
	CollisionCtrl() {};
	~CollisionCtrl() {};

	///<summary>Instanciamos el CollisionCtrl o creamos uno</summary>
	static CollisionCtrl* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new CollisionCtrl());
		}
		return instance_.get();
	}

	///<summary>Comprueba las colisiones necesarias para las islas</summary>
	void islandCollisions();
	///<summary>Comprueba las colisiones necesarias en el barco</summary>
	void shipCollisions();

#pragma region Removes
	///<summary>Quita las colisiones con el NPC (si el NPC se desbloquea y deja de aparecer en la isla)</summary>
	void removeNPC() { npc_ = nullptr; };
	///<summary>Quita un enemigo de la lista</summary>
	void removeEnemy(Enemy* enem) { enemies_.remove(enem); };
	///<summary>Quita un cofre de la lista (cuando se abre)</summary>
	//void removeChest(Chest* chest) { chests_.remove(chest); };
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

	//Islas
	///<summary>Setea el NPC bloqueado de la zona de la isla</summary>
	void setLockNPC(NPC* npc) { npc_ = npc; };
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

	//Barco
	///<summary>Guarda un nuevo NPC desbloqueado a la lista (para el barco)</summary>
	void setUnlockNPC(NPCsNames name, NPC* npc) { npcs_[name].object = npc; };
	///<summary>Indica si el objeto del barco ha sido pulsado o no</summary>
	void setShipObjectClick(ShipObjectsNames name, bool click) { shipObjects_[name].click = click; };
	///<summary>Guarda un elemento del barco</summary>
	//void setShipObject(ShipObjectsNames name, ShipObject* ob) { shipObjects_[name].object = ob; };

#pragma endregion

private:	//Private está abajo porque necesitan enum del público
	struct NPCsInfo {
		NPCsNames id;
		NPC* object;
	};

	struct ShipObjectsInfo {
		ShipObjectsNames id;
		//ShipObject* object;
		bool click = false;	//Determina si el objeto ha sido pulsado
	};

	Player* player_ = nullptr;

	//Islas
	NPC* npc_ = nullptr;	//El NPC en la isla no necesita ser una lista, hay como mucho uno por zona
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;
	//list<Chest*> chests_;
	//list<Bullet*> playerBullets_;
	//list<Bullet*> enemyBullets_;
	list<Trigger*> triggers_;

	//Barco
	vector<NPCsInfo> npcs_;	//Para los NPCs desbloqueados del barco (si no está desbloqueado será nullptr)
	vector<ShipObjectsInfo> shipObjects_;

	static unique_ptr<CollisionCtrl> instance_;
};