#pragma once
#include "HandleEvents.h"
#include "Player.h"
#include "NPC.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Chest.h"
#include "Bullet.h"
#include "ShipObject.h"
#include "PlayerBullet.h"
#include <list>
#include <vector>
#include "Barrel.h"

class PlayerBullet;
class CollisionCtrl {
public:
	enum class NPCsNames : int {
		ElderMan = 0,
		Merchant = 1,
		Chef = 2,
		Morty = 3,
		Parrot = 4,
		Skeleton = 5,
		Cartographer = 6,
		Nobody = 7
	};

	enum class ShipObjectsNames : int {
		Stash = 0,
		Door = 1,
		Wheel = 2,
		Exit = 3
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
	//Gestiona las colisiones con los objetos del tutorial
	void tutorialCollision();
	//Gestina las colisiones contra los barriles
	void volcanicCollision();
	///<summary>Para renderizar los textBox en caso de ser necesario</summary>
	void drawTextBox();
	///<summary>Devuelve los objetos en un area</summary>
	list<Enemy*> getEnemiesInArea(Point2D center, int radius);
	//Devuelve los objetos un área
	list<Collider*> getEntitiesInArea(Point2D center, int radius);

#pragma region Remove
	///<summary>Quita las colisiones con el NPC (si el NPC se desbloquea y deja de aparecer en la isla)</summary>
	void removeNPC() { npcs_.clear(); };
	///<summary>Quita un enemigo de la lista</summary>
	void removeEnemy(Enemy* enem) { enemiesToErase_.push_back(enem); };
	///<summary>Quita un cofre de la lista (cuando se abre)</summary>
	void removeChest(Chest* chest) { chestsToErase_.push_back(chest); };
	///<summary>Quita una bala de la lista</summary>
	void removePlayerBullet(PlayerBullet* bullet) { playerBulletsToErase_.push_back(bullet); };
	///<summary>Quita una bala de la lista</summary>
	void removeEnemyBullet(Bullet* bullet) { enemyBulletsToErase_.push_back(bullet); };
	///<summary>Quita un nuevo colliders</summary>
	void removeCollider(Collider* collider) { collidersToErase_.push_back(collider); };
	///<summary>Quita el dummy</summary>
	void removeDummy() { enemies_.clear(); dummy_ = nullptr; };
	//Quita un barril
	void removeBarrel(Barrel* collider) { barrelsToErase_.push_back(collider); }
	///<summary>Vac�a todas las listas (para los cambios de zona)</summary>
	void clearList() {
		//Listas de las islas
		obstacles_.clear(); obstacleWithRotation_.clear(); enemies_.clear();
		chests_.clear(); enemiesToErase_.clear(); chestsToErase_.clear();
		playerBulletsToErase_.clear(); enemyBulletsToErase_.clear();
		endObstacles_.clear();
		//Listas del barco
		npcs_.clear(); shipObjects_.clear(); newNpc = true;
		npcCollision.id = NPCsNames::Nobody;
		npcCollision.object = nullptr;
		collisionWithEndOfZone_ = false;
		//Listas del volcanica
		barrels_.clear();
	};
#pragma endregion

#pragma region Add
	///<summary>Setea el player</summary>
	void setPlayer(Player* player) { player_ = player; };
	//Cambia a la siguiente conversación
	void nextConversation() { numConversation_++; };

