#pragma once
#include "GameState.h"
#include <list>

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

public:
	StashState(Application* app = nullptr) : GameState(app) { initState(); };
	virtual ~StashState() {};
	static void backToPrevious(Application* app);

};

