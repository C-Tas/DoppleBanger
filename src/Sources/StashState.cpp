#include "StashState.h"
#include "GameManager.h"
void StashState::backToPrevious(Application* app) {
	app->getStateMachine()->popState();
}

void StashState::callbackAdvanceInventoryPage(GameState* state) {
	dynamic_cast<StashState*>(state)->advanceInventoryPage();
}

void StashState::callbackAdvanceStashPage(GameState* state) {
	dynamic_cast<StashState*>(state)->advanceStashPage();
}

void StashState::callbackPreviousInventoryPage(GameState* state) {
	dynamic_cast<StashState*>(state)->previousInventoryPage();
}

void StashState::callbackPreviousStashPage(GameState* state) {
	dynamic_cast<StashState*>(state)->previousStashPage();
}

void StashState::initState() {
	//La textura es temporal porque de momento no está la interfaz de este estado
	background_ = app_->getTextureManager()->getTexture(Resources::TextureId::InventaryMenu);

	//Botón de avanzar la página del inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(300, 150), Vector2D(50, 50), callbackAdvanceInventoryPage));
	//Botón de volver a la página anterior del inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(100, 150), Vector2D(50, 50), callbackPreviousInventoryPage));
	
	//Botón de avanzar la página del alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1300, 150), Vector2D(50, 50), callbackAdvanceStashPage));
	//Botón de volver a la página anterior del alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1100, 150), Vector2D(50, 50), callbackPreviousStashPage));

	//Botón de volver al estado anterior
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1000, 100), Vector2D(50, 50), backToPrevious));

	GameManager* gm = GameManager::instance();

	stash_ = gm->getStash();
	inventory_ = gm->getInventory();

	inventoryPos_ = inventory_.begin();
	stashPos_ = stash_.begin();
	
}

void StashState::advanceInventoryPage() {
#ifdef _DEBUG
	cout << "Vamos a la pagina siguiente del inventario" << endl;
#endif // _DEBUG

	if (((inventoryPage_+1) * INVENTORY_VISIBLE_ELEMENTS) <= inventory_.size()) {
		inventoryPage_++;
		advance(inventoryPos_, INVENTORY_VISIBLE_ELEMENTS);
	}
}

void StashState::previousInventoryPage()
{
#ifdef _DEBUG
	cout << "Volvemos a la pagina anterior del inventario" << endl;
#endif // _DEBUG


	if (((inventoryPage_ - 1) * INVENTORY_VISIBLE_ELEMENTS) >=0) {
		inventoryPage_--;
		advance(inventoryPos_, -INVENTORY_VISIBLE_ELEMENTS);
	}
}

void StashState::advanceStashPage()
{
#ifdef _DEBUG
	cout << "Vamos a la pagina siguiente del alijo" << endl;
#endif // _DEBUG
	if ((stashPage_ + 1) * STASH_VISIBLE_ELEMENTS <= stash_.size()) {
		stashPage_++;
		advance(stashPos_, STASH_VISIBLE_ELEMENTS);
	}
}

void StashState::previousStashPage()
{
#ifdef _DEBUG
	cout << "Vamos a la pagina anterior del alijo" << endl;
#endif // _DEBUG
	if ((stashPage_ - 1) * STASH_VISIBLE_ELEMENTS >= 0) {
		stashPage_--;
		advance(stashPos_, -STASH_VISIBLE_ELEMENTS);
	}
}
