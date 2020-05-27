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

void EndState::draw() const {
	rain_[currRain_]->render({ 0,0, app_->getWindowWidth(), app_->getWindowHeight() });

	GameState::draw();
}

void EndState::update() {
	if (SDL_GetTicks() - lastRainTime_ > rainTime_) {
		lastRainTime_ = SDL_GetTicks();
		currRain_++;
		
		if (currRain_ == rain_.size()) currRain_ = 0;
	}

	GameState::update();
}

void EndState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);
	gm_->setOnShip(true);

	rain_.push_back(app_->getTextureManager()->getTexture(Resources::TextureId::Rain1));
	rain_.push_back(app_->getTextureManager()->getTexture(Resources::TextureId::Rain2));
	rain_.push_back(app_->getTextureManager()->getTexture(Resources::TextureId::Rain3));
	rain_.push_back(app_->getTextureManager()->getTexture(Resources::TextureId::Rain4));

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
	
	//Metemos los NPCs pero solo los que estén actualmente desbloqueados
	//El viejo y el mercader están desde el principio
	NPC* elderman;
	elderman = new NPC(app_, app_->getTextureManager()->getTexture(Resources::VenancioFuneral), Vector2D(W_WIN * 2 / 5, H_WIN * 3 / 5), Vector2D(W_ELDERMAN, H_ELDERMAN), 7);
	addRenderUpdateLists(elderman);

	NPC* merchant;
	merchant = new NPC(app_, app_->getTextureManager()->getTexture(Resources::MerchantFuneral), Vector2D(W_WIN / 3, H_WIN / 3), Vector2D(W_MERCHANT, H_MERCHANT), 8);
	addRenderUpdateLists(merchant);

	//Comprobamos si los NPCs restantes están desbloqueados
	if (gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		NPC* chef;
		chef = new NPC(app_, app_->getTextureManager()->getTexture(Resources::CookerFuneral), Vector2D(W_WIN * 9 / 16, H_WIN / 2), Vector2D(W_CHEF, H_CHEF), 2);
		addRenderUpdateLists(chef);
	}

	if (gm_->isThatMissionPass(missions::papelesSiniestros)) {
		NPC* morty;
		morty = new NPC(app_, app_->getTextureManager()->getTexture(Resources::MortyFuneral), Vector2D(W_WIN / 3, H_WIN * 6 / 11), Vector2D(W_MORTY, H_MORTY), 3);
		addRenderUpdateLists(morty);
	}

		NPC* parrot;
		parrot = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Parrot), Vector2D(W_WIN  * 11 / 20, (double)H_WIN * 3 / 4), Vector2D(W_PARROT, H_PARROT), 4);
		addRenderUpdateLists(parrot);
	if (gm_->isThatMissionPass(missions::masValePajaroEnMano)) {
	}

	if (gm_->isThatMissionPass(missions::laboon)) {
		NPC* skeleton;
		skeleton = new NPC(app_, app_->getTextureManager()->getTexture(Resources::SkeletonMusician), Vector2D(W_WIN * 6 / 13, H_WIN * 8 / 17), Vector2D(W_SKELETON, H_SKELETON), 5);
		addRenderUpdateLists(skeleton);
	}

	if (gm_->isThatMissionPass(missions::arlongPark)) {
		NPC* cartographer;
		cartographer = new NPC(app_, app_->getTextureManager()->getTexture(Resources::CartographerFuneral), Vector2D((double)W_WIN * 4 / 11, H_WIN / 2), Vector2D(W_CARTOGRAPHER, H_CARTOGRAPHER), 6);
		addRenderUpdateLists(cartographer);
	}
}