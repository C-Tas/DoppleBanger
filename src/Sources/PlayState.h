#pragma once
#include "GameState.h"
#include "CollisionCtrl.h"
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"
#include <list>

class PlayState : public GameState
{
private:
	CollisionCtrl* collisionCtrl_ = nullptr;
	Player* player_ = nullptr;
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;

public:
	///<summary>Constructora PlayState</summary>
	PlayState(Application* app = nullptr) : GameState(app) { initPlayState(); };
	///<summary>Destructora</summary>
	virtual ~PlayState() { delete collisionCtrl_; };

	///<summary>Inicializa los elementos del PlayState</summary>
	void initPlayState();
	///<summary>Llama al update del CollisionManager</summary>
	virtual void update() { collisionCtrl_->islandCollisions(); GameState::update(); };
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
};

