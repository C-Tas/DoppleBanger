#pragma once
#include "GameState.h"
#include "Enemy.h"
#include "Player.h"

class PlayState :
	public GameState
{
protected:
	///<summary>Lista con todos los enemigos</summary>
	list<Enemy*> enemies_;
	Player* player_;

public:
	///<summary>Constructora PlayState</summary>
	PlayState(Application* app=nullptr) :GameState(app) {};
	///<summary>Destructora</summary>
	virtual ~PlayState() {};
	///<summary>A mayores comprueba las acciones del jugador</summary>
	virtual void update();

	///<summary>Ir a pauseState (push)</summary>
	static void goToPauseState(Application* app);
	///<summary>Ir a SaveGameState (push)</summary>
	static void goToSaveGame(Application* app);
	///<summary>Ir a InventoryState (push)</summary>
	static void goToInventoryState(Application* app);
	///<summary>Ir a SelectLevelState (push)</summary>
	static void goToSelectState(Application* app);
	///<summary>Ir a StashState (push)</summary>
	static void goToStashState(Application* app);
	//falta otro cambio

	///<summary>A�ade un objeto a las listas de objectsToRender_ y gameObjects_</summary>
	void addEnemy(Enemy* obj);
	///<summary>Comprueba las posibles acciones del jugador</summary>
	void checkPlayerActions();
	///<summary>Comprueba si el jugador ha hecho click en algún enemigo, y de ser el caso, devuelve el que se renderiza el último</summary>
	Enemy* checkAttack();
};

