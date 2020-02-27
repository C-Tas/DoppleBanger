#pragma once
#include <list>
#include "GameObject.h"
#include "Application.h"

using namespace std;
using uint = unsigned int;

class GameState
{
protected:
	list<GameObject*> gameObjects_;
	Application* app_;
public:
	GameState(Application* app) : app_(app) {};
	~GameState();
	virtual void draw() const;
	virtual void update();
};

