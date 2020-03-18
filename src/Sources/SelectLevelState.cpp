#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "Button.h"

void SelectLevelState::goToIsland0(Application* app) {
	app->getStateMachine()->changeState(new CaribbeanIslandState(app));
}
void SelectLevelState::goToIsland1(Application* app) {
	app->getStateMachine()->changeState(new SpookyIslandState(app));

}
void SelectLevelState::goToIsland2(Application* app) {
	app->getStateMachine()->changeState(new VolcanicIslandState(app));
}

SelectLevelState::SelectLevelState(Application* app, int islandUnlocked ) 
	:GameState(app), islandsUnlocked_(islandUnlocked) {
	initState();
}

void SelectLevelState::initState() {
	
	Button* newIslandButton;

	//Bucle que genera los botones para pasar a las distintas islas según el numero que hayan sido desbloqueadas
	for (int i = 0; i < functions_.size() && i < islandsUnlocked_; i++) {
		newIslandButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
			buttonPositions_[i], Vector2D(200, 200), functions_[i]);
		addRenderUpdateLists(newIslandButton);
	}	
}

