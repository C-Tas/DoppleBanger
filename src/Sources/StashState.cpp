#include "StashState.h"
#include "GameManager.h"
#include "Armor.h"
#include "Gloves.h"
#include "Boots.h"
#include "Sword.h"
#include "Gun.h"

#pragma region Callbacks

void StashState::backToPrevious(Application* app) {
	app->getGameStateMachine()->popState();
}

void StashState::callbackAdvanceInventoryPage(Application* app) {
	dynamic_cast<StashState*>(app->getCurrState())->advanceInventoryPage();
}

void StashState::callbackAdvanceStashPage(Application* app) {
	dynamic_cast<StashState*>(app->getCurrState())->advanceStashPage();
}

void StashState::callbackPreviousInventoryPage(Application* app) {
	dynamic_cast<StashState*>(app->getCurrState())->previousInventoryPage();
}

void StashState::callbackPreviousStashPage(Application* app) {
	dynamic_cast<StashState*>(app->getCurrState())->previousStashPage();
}

void StashState::callbackSelectObject(Application* app, InventoryButton* button)
{
	dynamic_cast<StashState*>(app->getCurrState())->selectObject(button);
}

void StashState::callbackChangeBetweenLists(Application* app)
{
	dynamic_cast<StashState*>(app->getCurrState())->changeBetweenLists();
}

void StashState::callbackDeleteObject(Application* app)
{
	dynamic_cast<StashState*>(app->getCurrState())->deleteObject();
}

void StashState::callbackAddMoneyToInventary(Application* app)
{
	dynamic_cast<StashState*>(app->getCurrState())->addMoneyToInventory();
}

void StashState::callbackAddMoneyToStash(Application* app)
{
	dynamic_cast<StashState*>(app->getCurrState())->addMoneyToStash();
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
	drawList(stash_.objects_, stash_.firstDrawn, STASH_VISIBLE_ELEMENTS, FIRST_STASH_ELEMENT, DISTANCE_BETWEEN_ELEMENTS, ELEMENTS_PER_ROW);
	drawList(inventory_.objects_, inventory_.firstDrawn, INVENTORY_VISIBLE_ELEMENTS, FIRST_INVENTORY_ELEMENT, DISTANCE_BETWEEN_ELEMENTS, ELEMENTS_PER_ROW);

	//Escribimos la informaci�n del boton seleccionado
	if (selectedObjectDescription_ != nullptr)selectedObjectDescription_->render(DESCRIPTION_RECT);
}

void StashState::update()
{
	//update de los objetos del inventario que hay en pantalla
	//auto it = inventory_.objects_->begin();
	//advance(it, inventory_.page_ * INVENTORY_VISIBLE_ELEMENTS);
	auto it = inventory_.firstDrawn;
	for (int i = 0; it != inventory_.objects_->end() && i < INVENTORY_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}
	//update de los objetos del alijo que hay en pantalla
	it = stash_.firstDrawn;
	//advance(it, stash_.page_ * STASH_VISIBLE_ELEMENTS);
	for (int i = 0; it != stash_.objects_->end() && i < STASH_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}
	//Update de todos los botones
	GameState::update();
}

