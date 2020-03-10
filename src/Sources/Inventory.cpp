#include "Inventory.h"
//callbacks
void callSelectObject(GameState* state, InventoryButton* button) {
	dynamic_cast<Inventory*>(state)->selectObject(button);
}

void callDeleteObject(GameState* state) {
	dynamic_cast<Inventory*>(state)->deleteObj();
}
void callEquipedObject(GameState* state) {
	dynamic_cast<Inventory*>(state)->equippedObj();
}

Inventory::Inventory(Application* app = nullptr) :GameState(app) {
	deleteButton_ = new Button(dynamic_cast<GameState*>(this),texture, Vector2D{ 300,400 }, Vector2D{ 50,50 },callDeleteObject);
	addUpdateList(deleteButton_);
	addRenderList(deleteButton_);
	equippedButton_ = new Button(this,texture, Vector2D{ 300,400 }, Vector2D{ 50,50 },callEquipedObject);
	addUpdateList(equippedButton_);
	addRenderList(equippedButton_);

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

void Inventory::addToInventory(Equipable* ob) {
	InventoryButton* b = new InventoryButton(this,texture, Vector2D{ 300,400 }, Vector2D{ 50,50 }, callSelectObject);
	list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), b);
	b->setIterator(it);


}

// este metodo desequipa el objeto si esta equipado y equipa el nuevo objeto
void Inventory::equiparAux(InventoryButton* but) {
	if (but != nullptr) {
		but->getObject()->OnDisabled();
		but->Enable(false);
		InventoryButton* aux = but;
		list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), aux);
		aux->setIterator(it);
	}
	but= select_; 
}


