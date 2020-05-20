#include "ShopState.h"
#include "Player.h"
#include "InventoryButton.h"
#include "Armor.h"
#include "Gloves.h"
#include "Boots.h"
#include "Sword.h"
#include "Gun.h"
#include "usable.h"
#include "TextBox.h"

#pragma region Callbacks

void ShopState::backToPrevious(Application* app) {
	app->getGameStateMachine()->popState();
	SDL_ShowCursor(SDL_DISABLE);
	//Se resetea la musica del barco
	app->resetMusicChannels();
	app->getAudioManager()->playChannel(Resources::WavesSound, -1, Resources::AuxMusicChannel1);
}

void ShopState::callbackAdvanceInventoryPage(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->advanceInventoryPage();
}

void ShopState::callbackAdvanceShopPage(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->advanceShopPage();
}

void ShopState::callbackPreviousInventoryPage(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->previousInventoryPage();
}

void ShopState::callbackPreviousShopPage(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->previousShopPage();
}

void ShopState::callbackSelectObject(Application* app, InventoryButton* button)
{
	dynamic_cast<ShopState*>(app->getCurrState())->selectObject(button);
}

void ShopState::callbackChangeBetweenLists(Application* app)
{
	dynamic_cast<ShopState*>(app->getCurrState())->changeBetweenLists();
}

void ShopState::callbackDeleteObject(Application* app)
{
	dynamic_cast<ShopState*>(app->getCurrState())->deleteObject();
}

void ShopState::callbackAddMoneyToInventary(Application* app)
{
	dynamic_cast<ShopState*>(app->getCurrState())->addMoneyToInventory();
}

#pragma endregion

void ShopState::draw() const
{
	//Dibujamos el fondo (de momento es el provisional)
	background_->render({ 0, 0, app_->getWindowWidth(), app_->getWindowHeight() });

	//Dibujamos todos los botones
	GameState::draw();

	//Dibujamos la cantidad de oro que hay en ambos inventarios
	inventoryMoneyTex_->render({ inventory_.moneyText.x, inventory_.moneyText.y, inventory_.moneyText.w * nOfDigits(inventory_.money_) ,inventory_.moneyText.h });

	//Dibujamos los objetos visibles en el inventario y en la tienda
	//Primer vector determina donde se posiciona el primer objeto y el segundo la distancia en x e y entre objetos
	drawList(shop_.objects_, shop_.firstDrawn, SHOP_VISIBLE_ELEMENTS, FIRST_SHOP_ELEMENT, DISTANCE_BETWEEN_ELEMENTS, ELEMENTS_PER_ROW);
	drawList(inventory_.objects_, inventory_.firstDrawn, INVENTORY_VISIBLE_ELEMENTS, FIRST_INVENTORY_ELEMENT, DISTANCE_BETWEEN_ELEMENTS, ELEMENTS_PER_ROW);

	//Escribimos la informaci�n del boton seleccionado
	if (selectedObjectDescription_ != nullptr)selectedObjectDescription_->render(DESCRIPTION_RECT);

	//pintar textos
	//descripcion objetos
	if (selected_ != nullptr) {
		selected_->getObject()->getDescription(descriptionBox);
	}
	double posx1 = (double)(app_->getWindowWidth() / 1.684);//950;
	double posy = (double)(app_->getWindowHeight() / 1.184);//770;

	if (selected_ != nullptr) {
		Texture potionText(app_->getRenderer(), "Precio: " + to_string((int)selected_->getObject()->getPrice()), app_->getFontManager()->getFont(Resources::FontId::RETRO), SDL_Color({ 0,0,0,1 }));
		potionText.render(posx1, posy);
	}
}

void ShopState::update()
{
	//update de los objetos del inventario que hay en pantalla
	auto it = inventory_.firstDrawn;
	for (int i = 0; it != inventory_.objects_->end() && i < INVENTORY_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}
	//update de los objetos de la tienda que hay en pantalla
	it = shop_.firstDrawn;
	//advance(it, stash_.page_ * STASH_VISIBLE_ELEMENTS);
	for (int i = 0; it != shop_.objects_->end() && i < SHOP_VISIBLE_ELEMENTS; i++) {
		(*it)->update();
		++it;
	}
	//Update de todos los botones
	GameState::update();
}

