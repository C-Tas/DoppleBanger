#pragma once
#include "PlayState.h"


class Player;
class ShipObject;
class Trigger;

class ShipState : public PlayState
{
public:
	///<summary> Constructora del barco</summary>
	ShipState(Application* app) : PlayState(app) { initState(); }
	virtual ~ShipState() { delete collisionMap_; }
	void update();

private:
	//Tiempo para que canten los piratas
	Uint32 pirateSingers_ = 18000;
	Uint32 startInstance_ = 0;
	bool songActive = false;

	//Para guardar la posici�n del clik del rat�n  
	SDL_Point mouse; 

	//Mapa con las colisiones del barco
	TiledMap* collisionMap_;
	const std::string TILED_MAP = "../Sources/assets/mapas/barco/barco.tmx";
	const int TILE_WIDTH_TILESET = 8;
	const int TILE_HEIGHT_TILESET = 8;
	const int TILE_DRAWING_SIZE =  (int)(app_->getWindowWidth()/60);
	const int TILESET_COLS = 1;
	const int TILESET_FILS = 1;

	#pragma region ShipObjects
	ShipObject* stash_ = nullptr;//Alijo
	ShipObject* door_ = nullptr; //Trampilla
	ShipObject* wheel_ = nullptr;//Tim�n
	ShipObject* exit_ = nullptr; //Salida

	//Dimensiones de las entidades
	const uint W_WIN = app_->getWindowWidth();
	const uint H_WIN = app_->getWindowHeight();

	const uint W_STASH = W_WIN / 7;
	const uint H_STASH = H_WIN / 6;

	const uint W_DOOR = W_WIN / 8;
	const uint H_DOOR = H_WIN / 8;

	const uint W_WHEEL = W_WIN / 11;
	const uint H_WHEEL = H_WIN / 5;

	const uint W_EXIT = W_WIN / 15;
	const uint H_EXIT = H_WIN / 3;

	const uint W_PLAYER = W_WIN / 8;
	const uint H_PLAYER = H_WIN / 4;
	#pragma endregion

	#pragma region NPCs
	const uint W_ELDERMAN = W_WIN / 11;
	const uint H_ELDERMAN = H_WIN / 6;

	const uint W_MERCHANT = W_WIN * 2 / 19;
	const uint H_MERCHANT = H_WIN * 2 / 9;

	const uint W_CHEF = W_WIN / 20;
	const uint H_CHEF = H_WIN / 8;

	const uint W_MORTY = W_WIN / 20;
	const uint H_MORTY = H_WIN / 10;

	const uint W_PARROT = W_WIN / 20;
	const uint H_PARROT = H_WIN / 10;

	const uint W_SKELETON = W_WIN / 20;
	const uint H_SKELETON = H_WIN / 10;

	const uint W_CARTOGRAPHER = W_WIN / 12;
	const uint H_CARTOGRAPHER = H_WIN / 6;
	#pragma region

	void initState();
	void createNPCs();

	#pragma region Callbacks
	static void goIsland(Application* app);
	static void goStashState(Application* app);
	static void goMap(Application* app);
	static void goSaveState(Application* app);
	#pragma endregion
};