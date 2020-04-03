#include "StashState.h"
#include "GameManager.h"

#pragma region Callbacks

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

void StashState::callbackDeleteObject(GameState* state)
{
	dynamic_cast<StashState*>(state)->deleteObject();
}

void StashState::callbackAddMoneyToInventary(GameState* state)
{
	dynamic_cast<StashState*>(state)->addMoneyToInventory();
}

void StashState::callbackAddMoneyToStash(GameState* state)
{
	dynamic_cast<StashState*>(state)->addMoneyToStash();
}
#pragma endregion

void StashState::draw() const
{
	//Dibujamos el fondo (de momento es el provisional)
	background_->render({ 0, 0, app_->getWindowWidth(), app_->getWindowHeight()});
	
	//Dibujamos todos los botones
	GameState::draw();

	//Dibujamos la cantidad de oro que hay en ambos inventarios
	inventoryMoneyTex_->render({ inventory_.moneyText.x, inventory_.moneyText.y, inventory_.moneyText.w *nOfDigits(inventory_.money_) ,inventory_.moneyText.h} );
	stashMoneyTex_->render({ stash_.moneyText.x, stash_.moneyText.y, stash_.moneyText.w *nOfDigits(stash_.money_) ,stash_.moneyText.h });

	//Dibujamos los objetos visibles en el inventario y en el alijo
	//Primer vector determina donde se posiciona el primer objeto y el segundo la distancia en x e y entre objetos
	drawList(stash_.objects_, stash_.page_, STASH_VISIBLE_ELEMENTS, Vector2D(app_->getWindowWidth() / 9, (app_->getWindowHeight() / 3) + (app_->getWindowHeight()/10)), Vector2D((app_->getWindowWidth() / 5), (app_->getWindowHeight() / 8)), 2);
	drawList(inventory_.objects_, inventory_.page_, INVENTORY_VISIBLE_ELEMENTS, Vector2D((app_->getWindowWidth()/2) + 55, (app_->getWindowHeight() / 3) + (app_->getWindowHeight() / 10)), Vector2D((app_->getWindowWidth() / 5), (app_->getWindowHeight() / 8)), 2);

	//Escribimos la información del boton seleccionado
	if (selectedObjectDescription_ != nullptr)selectedObjectDescription_->render({850, 675, 100, 50});
}

void StashState::update()
{
	//Update de todos los botones
	GameState::update();

	//update de los objetos del inventario que hay en pantalla
	auto it = inventory_.objects_->begin();
	advance(it, inventory_.page_ * INVENTORY_VISIBLE_ELEMENTS);
	for (int i = 0; it != inventory_.objects_->end() && i < INVENTORY_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}

	//update de los objetos del alijo que hay en pantalla
	it = stash_.objects_->begin();
	advance(it, stash_.page_ * STASH_VISIBLE_ELEMENTS);
	for (int i = 0; it != stash_.objects_->end() && i < STASH_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}
}

void StashState::initState() {
	//Fondo
	background_ = app_->getTextureManager()->getTexture(Resources::TextureId::StashMenu);

	//Botón de avanzar la página del inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow), Vector2D(1225, 299), Vector2D(75, 75), callbackAdvanceInventoryPage));
	//Botón de volver a la página anterior del inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::BackwardsArrow), Vector2D(957, 299), Vector2D(75, 75), callbackPreviousInventoryPage));
	
	//Botón de avanzar la página del alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow), Vector2D(490, 299), Vector2D(75, 75), callbackAdvanceStashPage));
	//Botón de volver a la página anterior del alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::BackwardsArrow), Vector2D(315, 299), Vector2D(75, 75), callbackPreviousStashPage));

	//Botón para cambiar el objeto de una lista a otra
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::ChangeButton), Vector2D(1430, 603), Vector2D(75, 75), callbackChangeBetweenLists));
	//Botón para eliminar el objeto seleccionado
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::TrashButton), Vector2D(1430, 703), Vector2D(75, 75), callbackDeleteObject));

	//Botón de volver al estado anterior
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::CloseButton), Vector2D(1431, 200), Vector2D(75, 75), backToPrevious));

	//Boton para pasar el dinero del alijo al inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::MoneyButton), Vector2D(168, 235), Vector2D(75, 75), callbackAddMoneyToInventary));
	//Boton para pasar el dinero del inventario al alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::MoneyButton), Vector2D(835, 235), Vector2D(75, 75), callbackAddMoneyToStash));

	GameManager* gm = GameManager::instance();

	//Cogemos la referencia de las listas que hay en GameManager
	stash_.objects_ = gm->getStash();
	inventory_.objects_ = gm->getInventory();

	//Cogemos la referencia al dinero de gameManager
	stash_.money_ = gm->getStashGold();
	inventory_.money_ = gm->getInventoryGold();

	//Posición de los textos del alijo e inventario
	stash_.moneyText = { 500, 245, 20,50 }; //width es el ancho de cada número 
	inventory_.moneyText = { 1260,245, 20,50 };

	//Texturas con texto
	inventoryMoneyTex_ = new Texture(app_->getRenderer(), to_string(inventory_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,0 }));
	stashMoneyTex_ = new Texture(app_->getRenderer(), to_string(stash_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
	//Creo aquí objetos para comprobar funcionalidad
	#ifdef _DEBUG
	cout << "Creando Objetos de prueba en el initState" << endl;

	Gun* gun = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon),"pistolaDefault", "uwu1",0,0,0,Shotgun_);
	Gun* gun1 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu2", 0, 0, 0, Shotgun_);
	Gun* gun2 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu3", 0, 0, 0, Shotgun_);
	Gun* gun3 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu4", 0, 0, 0, Shotgun_);

	
	InventoryButton* b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun, callbackSelectObject);
	auto it = stash_.objects_->insert(stash_.objects_->end(),b);
	b->setIterator(it);
	b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun1, callbackSelectObject);
	it = stash_.objects_->insert(stash_.objects_->end(), b);
	b->setIterator(it);
	b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun3, callbackSelectObject);
	it = stash_.objects_->insert(stash_.objects_->end(), b);
	b->setIterator(it);
	
	b = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
		Vector2D(100, 400), Vector2D(50, 50), gun2, callbackSelectObject);
	it = inventory_.objects_->insert(inventory_.objects_->end(), b);
	b->setIterator(it);



	#endif // _DEBUG
}