void ShopState::initState() {
	SDL_ShowCursor(SDL_ENABLE);
	//Fondo
	background_ = app_->getTextureManager()->getTexture(Resources::TextureId::ShopMenu);

	//Bot�n de avanzar la p�gina del inventario
	addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow)*/, Vector2D((57 * (app_->getWindowWidth() / 70)), ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackAdvanceInventoryPage));
	//Bot�n de volver a la p�gina anterior del inventario
	addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::BackwardsArrow)*/, Vector2D(45 * (app_->getWindowWidth() / 70), ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackPreviousInventoryPage));

	//Bot�n de avanzar la p�gina de la tienda
	addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow)*/, Vector2D(45 * (app_->getWindowWidth() / 140), ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackAdvanceShopPage));
	//Bot�n de volver a la p�gina anterior de la tienda
	addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::BackwardsArrow)*/, Vector2D((29 * (app_->getWindowWidth() / 140)) + 10, ARROW_ROW), Vector2D(BUTTON_SIZE, BUTTON_SIZE), callbackPreviousShopPage));

	//Bot�n para cambiar el objeto de una lista a otra
	addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::ChangeButton)*/, Vector2D(45 * (app_->getWindowWidth() / 64), FUNCTIONALITY_BUTTONS_ROW), Vector2D(5*BUTTON_SIZE, BUTTON_SIZE), callbackChangeBetweenLists));
	//Bot�n para eliminar el objeto seleccionado
	//addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::TrashButton)*/, Vector2D( 26 * (app_->getWindowWidth() / 32), FUNCTIONALITY_BUTTONS_ROW), Vector2D(2*BUTTON_SIZE, BUTTON_SIZE), callbackDeleteObject));

	//Bot�n de volver al estado anterior
	addRenderUpdateLists(new Button(app_, nullptr/*app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX)*/, Vector2D(CLOSE_BUTTON_COLUMN, 2 * (double)(app_->getWindowHeight() / 9)), CLOSE_BUTTON_SIZE, backToPrevious));

	//Cogemos la referencia al dinero de gameManager
	inventory_.money_ = gm_->getInventoryGold();

	//Posicion de los textos de la tienda e inventario
	inventory_.moneyText = { 25 * (app_->getWindowWidth() / 40),MONEY_BUTTON_ROW + MONEY_TEXT_OFFSET, FONT_WIDTH,FONT_HEIGHT };

	//Texturas con texto
	inventoryMoneyTex_ = new Texture(app_->getRenderer(), to_string(inventory_.money_), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,0 }));

	//Cogemos la referencia de las listas que hay en GameManager
	createItems(8);
	shop_.objects_ = gm_->getShop();
	inventory_.objects_ = gm_->getInventory();

	///Reasignamos el callback y el estado puesto que si se borra el antiguo Shop, no se podrá seleccionar 
	//ninguno de los objetos al no estar la función en la misma direccion de memoria
	for (auto ob = inventory_.objects_->begin(); ob != inventory_.objects_->end(); ++ob) {
		(*ob)->setNewCallBack(callbackSelectObject);
		(*ob)->setCurrentState(this);
	}
	for (auto ob = shop_.objects_->begin(); ob != shop_.objects_->end(); ++ob) {
		(*ob)->setNewCallBack(callbackSelectObject);
		(*ob)->setCurrentState(this);
	}

	inventory_.firstDrawn = inventory_.objects_->begin();
	shop_.firstDrawn = shop_.objects_->begin();
	//descripcion de objetos
	descriptionPoint = Point2D((double)(app_->getWindowWidth() / 1.88), (double)(app_->getWindowHeight() / 1.45));//850,620
	descriptionBox = new TextBox(app_, descriptionPoint);
}

void ShopState::endState()
{
	delete inventoryMoneyTex_;
	delete selectedObjectDescription_;
	delete descriptionBox;
}

#pragma region privateCallbacks

void ShopState::advanceInventoryPage() {
	//Si el primer elemento de la siguiente p�gina no se pasa del n�mero de objetos de la lista, avanzamos
	if (((inventory_.page_ + 1) * INVENTORY_VISIBLE_ELEMENTS) < inventory_.objects_->size()) {
		inventory_.page_++;
		advance(inventory_.firstDrawn, INVENTORY_VISIBLE_ELEMENTS);
	}
}

void ShopState::previousInventoryPage()
{	//Si el primer elemento de la p�gina anterior del la lista no es negativo(no existe), retrocedemos
	if (((inventory_.page_ - 1) * INVENTORY_VISIBLE_ELEMENTS) >= 0) {
		inventory_.page_--;
		advance(inventory_.firstDrawn, -INVENTORY_VISIBLE_ELEMENTS);
	}
}

void ShopState::advanceShopPage()
{	//Si el primer elemento de la siguiente p�gina no se pasa del n�mero de objetos de la lista, avanzamos
	if ((shop_.page_ + 1) * SHOP_VISIBLE_ELEMENTS < shop_.objects_->size()) {
		shop_.page_++;
		advance(shop_.firstDrawn, SHOP_VISIBLE_ELEMENTS);
	}
}

void ShopState::previousShopPage()
{	//Si el primer elemento de la p�gina anterior del la lista no es negativo(no existe), retrocedemos
	if ((shop_.page_ - 1) * SHOP_VISIBLE_ELEMENTS >= 0) {
		shop_.page_--;
		advance(shop_.firstDrawn, -SHOP_VISIBLE_ELEMENTS);
	}
}

