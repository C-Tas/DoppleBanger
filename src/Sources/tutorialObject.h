#pragma once
#include "Collider.h"
#include "GameState.h"
#include "tutorialState.h"
#include "Enemy.h"

class tutorialObject :
	public Enemy
{
public:
	tutorialObject(Application* app, Vector2D pos, Vector2D scale, Texture* tex) :Enemy(app, pos, scale) { 
		initObject(); 
		setTexture(tex);
	};
	~tutorialObject() {};

	virtual bool update();
	virtual void initialStats();
	//inicializa los puntos de hazaña y el oro que da esta entidad
	virtual void initRewards() {};
	virtual void onCollider();
	virtual void receiveDamage(int damage);
private:
	virtual void initObject();
};

