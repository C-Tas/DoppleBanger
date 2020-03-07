#include "SelectLevelState.h"
#include "Button.h"

void goToIsland0(Application* app) {
	app->getStateMachine()->changeState(/**/nullptr);
}
void goToIsland1(Application* app) {
	app->getStateMachine()->changeState(/**/nullptr);

}
void goToIsland2(Application* app) {
	app->getStateMachine()->changeState(/**/nullptr);

}

SelectLevelState::SelectLevelState(Application* app, int islandUnlocked ) 
	:GameState(app), islandsUnlocked_(islandUnlocked) {
	initState();
}
void SelectLevelState::initState() {
	
	Button* island0 = new Button (app_->getTextureManager()->getTexture(Resources::TextureId::Timon), 
		Vector2D(100, 400), Vector2D(400, 400), goToIsland0);

	addRenderList(island0);
	addUpdateList(island0);

	Button* island1;
	switch (islandsUnlocked_)
	{
	case 2:
		island1 = new Button(app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			Vector2D(100, 400), Vector2D(400, 400), goToIsland1);
		
		break;
	case 3:
		island1 = new Button(app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			Vector2D(800, 400), Vector2D(400, 400), goToIsland1);
		Button* island2 = new Button(app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			Vector2D(1300, 400), Vector2D(400, 400), goToIsland2);
		break;
	}
		
}
