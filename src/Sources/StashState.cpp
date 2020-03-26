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

void StashState::callbackSelectObject(GameState* state, InventoryButton* button)
{
	dynamic_cast<StashState*>(state)->selectObject(button);
}

void StashState::draw() const
{
	//Dibujamos el fondo (de momento es el provisional)
	//background_->render({ 0, 0, app_->getWindowWidth(), app_->getWindowHeight()});
	
	//Dibujamos todos los botones
	GameState::draw();

	//Dibujamos los objetos visibles en el inventario y en el alijo
	//Primer vector determina donde se posiciona el primer objeto y el segundo la distancia en x e y entre objetos
	drawList(stash_.objects_, stash_.listPos_, STASH_VISIBLE_ELEMENTS, Vector2D(app_->getWindowWidth() / 9, app_->getWindowHeight() / 3), Vector2D((app_->getWindowWidth() / 8), (app_->getWindowHeight() / 10)), 2);
	drawList(inventory_.objects_, inventory_.listPos_, INVENTORY_VISIBLE_ELEMENTS, Vector2D(app_->getWindowWidth() - app_->getWindowHeight() / 4, app_->getWindowHeight() / 3), Vector2D((app_->getWindowWidth() / 8), (app_->getWindowHeight() / 10)), 2);
}

void StashState::update()
{
	//Update de todos los botones
	GameState::update();

	//update de los objetos que hay en pantalla
}

void StashState::initState() {
#ifdef _DEBUG
	cout << "InitState de StashState" << endl;
#endif // _DEBUG

	//La textura es temporal porque de momento no está la interfaz de este estado
	background_ = app_->getTextureManager()->getTexture(Resources::TextureId::InventaryMenu);

	//Botón de avanzar la página del inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1300, 150), Vector2D(50, 50), callbackAdvanceInventoryPage));
	//Botón de volver a la página anterior del inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1100, 150), Vector2D(50, 50), callbackPreviousInventoryPage));
	
	//Botón de avanzar la página del alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(300, 150), Vector2D(50, 50), callbackAdvanceStashPage));
	//Botón de volver a la página anterior del alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(100, 150), Vector2D(50, 50), callbackPreviousStashPage));

	//Botón de volver al estado anterior
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1500, 50), Vector2D(50, 50), backToPrevious));

	GameManager* gm = GameManager::instance();

	stash_.objects_ = gm->getStash();
	inventory_.objects_ = gm->getInventory();

	//Creo aquí objetos para comprobar funcionalidad
#ifdef _DEBUG
	cout << "Creando Objetos de prueba en el initState" << endl;

	Gun* gun = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon),"pistolaDefault", "uwu",0,0,0,Shotgun_);
	Gun* gun1 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu", 0, 0, 0, Shotgun_);
	Gun* gun2 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu", 0, 0, 0, Shotgun_);
	
	InventoryButton* b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun, callbackSelectObject);
	auto it = stash_.objects_->insert(stash_.objects_->end(),b);
	b->setIterator(it);
	b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun1, callbackSelectObject);
	it = stash_.objects_->insert(stash_.objects_->end(), b);
	b->setIterator(it);
	b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun2, callbackSelectObject);
	it = stash_.objects_->insert(stash_.objects_->end(), b);
	b->setIterator(it);

#endif // _DEBUG

	inventory_.listPos_ = inventory_.objects_->begin();
	stash_.listPos_ = stash_.objects_->begin();
}

void StashState::advanceInventoryPage() {
	//Si el primer elemento de la siguiente página no se pasa del número de objetos de la lista, avanzamos
	if (((inventory_.page_+1) * INVENTORY_VISIBLE_ELEMENTS) <= inventory_.objects_->size()) {
		inventory_.page_++;
		advance(inventory_.listPos_, INVENTORY_VISIBLE_ELEMENTS);
	}
}

void StashState::previousInventoryPage()
{	//Si el primer elemento de la página anterior del la lista no es negativo(no existe), retrocedemos
	if (((inventory_.page_ - 1) * INVENTORY_VISIBLE_ELEMENTS) >=0) {
		inventory_.page_--;
		advance(inventory_.listPos_, -INVENTORY_VISIBLE_ELEMENTS);
	}
}

void StashState::advanceStashPage()
{	//Si el primer elemento de la siguiente página no se pasa del número de objetos de la lista, avanzamos
	if ((stash_.page_ + 1) * STASH_VISIBLE_ELEMENTS <= stash_.objects_->size()) {
		stash_.page_++;
		advance(stash_.listPos_, STASH_VISIBLE_ELEMENTS);
	}
}

void StashState::previousStashPage()
{	//Si el primer elemento de la página anterior del la lista no es negativo(no existe), retrocedemos
	if ((stash_.page_ - 1) * STASH_VISIBLE_ELEMENTS >= 0) {
		stash_.page_--;
		advance(stash_.listPos_, -STASH_VISIBLE_ELEMENTS);
	}
}

void StashState::selectObject(InventoryButton* button)
{
	selected_ = button;
}

void StashState::drawList(list<InventoryButton*>* list_, list<InventoryButton*>::iterator it, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween, int elementsPerRow)const
{
	//Si existe la lista y no está vacía la dibujamos
	if (list_!= nullptr && !list_->empty()) {
		int i = 0;
		auto aux = it;
		while (aux != list_->end() && i < elemsPerPage / elementsPerRow) {//filas
			int j = 0;
			while (aux != list_->end() && j < elementsPerRow) {//columnas
				(*aux)->setPos({ iniElemPos.getX() + distanceBetween.getX() * j, iniElemPos.getY() + distanceBetween.getY() * i });
				(*aux)->draw();
				++aux;
				j++;
			}
			i++;
		}
	}
}


