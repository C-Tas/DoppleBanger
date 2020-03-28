#pragma once
#include "GameState.h"
#include "CollisionCtrl.h"
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"
#include <list>

class PlayState : public GameState
{
protected:
	CollisionCtrl* collisionCtrl_ = nullptr;
	Player* player_ = nullptr;
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;

public:
	///<summary>Constructora PlayState</summary>
	PlayState(Application* app = nullptr) : GameState(app) { initPlayState(); };
	///<summary>Destructora</summary>
	virtual ~PlayState() { };

	///<summary>Inicializa los elementos del PlayState</summary>
	void initPlayState();
	///<summary>Llama al update del CollisionManager</summary>
	virtual void update();
	///<summary>Ir a pauseState (push)</summary>
	static void goToPauseState(Application* app);
	///<summary>Ir a InventoryState (push)</summary>
	static void goToInventoryState(Application* app);
	///<summary>Ir a SelectLevelState (push)</summary>
	static void goToSelectState(Application* app);
	///<summary>Ir a StashState (push)</summary>
	static void goToStashState(Application* app);
	//falta otro cambio

	///<summary>A�ade un objeto a la lista enemies_, objectsToRender y gameObjects_</summary>
	void addEnemy(Enemy* obj);
	///<summary>Quita un objeto a la lista enemies_, objectsToRender y gameObjects_</summary>
	void removeEnemy(Enemy* obj);
	///<summary>Comprueba las posibles acciones del jugador</summary>
	void checkPlayerActions();
	///<summary>Comprueba si el jugador ha hecho click en algún enemigo, y de ser el caso, devuelve el que se renderiza el último</summary>
	Enemy* checkAttack();
	///<summary>Encuentra al enemigo más cercano a una posición</summary>
	Enemy* findClosestEnemy(Point2D pos);
	///<summary>Comprueba colisiones con los enemigos y devuelve el primer enemigo en caso de haber colisión</summary>
	Enemy* collidesWithEnemy(Point2D pos, Vector2D scale);
};

