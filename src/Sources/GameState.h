#pragma once
#include <list>
using namespace std;
class GameObject;
class GameState
{
protected:
	list<GameObject*> objectList_;
public:
	virtual void Update();
	virtual void Render();
};

