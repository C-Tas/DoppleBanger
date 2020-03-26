#include "Inventory.h"
#include "Equipment.h"
//includes de prueba
//#include "Gloves.h"
#include "Player.h"
using namespace std;
//callbacks
//void callSelectObject(GameState* state, InventoryButton* button) {
//	dynamic_cast<Inventory*>(state)->selectObject(button);
//}

void callSelectObject(GameState * state, InventoryButton* but) {
		dynamic_cast<Inventory*>(state)->selectObject(but);
	}
void callDeleteObject(GameState* state) {
	dynamic_cast<Inventory*>(state)->deleteObj();
}
void callEquipedObject(GameState* state) {
	dynamic_cast<Inventory*>(state)->equippedObj();
}
void callForwardList(GameState* state) {
	dynamic_cast<Inventory*>(state)->forwardList();
}
void callBackList(GameState* state) {
	dynamic_cast<Inventory*>(state)->backList();
}
void callExit(Application* app){
	app->getStateMachine()->popState();
}

Inventory::Inventory(Application* app, Player* player) :GameState(app), player_(player) {
	deleteButton_ = new Button(app, dynamic_cast<GameState*>(this),app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 50,500 }, Vector2D{ 50,50 },callDeleteObject);
	addUpdateList(deleteButton_);
	addRenderList(deleteButton_);
	equippedButton_ = new Button(app, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 50,700 }, Vector2D{ 50,50 },callEquipedObject);
	addUpdateList(equippedButton_);
	addRenderList(equippedButton_);
	advanceButton_ = new Button(app,this,app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 700,100 }, Vector2D{ 50,50 }, callForwardList);
	addUpdateList(advanceButton_);
	addRenderList(advanceButton_);
	gobackButton_ = new Button(app, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 500,100 }, Vector2D{ 50,50 }, callBackList);
	addUpdateList(gobackButton_);
	addRenderList(gobackButton_);
	exitButton_= new Button(app, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 1300,100 }, Vector2D{ 50,50 }, callExit);
	addUpdateList(exitButton_);
	addRenderList(exitButton_);

	//Cogemos la lista de objetos del gameManager
	GameManager* gameManager_ = GameManager::instance();
	inventoryList_ = gameManager_->getInventory();
	//Cogemos los objetos equpados de player
	playerEquipment aux = player_->getInfoEquip();

	if (aux.armor_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.armor_, callSelectObject);
	if (aux.boots_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.boots_, callSelectObject);
	if (aux.gloves_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.gloves_, callSelectObject);
	if (aux.gun_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.gun_, callSelectObject);
	if (aux.sword_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.sword_, callSelectObject);
	if (aux.potion1_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.potion1_, callSelectObject);
	if (aux.potion2_ != nullptr) equipment_.armor_ = new InventoryButton(app_, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 }, aux.potion2_, callSelectObject);

	#ifdef _DEBUG
	cout << "creamos el objeto" << endl;
	string nombre = "guantes1";
	string desc = "duantes1";
	
	Gloves* guante0 = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);
	Gloves* guante1 = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);
	Gloves* guante2 = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);
	Gloves* guante3 = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);
	Gloves* guante4 = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);
	Gloves* guante5= new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);
	Gloves* guante6= new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), nombre, desc, 20.0, 10, 10);

	addToInventory(guante0);
	addToInventory(guante1);
	addToInventory(guante2);
	addToInventory(guante3);
	addToInventory(guante4);
	addToInventory(guante5);
	addToInventory(guante6);

	#endif

}
void Inventory::selectObject(InventoryButton* ob) {
	select_ = ob;
	printInformation();//este metodo todabia no hace nada

}

void Inventory::equippedObj() {
	//comprobamos si hay un objeto seleccionado y que no se trate de un objeto ya equipado
	if (select_ != nullptr && !select_->isEquipped()) {
		//comprobamos si se trata de un equipment
		if (typeid(*select_->getObject()) == typeid(Equipment)) {

			//comprobamos de que tipo es
			if (typeid(*select_->getObject()) == typeid(Gloves)) {
				equiparAux(equipment_.gloves_);
				player_->equip(static_cast<Gloves*>(select_->getObject()));

			}
			else if (typeid(*select_->getObject()) == typeid(Armor)) {
				equiparAux(equipment_.armor_);
				player_->equip(static_cast<Armor*>(select_->getObject()));
			}
			else if (typeid(*select_->getObject()) == typeid(Sword)) {
				equiparAux(equipment_.sword_);
				player_->equip(static_cast<Sword*>(select_->getObject()));
			}
			else if (typeid(*select_->getObject()) == typeid(Boots)) {
				equiparAux(equipment_.boots_);
				player_->equip(static_cast<Boots*>(select_->getObject()));
			}
			else if (typeid(*select_->getObject()) == typeid(Gun)) {
				equiparAux(equipment_.gun_);
				player_->equip(static_cast<Gun*>(select_->getObject()));
			}

			select_->Enable(true);
			select_->getObject()->equip(player_);
			inventoryList_->erase(select_->getIterator());
		}
		//si se trata de un usable
		else {
			equipPotionAux();
			select_->Enable(true);
			inventoryList_->erase(select_->getIterator());

		}
		
		
		// Una vez Equipado el nuevo objeto, lo activamos y lo eliminamos de la lista
		select_->Enable(true);
		select_->getObject()->equip(player_);
		inventoryList_->erase(select_->getIterator());

	}

}
void Inventory::deleteObj() {
	//Comprobamos si hay algun elemento seleccionado
	if (select_ != nullptr) {
		// comprobamos que no se trate de un elemento equipado
		if (!select_->isEquipped()) {
			
			if (select_->getIterator() == ListPos)++ListPos;
			inventoryList_->erase(select_->getIterator());
			//Eliminamos el objeto
			delete select_;
			select_ = nullptr;

		}
		//lo borramos de la lista
		
	}
}

