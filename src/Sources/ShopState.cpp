#include "ShopState.h"
#include "Player.h"
#include "InventoryButton.h"
#include "Armor.h"
#include "Gloves.h"
#include "Boots.h"
#include "Sword.h"
#include "Gun.h"

void callForwardListS(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->forwardList();
}
void callBackListS(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->backList();
}
void callShopForwardListS(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->ShopForwardList();
}
void callShopBackListS(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->ShopBackList();
}
void callExitS(Application* app) {
	app->getGameStateMachine()->popState();
}
void callSelectObjectS(Application* app, InventoryButton* ob) {
	dynamic_cast<ShopState*>(app->getCurrState())->selectObject(ob);
}
void callSellObjectS(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->sellObj();
}
void callBuyObjectS(Application* app) {
	dynamic_cast<ShopState*>(app->getCurrState())->buyObj();
}

ShopState::ShopState(Application* app, Player* player) :GameState(app), player_(player)
{
	sellButton_ = new Button(app, app_->getTextureManager()->getTexture(Resources::TextureId::MoneyButton), Vector2D{ 50,500 }, Vector2D{ 50,50 }, callSellObjectS);
	addUpdateList(sellButton_);
	addRenderList(sellButton_);
	advanceButton_ = new Button(app,  app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow), Vector2D{ 700,100 }, Vector2D{ 50,50 }, callForwardListS);
	addUpdateList(advanceButton_);
	addRenderList(advanceButton_);
	gobackButton_ = new Button(app,  app_->getTextureManager()->getTexture(Resources::TextureId::BackButton), Vector2D{ 500,100 }, Vector2D{ 50,50 }, callBackListS);
	addUpdateList(gobackButton_);
	addRenderList(gobackButton_);
	exitButton_ = new Button(app, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), Vector2D{ 1300,100 }, Vector2D{ 50,50 }, callExitS);
	addUpdateList(exitButton_);
	addRenderList(exitButton_);

	buyButton_ = new Button(app,  app_->getTextureManager()->getTexture(Resources::TextureId::MoneyButton), Vector2D{ 50,700 }, Vector2D{ 50,50 }, callBuyObjectS, 1);
	addUpdateList(buyButton_);
	addRenderList(buyButton_);
	shopAdvanceButton_ = new Button(app,  app_->getTextureManager()->getTexture(Resources::TextureId::ForwardArrow), Vector2D{ 300,100 }, Vector2D{ 50,50 }, callShopForwardListS, 1);
	addUpdateList(shopAdvanceButton_);
	addRenderList(shopAdvanceButton_);
	shopGobackButton_ = new Button(app,  app_->getTextureManager()->getTexture(Resources::TextureId::BackButton), Vector2D{ 100,100 }, Vector2D{ 50,50 }, callShopBackListS, 1);
	addUpdateList(shopGobackButton_);
	addRenderList(shopGobackButton_);

#ifdef _DEBUG

	Gloves* guante0 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);
	Gloves* guante1 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);
	Gloves* guante2 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);
	Gloves* guante3 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);
	Gloves* guante4 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);
	Gloves* guante5 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);
	Gloves* guante6 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesII);

	addToInventory(guante0);
	addToInventory(guante1);
	addToInventory(guante2);
	addToInventory(guante3);
	addToInventory(guante4);
	addToInventory(guante5);
	addToInventory(guante6);


	Gloves* guante11 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante12 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante13 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante14 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante15 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante16 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante17 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante18 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante19 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante20 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);
	Gloves* guante21 = new Gloves(app_, 20.0, 10, 10, equipType::GlovesI);

	addToShop(guante11);
	addToShop(guante12);
	addToShop(guante13);
	addToShop(guante14);
	addToShop(guante15);
	addToShop(guante16);
	addToShop(guante17);
	addToShop(guante18);
	addToShop(guante19);
	addToShop(guante20);
	addToShop(guante21);

#endif

}

ShopState::~ShopState()
{
	for (InventoryButton* object : shopList_) {
		delete object;
		object = nullptr;
	}
	shopList_.clear();

	for (InventoryButton* object : inventoryList_) {
		delete object;
		object = nullptr;
	}

	inventoryList_.clear();
}

void ShopState::addToInventory(Item* ob)
{
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_, Vector2D(300, 400), Vector2D(50, 50), ob, callSelectObjectS);
	//Añadimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = inventoryList_.insert(inventoryList_.end(), b);
	b->setIterator(it);
	//comprobamos si es el primer objeto de la lista
	if (it == inventoryList_.begin()) {
		ListPos = inventoryList_.begin();//iniciamos el puntero
	}
}

