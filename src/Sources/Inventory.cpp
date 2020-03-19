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

void callSelectObject(GameState * state, Equipment* ob) {
		dynamic_cast<Inventory*>(state)->selectObject(ob->getButton());
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

Inventory::Inventory(Application* app) :GameState(app) {
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

	#ifdef _DEBUG
	cout << "creamos el objeto" << endl;
	string nombre = "guantes1";
	string desc = "duantes1";
	Player* player = nullptr;
	
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
	//comprobamos si hay un objeto seleccionado
	if (select_ != nullptr) {
		//comprobamos de que tipo es
		if (typeid(*select_->getObject()) == typeid(Gloves)) {
			equiparAux(equipment_.gloves_);
		}
		else if (typeid(*select_->getObject()) == typeid(Armor)) {
			equiparAux(equipment_.armor_);
		}
		else if (typeid(*select_->getObject()) == typeid(Sword)) {
			equiparAux(equipment_.sword_);
		}
		else if (typeid(*select_->getObject()) == typeid(Boots)) {
			equiparAux(equipment_.boots_);
		}
		else if (typeid(*select_->getObject()) == typeid(Gun)) {
			equiparAux(equipment_.gun_);
		}
		
		// Una vez Equipado el nuevo objeto, lo activamos y lo eliminamos de la lista
		select_->Enable(true);

		//Recibe player
		//select_->getObject()->equip();
		InventoryList_.erase(select_->getIterator());

	}

}
void Inventory::deleteObj() {
	//Comprobamos si hay algun elemento seleccionado
	if (select_ != nullptr) {
		// comprobamos si se trata de un objeto equipado o de uno de la lista
		if (select_->isEquipped()) {
			//comprobamos de que tipo es
			if (typeid(*select_->getObject()) == typeid(Gloves)) {
				equipment_.gloves_ = nullptr;
			}
			else if (typeid(*select_->getObject()) == typeid(Armor)) {
				equipment_.armor_ = nullptr;
			}
			else if (typeid(*select_->getObject()) == typeid(Sword)) {
				equipment_.sword_ = nullptr;
			}
			else if (typeid(*select_->getObject()) == typeid(Boots)) {
				equipment_.boots_ = nullptr;
			}
			else if (typeid(*select_->getObject()) == typeid(Gun)) {
				equipment_.gun_ = nullptr;
			}

		}
		//lo borramos de la lista
		else {InventoryList_.erase(select_->getIterator());}
		//Eliminamos el objeto
		delete select_;
		select_ = nullptr;
	}
}

void Inventory::addToInventory(Equipment* ob) {
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_,this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 },ob, callSelectObject);
	//le asignamos al objeto su boton
	ob->setButton(b);
	//Añadimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), b);
	b->setIterator(it);
	//comprobamos si es el primer objeto de la lista
	if (it == InventoryList_.begin()) {
		ListPos = InventoryList_.begin();//iniciamos el puntero
	}


}

// este metodo desequipa el objeto si esta equipado y equipa el nuevo objeto
void Inventory::equiparAux(InventoryButton* &but) {
	//Si ya hay un objeto equipado
	if (but != nullptr) {
	//desequipamos el objeto actual

		//Recibe player
		//but->getObject()->remove();
		but->Enable(false);
		InventoryButton* aux = but;
		//El objeto desequipado lo devolvemos al final de la lista
		list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), aux);
		aux->setIterator(it);
	}
	//equipamos el nuevo objeto
	but= select_; 
}

//boton que avanza en la lista para mostrar los siguientes elementos, en este caso avazara el iterador
void Inventory::forwardList() {
	int aux = advanced;
	aux += 1;
	if ((aux * VIEW_LIST)<= InventoryList_.size()){
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
	if (!InventoryList_.empty()) {
		list<InventoryButton*>::iterator aux = ListPos;
		InventoryButton* auxOb = nullptr;
		// posiciones estandar de los botones
		int x = 700;
		int y = 200;
		int i = 0;
		//dibujamos los objetos de la primera columna
		while (i < VIEW_LIST / 2 && aux != InventoryList_.end()) {
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
		while (j < VIEW_LIST / 2 && aux != InventoryList_.end()) {
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
	if (!InventoryList_.empty()) {
		list<InventoryButton*>::iterator aux = ListPos;
		InventoryButton* auxOb = nullptr;
		int i = 0;
		//Actualizaremos SOLO los botones de la lista que salen por pantalla
		while(i < VIEW_LIST && aux!= InventoryList_.end()){
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

	

}