void ShopState::selectObject(InventoryButton* button)
{
	selected_ = button;
	if (selectedObjectDescription_ != nullptr)delete selectedObjectDescription_;
	//selectedObjectDescription_ = new Texture(app_->getRenderer(), "Descripcion Temporal", app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,1 }));
}

void ShopState::changeBetweenLists()
{
	//Comprobamos si hay algun elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected est� en la lista del inventario
		auto it = find(inventory_.firstDrawn, inventory_.objects_->end(), selected_);
		
		//Una vez sabemos a cual, lo intercambiamos de lista
		if (it == inventory_.objects_->end()) {
			selectedIsLastElement(shop_, SHOP_VISIBLE_ELEMENTS);
			if (gm_->getInventoryGold() >= selected_->getObject()->getPrice())
			{
				gm_->addInventoryGold(-selected_->getObject()->getPrice());
				moneyChange();
				//Insertamos en la otra lista
				it = inventory_.objects_->insert(inventory_.objects_->end(), selected_);
				//Si no había ningún elemento en la lista, asignamos como por defecto el primero
				if (inventory_.objects_->end() == inventory_.firstDrawn)inventory_.firstDrawn = inventory_.objects_->begin();
				//Lo quitamos de la inicial
				shop_.objects_->erase(selected_->getIterator());
				//actualizamos iterador
				selected_->setIterator(it);
				if (shop_.objects_->size() == 0) shop_.firstDrawn = shop_.objects_->begin();
			}
		}
		else {
			selectedIsLastElement(inventory_, INVENTORY_VISIBLE_ELEMENTS);
			gm_->addInventoryGold(selected_->getObject()->getPrice());
			moneyChange();
			//Insertamos en la otra lista
			it = shop_.objects_->insert(shop_.objects_->end(), selected_);
			//Si no había ningún elemento en la lista, asignamos como por defecto el primero
			if (shop_.objects_->end() == shop_.firstDrawn)shop_.firstDrawn = shop_.objects_->begin();
			//Lo quitamos
			inventory_.objects_->erase(selected_->getIterator());
			//actualizamos iterador
			selected_->setIterator(it);
			if (inventory_.objects_->size() == 0)inventory_.firstDrawn = inventory_.objects_->begin();
		}
	}
}

void ShopState::deleteObject()
{
	//Comprobamos si hay alg�n elemento seleccionado
	if (selected_ != nullptr) {

		//Buscamos si el objeto selected est� en la lista del inventario
		auto it = find(inventory_.firstDrawn, inventory_.objects_->end(), selected_);

		//Quitamos el objeto de la lista en la que se encuentra
		if (it == inventory_.objects_->end()) {
			selectedIsLastElement(shop_, SHOP_VISIBLE_ELEMENTS);
			shop_.objects_->erase(selected_->getIterator());
			if (shop_.objects_->size() == 0) shop_.firstDrawn = shop_.objects_->begin();
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

void ShopState::addMoneyToInventory()
{
	inventory_.money_ += shop_.money_;
	shop_.money_ = 0;
	moneyChange();
}

#pragma endregion

void ShopState::drawList(list<InventoryButton*>* list_, list<InventoryButton*>::iterator it, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween, int elementsPerRow)const
{
	//Si existe la lista y no est� vac�a la dibujamos
	if (list_ != nullptr && !list_->empty()) {
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

int ShopState::nOfDigits(int n) const
{
	int i = 1;
	while (n / 10 > 0) {
		n /= 10;
		i++;
	}
	return i;
	return 0;
}

void ShopState::selectedIsLastElement(ContainerSHOP& list_, int nVisibleElements)
{
	auto aux = list_.objects_->begin();
	advance(aux, list_.page_ * nVisibleElements);

	if (selected_->getIterator() == list_.firstDrawn && list_.firstDrawn == aux && aux != --list_.objects_->end())++list_.firstDrawn;//peta
	else if (selected_->getIterator() == list_.firstDrawn && list_.firstDrawn != list_.objects_->begin() && list_.firstDrawn == --list_.objects_->end()) {
		advance(list_.firstDrawn, -nVisibleElements);
		list_.page_--;
	}
}

void ShopState::moneyChange()
{
	delete inventoryMoneyTex_;
	inventoryMoneyTex_ = new Texture(app_->getRenderer(), to_string(gm_->getInventoryGold()), app_->getFontManager()->getFont(Resources::RETRO), SDL_Color({ 0,0,0,0 }));
}

void ShopState::createItems(int n)
{
	RandEquipGen* rand = app_->getEquipGen();
	for (size_t i = 0; i < n; i++)
	{
		Equipment* ob = rand->genEquip();
		gm_->addToShop(ob);
	}
}
