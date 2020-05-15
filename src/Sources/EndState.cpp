#include "EndState.h"
#include "ShipState.h"
#include "NPC.h"

void EndState::backToShip(Application* app)
{
	GameManager* gm_ = GameManager::instance();
	//Se pierde el oro
	gm_->setInventoryGold(0);
	//Se resetea el inventario
	gm_->resetInventory();
	//Se limpia la lista de colisiones
	CollisionCtrl::instance()->clearList();
	//Se reinicia la partida en el barco
	app->getGameStateMachine()->changeState(new ShipState(app));
}

void EndState::backToMainMenu(Application* app)
{
	app->getGameStateMachine()->clearAllStateExceptFirst();
}

void EndState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);
	gm_->setOnShip(true);
	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::GameOver));
	addRenderUpdateLists(background_);

	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D sizeElement = Vector2D(winWidth / 4, winHeight / 8);
	Vector2D posElement = Vector2D((winWidth / 2) - sizeElement.getX() * 1.5, winHeight * 3 / 4);
	//Volver al barco
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BackToShipButton), posElement, sizeElement, backToShip, this);
	
	//Volver al Menu Principal
	posElement = Vector2D((winWidth / 2) + sizeElement.getX() / 2, winHeight * 3 / 4);
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GoMainMenuButton), posElement, sizeElement, backToMainMenu, this);
	
	//Negros bailando
	sizeElement = Vector2D(winWidth / 4, winHeight / 4);
	posElement = Vector2D((winWidth / 2) - sizeElement.getX() / 2, (winHeight * 2 / 3) - sizeElement.getY());
	NPC* funeral = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Funeral), posElement, sizeElement, 7);
	addRenderUpdateLists(funeral);
}