void StashState::initState() {
	//Fondo
	background_ = app_->getTextureManager()->getTexture(Resources::TextureId::StashMenu);

	//Bot�n de avanzar la p�gina del inventario
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow), Vector2D((56 * (app_->getWindowWidth() / 70)), ARROW_ROW), Vector2D(BUTTON_SIZE,BUTTON_SIZE), callbackAdvanceInventoryPage));
	//Bot�n de volver a la p�gina anterior del inventario
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::BackwardsArrow), Vector2D(43 * (app_->getWindowWidth() / 70), ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackPreviousInventoryPage));
	
	//Bot�n de avanzar la p�gina del alijo
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow), Vector2D(22 * (app_->getWindowWidth() / 70), ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackAdvanceStashPage));
	//Bot�n de volver a la p�gina anterior del alijo
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BackwardsArrow), Vector2D((14 * (app_->getWindowWidth() / 70))+10, ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackPreviousStashPage));

	//Bot�n para cambiar el objeto de una lista a otra
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::ChangeButton), Vector2D(FUNCTIONALITY_BUTTONS_COLUMN, 6 * (app_->getWindowHeight() / 9)), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackChangeBetweenLists));
	//Bot�n para eliminar el objeto seleccionado
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::TrashButton), Vector2D(FUNCTIONALITY_BUTTONS_COLUMN, 7 * (app_->getWindowHeight() / 9)), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackDeleteObject));

	//Bot�n de volver al estado anterior
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), Vector2D(CLOSE_BUTTON_COLUMN, 2* (double)(app_->getWindowHeight()/9)), CLOSE_BUTTON_SIZE, backToPrevious));

	//Boton para pasar el dinero del alijo al inventario
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::MoneyButton), Vector2D((7 * (app_->getWindowWidth() / 70)), MONEY_BUTTON_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackAddMoneyToInventary));
	//Boton para pasar el dinero del inventario al alijo
	addRenderUpdateLists(new Button(app_,  app_->getTextureManager()->getTexture(Resources::TextureId::MoneyButton), Vector2D((37 * (app_->getWindowWidth() / 70))+10,MONEY_BUTTON_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackAddMoneyToStash));

	//Cogemos la referencia al dinero de gameManager
	stash_.money_ = gm_->getStashGold();
	inventory_.money_ = gm_->getInventoryGold();

	//Posici�n de los textos del alijo e inventario
	stash_.moneyText = { 5 * (app_->getWindowWidth() / 16), MONEY_BUTTON_ROW + MONEY_TEXT_OFFSET, FONT_WIDTH,FONT_HEIGHT }; //width es el ancho de cada n�mero 
	inventory_.moneyText = { 4 * (app_->getWindowWidth() / 5) - 10,MONEY_BUTTON_ROW + MONEY_TEXT_OFFSET, FONT_WIDTH,FONT_HEIGHT };

	//Texturas con texto
	inventoryMoneyTex_ = new Texture(app_->getRenderer(), to_string(inventory_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,0 }));
	stashMoneyTex_ = new Texture(app_->getRenderer(), to_string(stash_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
	//Creo aqu� objetos para comprobar funcionalidad

	//Cogemos la referencia de las listas que hay en GameManager
	stash_.objects_ = gm_->getStash();
	inventory_.objects_ = gm_->getInventory();
	///Reasignamos el callback y el estado puesto que si se borra el antiguo stash, no se podrá seleccionar 
	//ninguno de los objetos al no estar la función en la misma direccion de memoria
	for (auto ob = inventory_.objects_->begin(); ob != inventory_.objects_->end(); ++ob) {
		(*ob)->setNewCallBack(callbackSelectObject);
		(*ob)->setCurrentState(this);
	}
	for (auto ob = stash_.objects_->begin(); ob != stash_.objects_->end(); ++ob) {
		(*ob)->setNewCallBack(callbackSelectObject);
		(*ob)->setCurrentState(this);
	}

	inventory_.firstDrawn = inventory_.objects_->begin();
	stash_.firstDrawn = stash_.objects_->begin();
}

void StashState::endState()
{
	gm_->setInventoryGold(inventory_.money_);
	gm_->setStashGold(stash_.money_);

	delete inventoryMoneyTex_;
	delete stashMoneyTex_;
	delete selectedObjectDescription_;
}

#pragma region privateCallbacks

void StashState::advanceInventoryPage() {
	//Si el primer elemento de la siguiente p�gina no se pasa del n�mero de objetos de la lista, avanzamos
	if (((inventory_.page_ + 1) * INVENTORY_VISIBLE_ELEMENTS) < inventory_.objects_->size()) {
		inventory_.page_++;
		advance(inventory_.firstDrawn, INVENTORY_VISIBLE_ELEMENTS);
	}
}

void StashState::previousInventoryPage()
{	//Si el primer elemento de la p�gina anterior del la lista no es negativo(no existe), retrocedemos
	if (((inventory_.page_ - 1) * INVENTORY_VISIBLE_ELEMENTS) >=0) {
		inventory_.page_--;
		advance(inventory_.firstDrawn, -INVENTORY_VISIBLE_ELEMENTS);
	}
}

void StashState::advanceStashPage()
{	//Si el primer elemento de la siguiente p�gina no se pasa del n�mero de objetos de la lista, avanzamos
	if ((stash_.page_ + 1) * STASH_VISIBLE_ELEMENTS < stash_.objects_->size()) {
		stash_.page_++;
		advance(stash_.firstDrawn, STASH_VISIBLE_ELEMENTS);
	}
}

void StashState::previousStashPage()
{	//Si el primer elemento de la p�gina anterior del la lista no es negativo(no existe), retrocedemos
	if ((stash_.page_ - 1) * STASH_VISIBLE_ELEMENTS >= 0) {
		stash_.page_--;
		advance(stash_.firstDrawn, -STASH_VISIBLE_ELEMENTS);
	}
}

void StashState::selectObject(InventoryButton* button)
{
	selected_ = button;
	if (selectedObjectDescription_ != nullptr)delete selectedObjectDescription_;
	selectedObjectDescription_ = new Texture(app_->getRenderer(), "Descripcion Temporal", app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
}

void StashState::changeBetweenLists()
{
	//Comprobamos si hay algun elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected est� en la lista del inventario
		auto it = find(inventory_.firstDrawn, inventory_.objects_->end(), selected_);
		
		//Una vez sabemos a cual, lo intercambiamos de lista
		if (it == inventory_.objects_->end()) {

			selectedIsLastElement(stash_, STASH_VISIBLE_ELEMENTS);
			//Insertamos en la otra lista
			it = inventory_.objects_->insert(inventory_.objects_->end(), selected_);
			//Si no había ningún elemento en la lista, asignamos como por defecto el primero
			if (inventory_.objects_->end() == inventory_.firstDrawn)inventory_.firstDrawn = inventory_.objects_->begin();
			//Lo quitamos de la inicial
			stash_.objects_->erase(selected_->getIterator());
			//actualizamos iterador
			selected_->setIterator(it);
			if (stash_.objects_->size() == 0) stash_.firstDrawn = stash_.objects_->begin();
		}
		else {
			selectedIsLastElement(inventory_, INVENTORY_VISIBLE_ELEMENTS);
			//Insertamos en la otra lista
			it = stash_.objects_->insert(stash_.objects_->end(), selected_);
			//Si no había ningún elemento en la lista, asignamos como por defecto el primero
			if (stash_.objects_->end() == stash_.firstDrawn)stash_.firstDrawn = stash_.objects_->begin();
			//Lo quitamos
			inventory_.objects_->erase(selected_->getIterator());
			//actualizamos iterador
			selected_->setIterator(it);
			if (inventory_.objects_->size() == 0)inventory_.firstDrawn = inventory_.objects_->begin();
		}
	}
}

void StashState::deleteObject()
{
	//Comprobamos si hay alg�n elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected est� en la lista del inventario
		auto it = find(inventory_.firstDrawn, inventory_.objects_->end(), selected_);

		//Quitamos el objeto de la lista en la que se encuentra
		if (it == inventory_.objects_->end()) {
			selectedIsLastElement(stash_, STASH_VISIBLE_ELEMENTS);
			stash_.objects_->erase(selected_->getIterator());
			if (stash_.objects_->size() == 0) stash_.firstDrawn = stash_.objects_->begin();
		}
		else
		{
			selectedIsLastElement(inventory_, INVENTORY_VISIBLE_ELEMENTS);
			inventory_.objects_->erase(selected_->getIterator());
			if (inventory_.objects_->size() == 0)inventory_.firstDrawn = inventory_.objects_->begin();
		}

		//Borramos el objeto
		delete selected_;
		//Borramos la textura con la descripci�n del antiguo objeto seleccionado
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

void StashState::drawList(list<InventoryButton*>* list_, list<InventoryButton*>::iterator it, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween, int elementsPerRow)const
{
	//Si existe la lista y no est� vac�a la dibujamos
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

	if (selected_->getIterator() == list_.firstDrawn && list_.firstDrawn == aux && aux != --list_.objects_->end())++list_.firstDrawn;
	else if (selected_->getIterator() == list_.firstDrawn && list_.firstDrawn != list_.objects_->begin() && list_.firstDrawn == --list_.objects_->end()) {
		advance(list_.firstDrawn, -nVisibleElements);
		list_.page_--;
	}
}

void StashState::moneyChange()
{
	delete inventoryMoneyTex_;
	delete stashMoneyTex_;
	inventoryMoneyTex_ = new Texture(app_->getRenderer(), to_string(inventory_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,0 }));
	stashMoneyTex_ = new Texture(app_->getRenderer(), to_string(stash_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
}