void Inventory::addToInventory(Equipment* ob) {
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_,this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 },ob, callSelectObject);
	//le asignamos al objeto su boton
	//Añadimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = inventoryList_->insert(inventoryList_->end(), b);
	b->setIterator(it);
	//comprobamos si es el primer objeto de la lista
	if (it == inventoryList_->begin()) {
		ListPos = inventoryList_->begin();//iniciamos el puntero
	}


}

// este metodo desequipa el objeto si esta equipado y equipa el nuevo objeto
void Inventory::equiparAux(InventoryButton* &but) {
	//Si ya hay un objeto equipado
	if (but != nullptr) {
	//desequipamos el objeto actual

		
		but->getObject()->remove(player_);
		but->Enable(false);
		InventoryButton* aux = but;
		//El objeto desequipado lo devolvemos al final de la lista
		list <InventoryButton*>::iterator it = inventoryList_->insert(inventoryList_->end(), aux);
		aux->setIterator(it);
	}
	//equipamos el nuevo objeto
	but= select_; 
}
void Inventory::equipPotionAux() {
	//Si ya hay un objeto equipado
	if (equipment_.potion1_ == nullptr) {
		
		equipment_.potion1_ = select_;
		player_->equipPotion1(static_cast<usable*>(select_->getObject()));
	
	}
	else if (equipment_.potion2_ == nullptr) {
		equipment_.potion2_ = select_;
		player_->equipPotion2(static_cast<usable*>(select_->getObject()));
	}
	
}

//boton que avanza en la lista para mostrar los siguientes elementos, en este caso avazara el iterador
void Inventory::forwardList() {
	int aux = advanced;
	aux += 1;
	if ((aux * VIEW_LIST)<= inventoryList_->size()){
		advanced = aux;
		advance(ListPos, VIEW_LIST);//avanzamos el iterador
	}

}
//metodo para retroceder en la lista del inventario
void Inventory::backList() {
	int aux = advanced;
	aux -= 1;
	if ((aux * VIEW_LIST) >= 0) {
		advanced = aux;
		advance(ListPos, -VIEW_LIST);//retrocedemos el iterador
	}
}
void Inventory::draw()const {
//#ifdef _DEBUG
//	cout << "entramos en draw" << endl;
//#endif
	GameState::draw();//dibujamos todos los botones normales
	//Despues dibujaremos SOLO los botones de la lista que salen por pantalla
	if (!inventoryList_->empty()) {
		list<InventoryButton*>::iterator aux = ListPos;
		InventoryButton* auxOb = nullptr;
		// posiciones estandar de los botones
		int x = 700;
		int y = 200;
		int i = 0;
		//dibujamos los objetos de la primera columna
		while (i < VIEW_LIST / 2 && aux != inventoryList_->end()) {
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
		while (j < VIEW_LIST / 2 && aux != inventoryList_->end()) {
			auxOb = *aux;
			auxOb->setPos(Vector2D{ double(x + 100),double(y + (j * 100)) });
			auxOb->draw();//desreferenciamos el puntero
			aux++;
			j++;
		}
	}
	

	if (equipment_.gloves_ != nullptr) {
		equipment_.gloves_->setPos(Vector2D{ 500.0,500.0 });
		equipment_.gloves_->draw();
	}
	//todos los botones...
	

}
void Inventory::update() {
	//Actualizamos los objetos normales
	GameState::update();
	//comprobamos si la lista del inventario no esta vacia, si no lo esta se actualizan los objetos de la lista
	if (!inventoryList_->empty()) {
		list<InventoryButton*>::iterator aux = ListPos;
		InventoryButton* auxOb = nullptr;
		int i = 0;
		//Actualizaremos SOLO los botones de la lista que salen por pantalla
		while(i < VIEW_LIST && aux!= inventoryList_->end()){
			auxOb = *aux;
			auxOb->update();//desreferenciamos el puntero
			aux++;
			i++;
		}
	}
	if (equipment_.gloves_ != nullptr) {
		equipment_.gloves_->update();
	}
	if (equipment_.armor_ != nullptr) {
		equipment_.armor_->update();
	}
	if (equipment_.boots_ != nullptr) {
		equipment_.boots_->update();
	}
	if (equipment_.gun_ != nullptr) {
		equipment_.gun_->update();
	}
	
	if (equipment_.sword_ != nullptr) {
		equipment_.sword_->update();
	}
	if (equipment_.potion1_ != nullptr) {
		equipment_.potion1_->update();
	}
	if (equipment_.potion2_ != nullptr) {
		equipment_.potion2_->update();
	}

	

}






