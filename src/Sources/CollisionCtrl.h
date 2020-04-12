#pragma once
#include "HandleEvents.h"
#include "Player.h"
#include "NPC.h"
#include "Obstacle.h"
#include "Enemy.h"
//#include "Chest.h"
#include "Bullet.h"
#include "Trigger.h"
#include "ShipObject.h"
#include <list>
#include <vector>

class PlayerBullet;
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

	///<summary>Constructora, todos los elementos de colisi�n deben pasarse con los setters</summary>
	CollisionCtrl() { input_ = HandleEvents::instance(); };
	~CollisionCtrl() {};

	///<summary>Instanciamos el CollisionCtrl o creamos uno</summary>
	static CollisionCtrl* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new CollisionCtrl());
		}
		return instance_.get();
	};

	///<summary>Comprueba las colisiones necesarias para las islas</summary>
	void islandCollisions();
	///<summary>Comprueba las colisiones necesarias en el barco</summary>
	void shipCollisions();
	list<Enemy*> getEnemiesInArea(Point2D center, int radius);

#pragma region Remove
	///<summary>Quita las colisiones con el NPC (si el NPC se desbloquea y deja de aparecer en la isla)</summary>
	void removeNPC() { npc_.object = nullptr; };
	///<summary>Quita un enemigo de la lista</summary>
	void removeEnemy(Enemy* enem) { enemiesToErase_.push_back(enem); };
	///<summary>Quita un cofre de la lista (cuando se abre)</summary>
	//void removeChest(Chest* chest) { chestsToErase_.push_back(chest); };
	///<summary>Quita una bala de la lista</summary>
	void removePlayerBullet(PlayerBullet* bullet) { playerBulletsToErase_.push_back(bullet); };
	///<summary>Quita una bala de la lista</summary>
	void removeEnemyBullet(Bullet* bullet) { enemyBulletsToErase_.push_back(bullet); };
	///<summary>Quita un trigger de la lista</summary>
	void removeTrigger(Trigger* trigger) { triggersToErase_.push_back(trigger); };

	///<summary>Vac�a todas las listas (para los cambios de zona)</summary>
	void clearList() {
		//Listas de las islas
		npc_.object = nullptr; obstacles_.clear(); enemies_.clear();
		/*chests_.clear();*/ triggers_.clear(); enemiesToErase_.clear(); /*chestsToErase_.clear();*/
		playerBulletsToErase_.clear(); enemyBulletsToErase_.clear(); triggersToErase_.clear();
		//Listas del barco
		npcs_.clear(); shipObjects_.clear();
	};
#pragma endregion

#pragma region Add
	///<summary>Setea el player</summary>
	void setPlayer(Player* player) { player_ = player; };

	//Islas
	///<summary>Setea el NPC bloqueado de la zona de la isla</summary>
	void setLockNPC(NPCsNames name, NPC* npc) { npc_ = NPCsInfo(name, npc); };
	///<summary>A�ade un nuevo obst�culo</summary>
	void addObstacle(Obstacle* obstacle) { obstacles_.push_back(obstacle); };
	///<summary>A�ade un nuevo enemigo</summary>
	void addEnemy(Enemy* enem) { enemies_.push_back(enem); };
	///<summary>Vac�a la lista de cofres y setea los nuevos</summary>
	//void addChest(Chest* chest) { chests_.push_back(chest); };
	///<summary>A�ade una nueva bala a la lista</summary>
	void addPlayerBullet(PlayerBullet* bullet) { playerBullets_.push_back(bullet); };
	///<summary>A�ade una nueva bala a la lista</summary>
	void addEnemyBullet(Bullet* bullet) { enemyBullets_.push_back(bullet); };
	///<summary>A�ade un nuevo trigger</summary>
	void addTriggers(Trigger* trigger) { triggers_.push_back(trigger); };

	//Barco
	///<summary>Guarda un nuevo NPC desbloqueado a la lista (para el barco)</summary>
	void addUnlockNPC(NPCsNames name, NPC* npc) { npcs_.push_back(NPCsInfo(name, npc)); };
	///<summary>Guarda los elementos del barco</summary>
	void addShipObjects(ShipObject* stash, ShipObject* door, ShipObject* wheel, ShipObject* exit) { 
			shipObjects_.push_back(ShipObjectsInfo(Stash, stash)); shipObjects_.push_back(ShipObjectsInfo(Door, door)); 
			shipObjects_.push_back(ShipObjectsInfo(Wheel, wheel)); shipObjects_.push_back(ShipObjectsInfo(Exit, exit)); };

#pragma endregion

private:	//Private est� abajo porque necesitan enum del p�blico
	struct NPCsInfo {
		NPCsNames id;
		NPC* object = nullptr;

		NPCsInfo() {};
		NPCsInfo(NPCsNames i, NPC* ob) { id = i; object = ob; };
	};

	struct ShipObjectsInfo {
		ShipObjectsNames id;
		ShipObject* object = nullptr;
		bool click = false;

		ShipObjectsInfo() {};
		ShipObjectsInfo(ShipObjectsNames i, ShipObject* ob) { id = i; object = ob; };
	};

	HandleEvents* input_ = nullptr;	//Para controlar si los objetos han sido clickados

	Player* player_ = nullptr;

	//Islas
	NPCsInfo npc_;	//El NPC en la isla no necesita ser una lista, hay como mucho uno por zona
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;
	//list<Chest*> chests_;
	list<PlayerBullet*> playerBullets_;
	list<Bullet*> enemyBullets_;
	list<Trigger*> triggers_;

	list<Enemy*> enemiesToErase_;
	//list<Chest*> chestsToErase_;
	list<PlayerBullet*> playerBulletsToErase_;
	list<Bullet*> enemyBulletsToErase_;
	list<Trigger*> triggersToErase_;

	//Barco
	vector<NPCsInfo> npcs_;
	vector<ShipObjectsInfo> shipObjects_;

	static unique_ptr<CollisionCtrl> instance_;
};