void StashState::endState()
{
	GameManager* gm = GameManager::instance();
	gm->setInventoryGold(inventory_.money_);
	gm->setStashGold(stash_.money_);

	delete inventoryMoneyTex_;
	delete stashMoneyTex_;
	delete selectedObjectDescription_;
}

#pragma region privateCallbacks

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
	if (selectedObjectDescription_ != nullptr)delete selectedObjectDescription_;
	selectedObjectDescription_ = new Texture(app_->getRenderer(), selected_->getObject()->getItemDescription(), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
}

void StashState::changeBetweenLists()
{
	//Comprobamos si hay algun elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected está en la lista del inventario
		auto it = find(inventory_.objects_->begin(), inventory_.objects_->end(), selected_);
		
		//Una vez sabemos a cual, lo intercambiamos de lista
		if (it == inventory_.objects_->end()) {

			selectedIsLastElement(stash_, STASH_VISIBLE_ELEMENTS);
			//Insertamos en la otra lista
			it = inventory_.objects_->insert(inventory_.objects_->end(), selected_);
			//Lo quitamos de la inicial
			stash_.objects_->erase(selected_->getIterator());
			//actualizamos iterador
			selected_->setIterator(it);
			
		}
		else {

			selectedIsLastElement(inventory_, INVENTORY_VISIBLE_ELEMENTS);
			//Insertamos en la otra lista
			it = stash_.objects_->insert(stash_.objects_->end(), selected_);
			//Lo quitamos
			inventory_.objects_->erase(selected_->getIterator());
			//actualizamos iterador
			selected_->setIterator(it);
		}
	}
}

void StashState::deleteObject()
{
	//Comprobamos si hay algún elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected está en la lista del inventario
		auto it = find(inventory_.objects_->begin(), inventory_.objects_->end(), selected_);

		//Quitamos el objeto de la lista en la que se encuentra
		if (it == inventory_.objects_->end()) {
			selectedIsLastElement(stash_, STASH_VISIBLE_ELEMENTS);
			stash_.objects_->erase(selected_->getIterator());
		}
		else
		{
			selectedIsLastElement(inventory_, INVENTORY_VISIBLE_ELEMENTS);
			inventory_.objects_->erase(selected_->getIterator());
		}

		//Borramos el objeto
		delete selected_;
		//Borramos la textura con la descripción del antiguo objeto seleccionado
		delete selectedObjectDescription_;
		//Ponemos el puntero a null para evitar posibles errores
		selected_ = nullptr;
		selectedObjectDescription_ = nullptr;

	}
}

void StashState::addMoneyToInventory()
{
	inventory_.money_ += stash_.money_;
	stash_.money_ = 0;
	moneyChange();
}

void StashState::addMoneyToStash()
{
	stash_.money_ += inventory_.money_;
	inventory_.money_ = 0;
	moneyChange();
}

#pragma endregion

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

int StashState::nOfDigits(int n) const
{
	int i = 1;
	while (n / 10 > 0) {
		n /= 10;
		i++;
	}
	return i;
	return 0;
}

void StashState::selectedIsLastElement(Container & list_, int nVisibleElements)
{
	auto aux = list_.objects_->begin();
	advance(aux, list_.page_ * nVisibleElements);

	//Si es el ultimo objeto,no es el primero de todos, está solo en una página y es el que queremos mover, 
	//vamos a retroceder esa página a la anterior con objetos
	if (--list_.objects_->end() == selected_->getIterator() && list_.page_ > 0 && selected_->getIterator() == aux) list_.page_--;
}

void StashState::moneyChange()
{
	delete inventoryMoneyTex_;
	delete stashMoneyTex_;
	inventoryMoneyTex_ = new Texture(app_->getRenderer(), to_string(inventory_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,0 }));
	stashMoneyTex_ = new Texture(app_->getRenderer(), to_string(stash_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
}


