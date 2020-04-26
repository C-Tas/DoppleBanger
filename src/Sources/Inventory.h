#pragma once
#include "GameState.h"
#include <list>

class InventoryButton;
using namespace std;

struct Equipments
{
	InventoryButton* armor_ = nullptr;
	InventoryButton* boots_ = nullptr;
	InventoryButton* gloves_ = nullptr;
	InventoryButton* sword_ = nullptr;
	InventoryButton* gun_ = nullptr;
	InventoryButton* potion1_ = nullptr;
	InventoryButton* potion2_ = nullptr;
};

class Inventory: public GameState
{
private:
	Texture* background_ ;
	list<InventoryButton*>* inventoryList_;
	Button* deleteButton_;// boton para eliminar un elemento del inventario
	Button* equippedButton_; // boton para equipar un elemento al jugador
	Button* advanceButton_; // boton para que se muestren los siguientes elementos de la lista
	Button* gobackButton_; // boton para que se muestren los anteriores elementos de la lista
	Button* exitButton_; // boton para volver al estado anterior
	Button* goToSkillsButton_;
	
	InventoryButton* select_ = nullptr;//Guarda La referencia al elemento seleccionado
	list<InventoryButton*>:: iterator ListPos;//Guarda la posicion de la lista que se muestra por pantalla
	Equipments equipment_;
	const int  VIEW_LIST = 6; //variable que guarda el numero de onjetos que se va a mostrar a la vez por pantalla
	int advanced = 0;//Complamentario a listPos, gurda cuantas veces se ha avanzado o retrocedido en la lista,para actualizar el iterador
	Player* player_ = nullptr;

	virtual void initState() {};

	//const int MAX_OBJECTS;

	//metodos privados
	
	void printInformation() {};
	void printPlayerInfo(){};
	void equiparAux(InventoryButton* &but);
	void equipPotionAux();
	
	
	
public:
	Inventory(Application* app );
	virtual ~Inventory() ;
	void addToInventory(Equipment* ob);
	virtual void draw() const;
	virtual void update();
	void selectObject(InventoryButton* ob);
	void equippedObj();
	void deleteObj();
	void forwardList();
	void backList();
};

