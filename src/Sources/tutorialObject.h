#pragma once
#include "Collider.h"
#include "GameState.h"
#include "tutorialState.h"
#include "Enemy.h"

class tutorialObject :
	public Enemy
{
public:
	tutorialObject(Application* app, Vector2D pos, Vector2D scale, Texture* tex, int id) :Enemy(app, pos, scale), id_(id) {
		initObject(); 
		setTexture(tex);
	};
	~tutorialObject() {};

	virtual bool update();
	virtual void initialStats();
	//inicializa los puntos de hazaña y el oro que da esta entidad
	virtual void initRewards() { achievementPoints_ = 10; };
	virtual void onCollider();
	virtual void receiveDamage(int damage);
private:
	int id_ = -1;
	virtual void initObject();
	virtual void updateCooldowns() {};
};

