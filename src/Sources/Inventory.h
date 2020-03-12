#pragma once
#include "InventoryButton.h"
#include "GameState.h"
#include <list>
using namespace std;
struct Equipments
{
	InventoryButton* helmet_ = nullptr;
	InventoryButton* armor_ = nullptr;
	InventoryButton* boots_ = nullptr;
	InventoryButton* gloves_ = nullptr;
	InventoryButton* sword_ = nullptr;
	InventoryButton* gun_ = nullptr;

};


class Inventory: public GameState
{
private:
	Texture* background_;
	Texture* texture;//provisional
	list<InventoryButton*> InventoryList_;
	list<int> AuxList_;
	Button* deleteButton_;// boton para eliminar un elemento del inventario
	Button* equippedButton_; // boton para equipar un elemento al jugador
	Button* advanceButton_; // boton para que se muestren los siguientes elementos de la lista
	Button* gobackButton_; // boton para que se muestren los anteriores elementos de la lista
	Button* ExitButton_; // boton para volver al estado anterior
	
	InventoryButton* select_ = nullptr;
	list<InventoryButton>:: iterator ListPos;
	Equipments equipment_;
	const int  VIEW_LIST = 6; //variable que guarda el numero de onjetos que se va a mostrar a la vez por pantalla
	int advanced = 0;
	//const int MAX_OBJECTS;

	//metodos privados
	
	void printInformation() {};
	void equiparAux(InventoryButton* but);
	
	
	
public:
	Inventory(Application* app = nullptr);
	void addToInventory(Equipment* ob);
	const virtual void draw() ;//Métodos que faltan por definir y por eso dan fallo de link
	virtual void update() {};//Métodos que faltan por definir y por eso dan fallo de link
	void selectObject(InventoryButton* ob);
	void equippedObj();
	void deleteObj();
	void forwardList();
	void backList();
	

	

	

};

