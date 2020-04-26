#pragma once
#include "GameState.h"
#include <list>

class InventoryButton;

class ShopState :
	public GameState
{
private:
	Texture* background_;
	list<InventoryButton*> inventoryList_;
	Button* sellButton_; // boton para vender un elemento del inventario
	Button* buyButton_; // boton para equipar un elemento al jugador
	Button* advanceButton_; // boton para que se muestren los siguientes elementos de la lista
	Button* gobackButton_; // boton para que se muestren los anteriores elementos de la lista
	Button* exitButton_; // boton para volver al estado anterior
	Button* shopAdvanceButton_;
	Button* shopGobackButton_;
	InventoryButton* select_ = nullptr;//Guarda La referencia al elemento seleccionado
	list<InventoryButton*>::iterator ListPos;//Guarda la posicion de la lista que se muestra por pantalla
	const int  VIEW_LIST = 6; //variable que guarda el numero de onjetos que se va a mostrar a la vez por pantalla
	int advanced = 0;//Complamentario a listPos, gurda cuantas veces se ha avanzado o retrocedido en la lista,para actualizar el iterador
	Player* player_;

	list<InventoryButton*> shopList_;
	list<InventoryButton*>::iterator shopListPos;
	int shopAdvanced = 0;
	const int  SHOP_VIEW_LIST = 10;

	void initState() {};

public:
	ShopState(Application* app, Player* player = nullptr);
	virtual ~ShopState();
	void addToInventory(Item* ob);
	virtual void draw() const;
	virtual void update();
	void selectObject(InventoryButton* ob);
	void sellObj();
	void deleteObj();
	void forwardList();
	void backList();

	void addToShop(Equipment* ob);
	void buyObj();
	void ShopForwardList();
	void ShopBackList();
};

