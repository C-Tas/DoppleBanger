#include "VolcanicIslandState.h"
#include "Enemy.h"
#include "Player.h"
#include "ShipState.h"
 
void backShipVolcanic(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}

void VolcanicIslandState::initState()
{
	background_ = app_->getTextureManager()->getTexture(Resources::Caribbean);

	Button* backButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::BackButton),
		Vector2D(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2), Vector2D(300, 300), backShipVolcanic);
	addRenderUpdateLists(backButton);

	Enemy* dragon = new Enemy(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), { 0,0 }, { 120,120 }, { 0,0,0,0 }, {}, { 0,0,144,133 }, 3);
	addRenderUpdateLists(dragon);

	//Siempre se añade el último para que se renderice por encima de los demás objetos
	addRenderUpdateLists(player_);
}

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
#ifdef _DEBUG
	printf("VolcanicIsland");
#endif // _DEBUG
	
}