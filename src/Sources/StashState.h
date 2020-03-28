#pragma once
#include "GameState.h"
#include <list>


///<summary>Contenedor de la información tanto del alijo como del inventario</summary>
struct Container {
	///<summary>Lista con los objetos del inventario o del alijo</summary>
	list<InventoryButton*>* objects_;
	///<summary>"Página" del inventario en la que nos encontramos(es decir, en la que están los objetos del inventario que vemos en la interfaz)</summary>
	int page_ = 0;
};

class StashState :
	public GameState
{
private:
	///<summary>Contenedor con la información del alijo</summary>
	Container stash_;
	//<summary>Contenedor con la información del inventario</summary>
	Container inventory_;
	///<summary>Textura del fondo del estado</summary>
	Texture* background_;
	///<summary>Puntero al boton seleccionado</summary>
	InventoryButton* selected_ = nullptr;

	///<summary>Método para inicializar el estado. Se le llama desde la constructora</summary>
	void initState();

	///<summary>Número de elementos del inventario que se ven por pantalla</summary>
	const int INVENTORY_VISIBLE_ELEMENTS = 2;
	///<summary>Número de elementos del alijo que se ven por pantalla</summary>
	const int STASH_VISIBLE_ELEMENTS = 2;

	///Métodos privados auxiliares para los callbacks
	void advanceInventoryPage();
	void previousInventoryPage();
	void advanceStashPage();
	void previousStashPage();
	void selectObject(InventoryButton* button);
	void changeBetweenLists();

	///<summary>Método privado para pintar las dos listas con objetos de la forma que precisen</summary>
	void drawList(list<InventoryButton*>*  list_, int page, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween,int elementsPerRow = 1)const ;


public:
	///<summary>Constructora del StashState</summary>
	StashState(Application* app = nullptr) : GameState(app) { initState(); };
	///<summary>Detsructora</summary>
	virtual ~StashState() {background_ = nullptr; };

	///<summary>Callbacks para los botones (Cambio de estado)</summary>
	static void backToPrevious(Application* app);

	//<summary>Callbacks para cambiar elementos de este estado</summary>
	static void callbackAdvanceInventoryPage(GameState* state);
	static void callbackPreviousInventoryPage(GameState* state);
	static void callbackAdvanceStashPage(GameState* state);
	static void callbackPreviousStashPage(GameState* state);
	static void callbackSelectObject(GameState* state, InventoryButton* button);
	static void callbackChangeBetweenLists(GameState* state);

	virtual void draw()const;
	virtual void update();

};

