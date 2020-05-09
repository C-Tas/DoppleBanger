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
	virtual void initialStats() {};
	//inicializa los puntos de hazaña y el oro que da esta entidad
	virtual void initRewards(){};
	virtual void onCollider() {
		dynamic_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		auto state = dynamic_cast<tutorialState*>(app_->getCurrState());
		if(state){
			state->currTaskSucess();
		}
	};
private:
	virtual void initObject();
};

