#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "Button.h"

void goToIsland0(Application* app) {
	app->getStateMachine()->changeState(new CaribbeanIslandState(app));
}
void goToIsland1(Application* app) {
	app->getStateMachine()->changeState(new SpookyIslandState(app));

}
void goToIsland2(Application* app) {
	app->getStateMachine()->changeState(new VolcanicIslandState(app));

}

SelectLevelState::SelectLevelState(Application* app, int islandUnlocked ) 
	:GameState(app), islandsUnlocked_(islandUnlocked) {
	initState();
}

void SelectLevelState::initState() {
	
	Button* newIslandButton;

	for (int i = 0; i < functions_.size() && i < islandsUnlocked_; i++) {
		newIslandButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			buttonPositions_[i], Vector2D(200, 200), functions_[i]);
		addRenderUpdateLists(newIslandButton);
	}
	
	/*
	Button* island0 = new Button (app_,app_->getTextureManager()->getTexture(Resources::TextureId::Timon), 
		Vector2D(100, 400), Vector2D(400, 400), goToIsland0);

	addRenderUpdateLists(island0);

	Button* island1;
	switch (islandsUnlocked_)
	{
	case 2:
		island1 = new Button(app_,app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			Vector2D(800, 400), Vector2D(400, 400), goToIsland1);
		addRenderUpdateLists(island1);
		
		break;
	case 3:
		island1 = new Button(app_,app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			Vector2D(800, 400), Vector2D(400, 400), goToIsland1);
		addRenderUpdateLists(island1);

		Button* island2 = new Button(app_,app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			Vector2D(1300, 400), Vector2D(400, 400), goToIsland2);
		break;
	}*/
		
}
