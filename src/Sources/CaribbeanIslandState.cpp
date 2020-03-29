#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"

void backShipCaribbean(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void CaribbeanIslandState::initState()
{
	//background_ = app_->getTextureManager()->getTexture(Resources::Caribbean);

	//Button* backButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::BackButton),
	//	Vector2D(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2), Vector2D(300, 300), backShipCaribbean);
	//addRenderUpdateLists(backButton);

	////Siempre se añade el último para que se renderice por encima de los demás objetos
	//addRenderUpdateLists(player_);
}

CaribbeanIslandState::CaribbeanIslandState(Application* app): PlayState(app) {
	initState();

	#ifdef _DEBUG
	printf("CaribbeanIsland");
	#endif
}