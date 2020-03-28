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

void StashState::callbackChangeBetweenLists(GameState* state)
{
	dynamic_cast<StashState*>(state)->changeBetweenLists();
}

void StashState::draw() const
{
	//Dibujamos el fondo (de momento es el provisional)
	//background_->render({ 0, 0, app_->getWindowWidth(), app_->getWindowHeight()});
	
	//Dibujamos todos los botones
	GameState::draw();

	//Dibujamos los objetos visibles en el inventario y en el alijo
	//Primer vector determina donde se posiciona el primer objeto y el segundo la distancia en x e y entre objetos
	drawList(stash_.objects_, stash_.page_, STASH_VISIBLE_ELEMENTS, Vector2D(app_->getWindowWidth() / 9, app_->getWindowHeight() / 3), Vector2D((app_->getWindowWidth() / 8), (app_->getWindowHeight() / 10)), 2);
	drawList(inventory_.objects_, inventory_.page_, INVENTORY_VISIBLE_ELEMENTS, Vector2D((app_->getWindowWidth()/2), app_->getWindowHeight() / 3), Vector2D((app_->getWindowWidth() / 8), (app_->getWindowHeight() / 10)), 2);
}

void StashState::update()
{
	//Update de todos los botones
	GameState::update();

	//update de los objetos que hay en pantalla
	auto it = inventory_.objects_->begin();
	advance(it, inventory_.page_ * INVENTORY_VISIBLE_ELEMENTS);
	for (int i = 0; it != inventory_.objects_->end() && i < INVENTORY_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}

	//update de los objetos que hay en pantalla
	it = stash_.objects_->begin();
	advance(it, stash_.page_ * STASH_VISIBLE_ELEMENTS);
	for (int i = 0; it != stash_.objects_->end() && i < STASH_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}
}

void StashState::initState() {

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

	//Botón para cambiar el objeto de una lista a otra
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1500, 300), Vector2D(50, 50), callbackChangeBetweenLists));

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
	it = inventory_.objects_->insert(inventory_.objects_->end(), b);
	b->setIterator(it);



	#endif // _DEBUG
}

void StashState::advanceInventoryPage() {
	//Si el primer elemento de la siguiente página no se pasa del número de objetos de la lista, avanzamos
	if (((inventory_.page_+1) * INVENTORY_VISIBLE_ELEMENTS) < inventory_.objects_->size()) {
		inventory_.page_++;
	}
}

void StashState::previousInventoryPage()
{	//Si el primer elemento de la página anterior del la lista no es negativo(no existe), retrocedemos
	if (((inventory_.page_ - 1) * INVENTORY_VISIBLE_ELEMENTS) >=0) {
		inventory_.page_--;
	}
}

void StashState::advanceStashPage()
{	//Si el primer elemento de la siguiente página no se pasa del número de objetos de la lista, avanzamos
	if ((stash_.page_ + 1) * STASH_VISIBLE_ELEMENTS < stash_.objects_->size()) {
		stash_.page_++;
	}
}

void StashState::previousStashPage()
{	//Si el primer elemento de la página anterior del la lista no es negativo(no existe), retrocedemos
	if ((stash_.page_ - 1) * STASH_VISIBLE_ELEMENTS >= 0) {
		stash_.page_--;
	}
}

void StashState::selectObject(InventoryButton* button)
{
	selected_ = button;
}

void StashState::changeBetweenLists()
{
	//Comprobamos si hay algun elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected está en la lista del inventario
		auto it = find(inventory_.objects_->begin(), inventory_.objects_->end(), selected_);
		
		//Una vez sabemos a cual, lo intercambiamos de lista
		if (it == inventory_.objects_->end()) {
			it = inventory_.objects_->insert(inventory_.objects_->end(), selected_);//Insertamos en la otra
			stash_.objects_->erase(selected_->getIterator()); //Lo quitamos de la inicial
			selected_->setIterator(it);//actualizamos iterador
			
		}
		else {
			it = stash_.objects_->insert(stash_.objects_->end(), selected_);//Insertamos en la otra
			inventory_.objects_->erase(selected_->getIterator());//Lo quitamos
			selected_->setIterator(it);//actualizamos iterador
		}
	}
}

void StashState::drawList(list<InventoryButton*>* list_, int page, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween, int elementsPerRow)const
{
	//Si existe la lista y no está vacía la dibujamos
	if (list_!= nullptr && !list_->empty()) {
		int i = 0;
		auto aux = list_->begin();
		advance(aux, page * elemsPerPage);
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


