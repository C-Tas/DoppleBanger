#include "Inventory.h"
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

Inventory::Inventory(Application* app) :GameState(app) {
	deleteButton_ = new Button(app, dynamic_cast<GameState*>(this),app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 600,400 }, Vector2D{ 50,50 },callDeleteObject);
	addUpdateList(deleteButton_);
	addRenderList(deleteButton_);
	equippedButton_ = new Button(app, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 },callEquipedObject);
	addUpdateList(equippedButton_);
	addRenderList(equippedButton_);
	advanceButton_ = new Button(app,this,app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 600,100 }, Vector2D{ 50,50 }, callForwardList);
	addUpdateList(advanceButton_);
	addRenderList(advanceButton_);
	gobackButton_ = new Button(app, this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 500,100 }, Vector2D{ 50,50 }, callBackList);
	addUpdateList(gobackButton_);
	addRenderList(gobackButton_);
	#ifdef _DEBUG
	cout << "creamos el objeto" << endl;
	addToInventory(nullptr);

	#endif

}
void Inventory::selectObject(InventoryButton* ob) {
	select_ = ob;
	printInformation();//este metodo todabia no hace nada

}

void Inventory::equippedObj() {
	////comprobamos si hay un objeto seleccionado
	//if (sellect_ != nullptr) {
	//	//comprobamos de que tipo es
	//	if (typeid(*sellect_->getObject()) == typeid(helmet)) {
	//		equiparAux(equipment_.helmet_);
	//	}
	//	else if (typeid(*sellect_->getObject()) == typeid(boots)) {
	//		equiparAux(equipment_.boots_);
	//	}

	//	// Una vez Equipado el nuevo objeto, lo activamos y lo eliminamos de la lista
	//	sellect_->Enable(true);
	//	sellect_->getObject()->OnEnabled();
	//	InventoryList_.erase(sellect_->getIterator());

	//}

}
void Inventory::deleteObj() {
	////Comprobamos si hay algun elemento seleccionado
	//if (sellect_ != nullptr) {
	//	// comprobamos si se trata de un objeto equipado o de uno de la lista
	//	if (sellect_->isEquipped()) {
	//		//comprobamos de que tipo es
	//		if (typeid(*sellect_->getObject()) == typeid(helmet)) {
	//			equipment_.helmet_ = nullptr;
	//			
	//		}
	//		//etc aun no existe ningun objeto

	//		
	//	}
	//	//lo borramos de la lista
	//	else {InventoryList_.erase(sellect_->getIterator());}
	//	//Eliminamos el objeto
	//	delete sellect_;
	//	sellect_ = nullptr;
	//}
}

void Inventory::addToInventory(Equipment* ob) {
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_,this, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D{ 300,400 }, Vector2D{ 50,50 },ob, callSelectObject);
	//le asignamos al objeto su boton
	//ob->setButton(b);
	//Añadimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), b);
	b->setIterator(it);
	//comprobamos si es el primer objeto de la lista
	if (it == InventoryList_.begin()) {
		ListPos = InventoryList_.begin();//iniciamos el puntero
	}


}

// este metodo desequipa el objeto si esta equipado y equipa el nuevo objeto
void Inventory::equiparAux(InventoryButton* but) {
	//Si ya hay un objeto equipado
	/*if (but != nullptr) {
	//desequipamos el objeto actual
		but->getObject()->OnDisabled();
		but->Enable(false);
		InventoryButton* aux = but;
		//El objeto desequipado lo devolvemos al final de la lista
		list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), aux);
		aux->setIterator(it);
	}
	//equipamos el nuevo objeto
	but= select_; */
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
	if ((aux * VIEW_LIST) <= 1) {
		advanced = aux;
		advance(ListPos, -VIEW_LIST);//retrocedemos el iterador
	}

}

void Inventory::draw()const {
#ifdef _DEBUG
	cout << "entramos en draw" << endl;
#endif
	GameState::draw();//dibujamos todos los botones normales
	//Despues dibujaremos SOLO los botones de la lista que salen por pantalla
	list<InventoryButton*>::iterator aux = ListPos;
	InventoryButton* auxOb = nullptr;
	// posiciones estandar de los botones
	int x = 900; 
	int y = 100;
	int i = 0;
	//dibujamos los objetos de la primera columna
	while (i < VIEW_LIST/2 && aux != InventoryList_.end()) {
#ifdef _DEBUG
		cout << "entramos en el bucle" << endl;
#endif
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
		auxOb->setPos(Vector2D{ double(x + 100),double(y + (i * 100)) });
		auxOb->draw();//desreferenciamos el puntero
		aux++;
		j++;
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
	//todos los botones...

}