void ShopState::draw() const
{
	GameState::draw();//dibujamos todos los botones normales
	//Despues dibujaremos SOLO los botones de la lista que salen por pantalla
	if (!inventoryList_.empty()) {
		list<InventoryButton*>::iterator aux = ListPos;
		InventoryButton* auxOb = nullptr;
		// posiciones estandar de los botones
		int x = 700;
		int y = 200;
		int i = 0;
		//dibujamos los objetos de la primera columna
		while (i < VIEW_LIST / 2 && aux != inventoryList_.end()) {
			//#ifdef _DEBUG
			//		cout << "entramos en el bucle" << endl;
			//#endif
			auxOb = *aux;
			auxOb->setPos(Vector2D{ double(x),double(y + (i * 100)) });
			auxOb->draw();//desreferenciamos el puntero
			aux++;
			i++;
		}
		//dibujamos los objetos de la segunda colmna
		int j = 0;
		while (j < VIEW_LIST / 2 && aux != inventoryList_.end()) {
			auxOb = *aux;
			auxOb->setPos(Vector2D{ double(x + 100),double(y + (j * 100)) });
			auxOb->draw();//desreferenciamos el puntero
			aux++;
			j++;
		}
	}
	if(!shopList_.empty())
	{
		list<InventoryButton*>::iterator aux = shopListPos;
		InventoryButton* auxOb = nullptr;
		// posiciones estandar de los botones
		int x = 200;
		int y = 200;
		int i = 0;
		//dibujamos los objetos de la primera columna
		while (i < SHOP_VIEW_LIST / 2 && aux != shopList_.end()) {
			auxOb = *aux;
			auxOb->setPos(Vector2D{ double(x),double(y + (i * 100)) });
			auxOb->draw();//desreferenciamos el puntero
			aux++;
			i++;
		}
		//dibujamos los objetos de la segunda colmna
		int j = 0;
		while (j < SHOP_VIEW_LIST / 2 && aux != shopList_.end()) {
			auxOb = *aux;
			auxOb->setPos(Vector2D{ double(x + 100),double(y + (j * 100)) });
			auxOb->draw();//desreferenciamos el puntero
			aux++;
			j++;
		}
	}
}

void ShopState::update()
{
	//Comprobamos si la lista del inventario no esta vacia, si no lo esta se actualizan los objetos de la lista
	if (!inventoryList_.empty()) 
	{
		list<InventoryButton*>::iterator aux = ListPos;
		InventoryButton* auxOb = nullptr;
		int i = 0;
		//Actualizaremos SOLO los botones de la lista que salen por pantalla
		while (i < VIEW_LIST && aux != inventoryList_.end()) 
		{
			auxOb = *aux;
			auxOb->update();//desreferenciamos el puntero
			aux++;
			i++;
		}
	}

	if (!shopList_.empty()) 
	{
		list<InventoryButton*>::iterator aux = shopListPos;
		InventoryButton* auxOb = nullptr;
		int i = 0;
		//Actualizaremos SOLO los botones de la lista que salen por pantalla
		while (i < SHOP_VIEW_LIST && aux != shopList_.end()) 
		{
			auxOb = *aux;
			auxOb->update();//desreferenciamos el puntero
			aux++;
			i++;
		}
	}
	//Actualizamos los objetos normales
	GameState::update();
}

void ShopState::selectObject(InventoryButton* ob)
{
	select_ = ob;
}

void ShopState::sellObj()
{
	if (select_ != nullptr && select_->getId() == 0)
	{
		if (select_->getIterator() == ListPos)++ListPos;
		select_->Enable(true);
		gm_->addInventoryGold(select_->getObject()->getPrice());
		inventoryList_.erase(select_->getIterator());
		delete select_;
		select_ = nullptr;
	}
}

void ShopState::deleteObj()
{
	inventoryList_.erase(select_->getIterator());

	//Eliminamos el objeto
	delete select_;
	select_ = nullptr;
}

//boton que avanza en la lista para mostrar los siguientes elementos, en este caso avazara el iterador
void ShopState::forwardList() {
	int aux = advanced;
	aux += 1;
	if ((aux * VIEW_LIST) <= inventoryList_.size()) {
		advanced = aux;
		advance(ListPos, VIEW_LIST);//avanzamos el iterador
	}
}
//metodo para retroceder en la lista del inventario
void ShopState::backList() {
	int aux = advanced;
	aux -= 1;
	if ((aux * VIEW_LIST) >= 0) {
		advanced = aux;
		advance(ListPos, -VIEW_LIST);//retrocedemos el iterador
	}
}

void ShopState::addToShop(Equipment* ob)
{
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_, Vector2D{ 300,400 }, Vector2D{ 50,50 }, ob, callSelectObjectS, false, 1);
	//Añadimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = shopList_.insert(shopList_.end(), b);
	b->setIterator(it);
	//comprobamos si es el primer objeto de la lista
	if (it == shopList_.begin()) {
		shopListPos = shopList_.begin();//iniciamos el puntero
	}
}

void ShopState::buyObj()
{
	if (select_ != nullptr && gm_->getInventoryGold() >= select_->getObject()->getPrice() && select_->getId() == 1)
	{
		if (select_->getIterator() == shopListPos)++shopListPos;
		select_->Enable(true);
		gm_->addInventoryGold(-select_->getObject()->getPrice());
		addToInventory(select_->getObject());
		shopList_.erase(select_->getIterator());
	}
}

void ShopState::ShopForwardList()
{
	int aux = shopAdvanced;
	aux += 1;
	if ((aux * SHOP_VIEW_LIST) <= shopList_.size()) {
		shopAdvanced = aux;
		advance(shopListPos, SHOP_VIEW_LIST);//avanzamos el iterador
	}
}

void ShopState::ShopBackList()
{
	int aux = shopAdvanced;
	aux -= 1;
	if ((aux * SHOP_VIEW_LIST) >= 0) {
		shopAdvanced = aux;
		advance(shopListPos, -SHOP_VIEW_LIST);//retrocedemos el iterador
	}
}
