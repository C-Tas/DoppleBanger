#pragma once
#include <list>
#include "Application.h"
using namespace std;
class GameObject;
class GameState
{
protected:
	list<GameObject*> objectList_;
	Application* app_;
public:
	GameState(Application* app = nullptr) :app_(app) {};
	virtual void update();
	virtual void render();
};

