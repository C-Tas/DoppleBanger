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
	Button* deleteButton_;		// boton para eliminar un elemento del inventario
	Button* equippedButton_;	// boton para equipar un elemento al jugador
	Button* advanceButton_;		// boton para que se muestren los siguientes elementos de la lista
	Button* gobackButton_;		// boton para que se muestren los anteriores elementos de la lista
	Button* exitButton_;		// boton para volver al estado anterior
	Button* goToSkillsButton_;	//boton para ir al menu de habilidades
	
	InventoryButton* select_ = nullptr;			//Guarda La referencia al elemento seleccionado
	list<InventoryButton*>:: iterator ListPos;	//Guarda la posicion de la lista que se muestra por pantalla
	Equipments equipment_;						//struct que tiene el equipamiento en el ivnentario
	const int  VIEW_LIST = 6;					//variable que guarda el numero de onjetos que se va a mostrar a la vez por pantalla
	int advanced = 0;							//Complamentario a listPos, gurda cuantas veces se ha avanzado o retrocedido en la lista,para actualizar el iterador
	Player* player_ = nullptr;

	virtual void initState();

	//metodos privados
	void printInformation() {};
	void printPlayerInfo(){};
	//Selecciona el tipo de Equipamiento qu� es
	void selectEquipment();
	//Cambia el tipo del equipo por otro nuevo
	void changeEquipment(InventoryButton* &but);
	//Equipa una pocion
	int slotPotion = 0;	//Para saber en que posicion colocar la nueva pocion
	void equipPotion();
public:
	Inventory(Application* app) :GameState(app) { initState(); };
	virtual ~Inventory() ;
	virtual void draw() const;
	virtual void update();
	//Selecciona el objeto clickado
	void selectObject(InventoryButton* ob);
	//Equipa un objeto
	void equipObject();
	//Elimina un objeto del inventario
	void deleteObj();
	//Itera hacia la siguiente pagina de la lista
	void forwardList();
	//Itera hacia la anterior pagina de la lista
	void backList();

};