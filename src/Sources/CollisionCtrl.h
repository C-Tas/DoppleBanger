#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"
#include <list>

class CollisionCtrl {
private:
	Player* player_ = nullptr;
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;
public:
	CollisionCtrl(Player* player, list<Obstacle*> obstacles, list<Enemy*> enemies) :
		player_(player), obstacles_(obstacles), enemies_(enemies) {};
	~CollisionCtrl() {};

	///<summary>Comprueba las colisiones</summary>
	void update();

#pragma region Setters
	///<summary>Setea el player</summary>
	void setPlayer(Player* player) { player_ = player; };
	///<summary>Vacía la lista de obstáculos para setear una nueva</summary>
	void setObstacles(list<Obstacle*> obstacles) { obstacles_.clear(); obstacles_ = obstacles; };
	///<summary>Vacía la lista de enemigos para setear una nueva</summary>
	void setEnemies(list<Enemy*> enems) { enemies_.clear(); enemies_ = enems; };
#pragma endregion
};