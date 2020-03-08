#include "Inventory.h"


Inventory::Inventory(Application* app = nullptr) :GameState(app) {
	deleteButton_ = new Button(texture, Vector2D{ 300,400 }, Vector2D{ 50,50 },deleteObj);
	addUpdateList(deleteButton_);
	addRenderList(deleteButton_);
	equippedButton_ = new Button(texture, Vector2D{ 300,400 }, Vector2D{ 50,50 },equippedObj);
	addUpdateList(equippedButton_);
	addRenderList(equippedButton_);

}
void Inventory::selectObject(InventoryButton* ob) {
	sellect_ = ob;
	printInformation();//este metodo todabia no hace nada

}

void Inventory::equippedObj() {
	if (sellect_ != nullptr) {
		
		if (typeid(*sellect_->getObject()) == typeid(helmet)) {
			if (equipment_.helmet_ != nullptr) {
				InventoryButton* aux = equipment_.helmet_;
				list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), aux);
				aux->setIterator(it);
			}
			equipment_.helmet_ = sellect_;
			
		}
		//else if()...

		sellect_->Enable(true);
		sellect_->getObject()->OnEnabled();
		InventoryList_.erase(sellect_->getIterator());

	}

}
void Inventory::deleteObj() {
	if (sellect_ != nullptr) {
		if (sellect_->isEquipped()) {
			if (typeid(*sellect_->getObject()) == typeid(helmet)) {
				equipment_.helmet_ = nullptr;
				
			}
			//etc

			
		}
		else {InventoryList_.erase(sellect_->getIterator());}

		delete sellect_;
		sellect_ = nullptr;
	}
}

void Inventory::addToInventory(Equipable* ob) {
	InventoryButton* b = new InventoryButton(texture, Vector2D{ 300,400 }, Vector2D{ 50,50 }, selectObject);
	list <InventoryButton*>::iterator it = InventoryList_.insert(InventoryList_.end(), b);
	b->setIterator(it);


}
