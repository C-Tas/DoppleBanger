#pragma once
#include "GameState.h"
#include <list>

enum class BelongingList: int {Stash, Inventory};

struct SelectedElement {
	BelongingList list;
	InventoryButton buttonSelected;
};

class StashState :
	public GameState
{
private:
	///<summary>Puntero a la lista del alijo del gameManager</summary>
	list<InventoryButton*> stash_;
	///<summary>Puntero a la lista del inventario del gameManager</summary>
	list<InventoryButton*> inventory_;
	///<summary>Textura del fondo del estado</summary>
	Texture* background_;

	///<summary>Método para inicializar el estado. Se le llama desde la constructora</summary>
	void initState();

	///<summary>Número de elementos del inventario que se ven por pantalla</summary>
	const int INVENTORY_VISIBLE_ELEMENTS = 8;
	///<summary>"Página" del inventario en la que nos encontramos (es decir, en la que están los objetos del inventario que vemos)</summary>
	int inventoryPage_ = 0;
	///<summary>Iterador al primer elemento de la lista del la página del inventario en la que nos encontramos</summary>
	list<InventoryButton*>::iterator inventoryPos_;

	///<summary>Número de elementos del alijo que se ven por pantalla</summary>
	const int STASH_VISIBLE_ELEMENTS = 8;
	///<summary>"Página" del alijo en la que nos encontramos (es decir, el la que están los objetos del alijo que vemos)</summary>
	int stashPage_ = 0;
	///<summary>Iterador al primer elemento de la lista del la página del alijo en la que nos encontramos</summary>
	list<InventoryButton*>::iterator stashPos_;

	///Métodos privados auxiliares para los callbacks
	void advanceInventoryPage();
	void previousInventoryPage();
	void advanceStashPage();
	void previousStashPage();

public:
	///<summary>Constructora del StashState</summary>
	StashState(Application* app = nullptr) : GameState(app) { initState(); };
	///<summary>Detsructora</summary>
	virtual ~StashState() { background_ = nullptr; };

	///<summary>Callbacks para los botones (Cambio de estado)</summary>
	static void backToPrevious(Application* app);

	//<summary>Callbacks para cambiar elementos de este estado</summary>
	static void callbackAdvanceInventoryPage(GameState* state);
	static void callbackPreviousInventoryPage(GameState* state);
	static void callbackAdvanceStashPage(GameState* state);
	static void callbackPreviousStashPage(GameState* state);

};

