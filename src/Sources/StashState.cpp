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
	//background_->render({ 0, 0, app_->getWindowWidth(), app_->getWindowHeight()});
	
	//Dibujamos todos los botones
	GameState::draw();

	//Dibujamos la cantidad de oro que hay en ambos inventarios
	Texture inventoryMoney = Texture(app_->getRenderer(), to_string(inventory_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({255,255,255,1}));
	inventoryMoney.render({ inventory_.moneyText.x + inventory_.moneyText.w, inventory_.moneyText.y+20, 
		20*nOfDigits(inventory_.money_) ,inventory_.moneyText.h - 25 } );

	Texture stashMoney = Texture(app_->getRenderer(), to_string(stash_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 255,255,255,1 }));
	stashMoney.render({ stash_.moneyText.x + stash_.moneyText.w, stash_.moneyText.y+20, 
		20*nOfDigits(stash_.money_) ,stash_.moneyText.h - 25 });

	//Dibujamos los objetos visibles en el inventario y en el alijo
	//Primer vector determina donde se posiciona el primer objeto y el segundo la distancia en x e y entre objetos
	drawList(stash_.objects_, stash_.page_, STASH_VISIBLE_ELEMENTS, Vector2D(app_->getWindowWidth() / 9, app_->getWindowHeight() / 3), Vector2D((app_->getWindowWidth() / 8), (app_->getWindowHeight() / 10)), 2);
	drawList(inventory_.objects_, inventory_.page_, INVENTORY_VISIBLE_ELEMENTS, Vector2D((app_->getWindowWidth()/2), app_->getWindowHeight() / 3), Vector2D((app_->getWindowWidth() / 8), (app_->getWindowHeight() / 10)), 2);
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
	//Botón para eliminar el objeto seleccionado
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1500, 450), Vector2D(50, 50), callbackDeleteObject));

	//Botón de volver al estado anterior
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1500, 50), Vector2D(50, 50), backToPrevious));

	//Boton para pasar el dinero del alijo al inventario
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1500, 600), Vector2D(50, 50), callbackAddMoneyToInventary));
	//Boton para pasar el dinero del inventario al alijo
	addRenderUpdateLists(new Button(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(1500, 750), Vector2D(50, 50), callbackAddMoneyToStash));


	GameManager* gm = GameManager::instance();

	//Cogemos la referencia de las listas que hay en GameManager
	stash_.objects_ = gm->getStash();
	inventory_.objects_ = gm->getInventory();

	//Cogemos la referencia al dinero de gameManager
	stash_.money_ = gm->getStashGold();
	inventory_.money_ = gm->getInventoryGold();

	//Posición de los textos del alijo e inventario
	stash_.moneyText = { 1000, 700, 200,100 };
	inventory_.moneyText = { 100,700, 200,100 };

	//Textos dinero del Alijo y del inventario
	addRenderUpdateLists(new Draw(app_, app_->getTextureManager()->getTexture(Resources::StashMoneyText), stash_.moneyText));
	addRenderUpdateLists(new Draw(app_, app_->getTextureManager()->getTexture(Resources::InventoryMoneyText), inventory_.moneyText));

	//Creo aquí objetos para comprobar funcionalidad
	#ifdef _DEBUG
	cout << "Creando Objetos de prueba en el initState" << endl;

	Gun* gun = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon),"pistolaDefault", "uwu",0,0,0,Shotgun_);
	Gun* gun1 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu", 0, 0, 0, Shotgun_);
	Gun* gun2 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu", 0, 0, 0, Shotgun_);
	Gun* gun3 = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), "pistolaDefault", "uwu", 0, 0, 0, Shotgun_);

	
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

#pragma region privateCallbacks

void StashState::endState()
{
	GameManager* gm = GameManager::instance();
	gm->setInventoryGold(inventory_.money_);
	gm->setStashGold(stash_.money_);
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
		//Ponemos el puntero a null para evitar posibles errores
		selected_ = nullptr;

	}
}

void StashState::addMoneyToInventory()
{
	inventory_.money_ += stash_.money_;
	stash_.money_ = 0;
}

void StashState::addMoneyToStash()
{
	stash_.money_ += inventory_.money_;
	inventory_.money_ = 0;
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