	//Islas
	///<summary>A�ade un nuevo obst�culo</summary>
	void addObstacle(Obstacle* obstacle) { obstacles_.push_back(obstacle); };
	///<summary>Añade un obstáculo que tiene rotación</summary>
	void addObstacleWithRotation(Obstacle* obstacle) { obstacleWithRotation_.push_back(obstacle); }
	///<summary>Añade un objeto a los que marcan el final del nivel</summary>
	void addEndObstacle(Obstacle* obstacle) { endObstacles_.push_back(obstacle); };
	///<summary>A�ade un nuevo enemigo</summary>
	void addEnemy(Enemy* enem) { enemies_.push_back(enem); };
	///<summary>Vac�a la lista de cofres y setea los nuevos</summary>
	void addChest(Chest* chest) { chests_.push_back(chest); };
	///<summary>A�ade una nueva bala a la lista</summary>
	void addPlayerBullet(PlayerBullet* bullet) { playerBullets_.push_back(bullet); };
	///<summary>A�ade una nueva bala a la lista</summary>
	void addEnemyBullet(Bullet* bullet) { enemyBullets_.push_back(bullet); };
	///<summary>A�ade un nuevo colliders</summary>
	void addCollider(Collider* collider) { colliders_.push_back(collider); };
	//<summary>Método para saber si está activado el textbox de cambio de zona</summary>
	bool isNextZoneTextBoxActive() { return collisionWithEndOfZone_; }
	//Barco
	///<summary>Guarda un nuevo NPC a la lista</summary>
	void addNPC(NPCsNames name, NPC* npc) { npcs_.push_back(NPCsInfo(name, npc)); };
	///<summary>Guarda los elementos del barco</summary>
	void addShipObjects(ShipObject* stash, ShipObject* door, ShipObject* wheel, ShipObject* exit) { 
			shipObjects_.push_back(ShipObjectsInfo(ShipObjectsNames::Stash, stash)); shipObjects_.push_back(ShipObjectsInfo(ShipObjectsNames::Door, door));
			shipObjects_.push_back(ShipObjectsInfo(ShipObjectsNames::Wheel, wheel)); shipObjects_.push_back(ShipObjectsInfo(ShipObjectsNames::Exit, exit));
	};

	//Tutorial
	void setBottle(Enemy* obj) { bottle_ = obj; }
	void setDummy(Enemy* obj) { dummy_ = obj; }

	//Volcanica
	void addBarrel(Barrel* collider) { barrels_.push_back(collider); }
		
#pragma endregion

private:	//Private est� abajo porque necesitan enum del p�blico
	struct NPCsInfo {
		NPCsNames id = NPCsNames::Nobody;
		NPC* object = nullptr;

		NPCsInfo() {};
		NPCsInfo(NPCsNames i, NPC* ob) { id = i; object = ob; };
	};

	struct ShipObjectsInfo {
		ShipObjectsNames id = ShipObjectsNames::Stash;
		ShipObject* object = nullptr;
		bool click = false;

		ShipObjectsInfo() {};
		ShipObjectsInfo(ShipObjectsNames i, ShipObject* ob) { id = i; object = ob; };
	};

	bool canTalk = true;
	HandleEvents* input_ = nullptr;	//Para controlar si los objetos han sido clickados

	Player* player_ = nullptr;
	vector<NPCsInfo> npcs_;	//Si estamos en el barco habrá varios, si estamos en una isla habrá como mucho uno

	int numConversation_ = 0;

	//Islas
	list<Obstacle*> obstacles_;
	list<Obstacle*> obstacleWithRotation_;
	list<Obstacle*> endObstacles_;
	list<Enemy*> enemies_;
	list<Chest*> chests_;
	list<PlayerBullet*> playerBullets_;
	list<Bullet*> enemyBullets_;
	list<Collider*> colliders_;
	list<Barrel*> barrels_;

	list<Enemy*> enemiesToErase_;
	list<Chest*> chestsToErase_;
	list<PlayerBullet*> playerBulletsToErase_;
	list<Bullet*> enemyBulletsToErase_;
	list<Collider*> collidersToErase_;
	list<Barrel*> barrelsToErase_;

	//Colision con el trigger de fin de zona
	bool collisionWithEndOfZone_ = false;

	//Barco
	bool onShip = true;		//Para mandar si estamos en el barco o en una isla
	bool newNpc = true;	//Para que los NPCs solo se agreguen una vez a la lista de desbloqueados

	//tutorial 
	Enemy* bottle_ = nullptr;
	Enemy* dummy_ = nullptr;

	NPCsInfo npcCollision;
	vector<ShipObjectsInfo> shipObjects_;

	static unique_ptr<CollisionCtrl> instance_;

	//MerchantDialog
	bool isCollidingWithMechant_ = false;
	bool isCollidingWithParrot_ = false;
	int randomPhrase_ = 0;
	const int MAX_MERCHANT_PHRASES = 4;
	const int MAX_PARROT_PHRASES = 4;
};