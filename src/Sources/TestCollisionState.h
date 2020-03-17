#pragma once
#include "GameState.h"
#include "TestObjectCollider.h"
#include "Player.h"
#include "Collisions.h"

//GameState creado para testear colisiones
class TestCollisionState : public GameState
{
private:
	TestObjectCollider* objectCollider_ = nullptr;
	TestObjectCollider* objectCollider2_ = nullptr;
	Player* player_ = nullptr;
public:
	TestCollisionState(Application* app) : GameState(app) { initState(); }
	virtual ~TestCollisionState() {}

	void initState();
	void update();
};

