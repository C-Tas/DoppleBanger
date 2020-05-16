#include "EndState.h"
#include "ShipState.h"
#include "NPC.h"
#include "BeerButton.h"

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

void EndState::chooseOption(Application* app) {
	static_cast<EndState*>(app->getCurrState())->changeButtons();
}
void EndState::backToMainMenu(Application* app)
{
	app->getGameStateMachine()->clearAllStateExceptFirst();
}

void EndState::changeButtons()
{
	if (!choosen) {
		choosen = true;
		removeRenderUpdateLists(mainMenu_);
		removeRenderUpdateLists(ship_);

		//Se cambia la textura por la de escoger opcion
		background_->setTexture(app_->getTextureManager()->getTexture(Resources::GameOver2));
		Vector2D sizeElement = Vector2D(winWidth / 4, winHeight / 8);
		Vector2D posElement = Vector2D((winWidth / 2) - sizeElement.getX() * 1.5, winHeight * 3 / 4);

		//Boton de confirmar
		yes_ = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::YesButton),
			posElement, sizeElement, backToMainMenu);
		yes_->setCurrentState(this);
		addRenderUpdateLists(yes_);

		//Boton de negar
		posElement = Vector2D((winWidth / 2) + sizeElement.getX() / 2, winHeight * 3 / 4);
		no_ = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::NoButton),
			posElement, sizeElement, chooseOption);
		no_->setCurrentState(this);
		addRenderUpdateLists(no_);
	}
	else {
		choosen = false;
		removeRenderUpdateLists(yes_);
		removeRenderUpdateLists(no_);

		//Se cambia la textura por la de fin de juego
		background_->setTexture(app_->getTextureManager()->getTexture(Resources::GameOver1));
		Vector2D sizeElement = Vector2D(winWidth / 4, winHeight / 8);
		Vector2D posElement = Vector2D((winWidth / 2) - sizeElement.getX() * 1.5, winHeight * 3 / 4);

		//Boton del barco
		ship_ = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BackToShipButton),
			posElement, sizeElement, backToShip);
		ship_->setCurrentState(this);
		addRenderUpdateLists(ship_);

		//Boton del menu principal
		posElement = Vector2D((winWidth / 2) + sizeElement.getX() / 2, winHeight * 3 / 4);
		mainMenu_ = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GoMainMenuButton),
			posElement, sizeElement, chooseOption);
		mainMenu_->setCurrentState(this);
		addRenderUpdateLists(mainMenu_);
	}
}

void EndState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);
	gm_->setOnShip(true);
	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::GameOver1));
	addRenderUpdateLists(background_);

	winWidth = app_->getWindowWidth();
	winHeight = app_->getWindowHeight();

	Vector2D sizeElement = Vector2D(winWidth / 4, winHeight / 8);
	Vector2D posElement = Vector2D((winWidth / 2) - sizeElement.getX() * 1.5, winHeight * 3 / 4);
	//Volver al barco
	ship_ = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BackToShipButton),
		posElement, sizeElement, backToShip);
	ship_->setCurrentState(this);
	addRenderUpdateLists(ship_);
	
	//Volver al Menu Principal
	posElement = Vector2D((winWidth / 2) + sizeElement.getX() / 2, winHeight * 3 / 4);
	mainMenu_ = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GoMainMenuButton),
		posElement, sizeElement, chooseOption);
	mainMenu_->setCurrentState(this);
	addRenderUpdateLists(mainMenu_);
	
	//Negros bailando
	sizeElement = Vector2D(winWidth / 4, winHeight / 4);
	posElement = Vector2D((winWidth / 2) - sizeElement.getX() / 2, (winHeight * 2 / 3) - sizeElement.getY());
	NPC* funeral = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Funeral), posElement, sizeElement, 7);
	addRenderUpdateLists(funeral);
}
