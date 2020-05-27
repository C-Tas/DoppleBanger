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
	bool onTutorial() { return tutorialComplete; }
protected:
	//Para Venancio
	NPC* venancio_ = nullptr;
	Vector2D TUTORIAL_POS;
	Vector2D POST_TUTORIAL_POS;
	bool tutorialComplete = true;

private:
	bool songActive = false;

	//Para guardar la posici�n del clik del rat�n  
	SDL_Point mouse; 

	//Mapa con las colisiones del barco
	TiledMap* collisionMap_;
	const std::string TILED_MAP = "../Sources/assets/mapas/barco/barco.tmx";
	const int TILE_WIDTH_TILESET = 8;
	const int TILE_HEIGHT_TILESET = 8;
	const int TILE_DRAWING_SIZE =  (app_->getWindowWidth()/62);
	const int TILESET_COLS = 1;
	const int TILESET_FILS = 1;

	#pragma region ShipObjects
	ShipObject* stash_ = nullptr;//Alijo
	ShipObject* door_ = nullptr; //Trampilla
	ShipObject* wheel_ = nullptr;//Tim�n
	ShipObject* exit_ = nullptr; //Salida


	//Dimensiones de las entidades
	const double W_WIN = app_->getWindowWidth();
	const double H_WIN = app_->getWindowHeight();

	const double W_STASH = W_WIN / 7;
	const double H_STASH = H_WIN / 6;

	const double W_DOOR = W_WIN / 8;
	const double H_DOOR = H_WIN / 8;

	const double W_WHEEL = W_WIN / 11;
	const double H_WHEEL = H_WIN / 5;

	const double W_EXIT = W_WIN / 15;
	const double H_EXIT = H_WIN / 3;

	const double W_PLAYER = W_WIN / 8;
	const double H_PLAYER = H_WIN / 4;
	#pragma endregion

	#pragma region NPCs
	const double W_ELDERMAN = W_WIN * 2 / 14;
	const double H_ELDERMAN = H_WIN * 2 / 7;

	const double W_MERCHANT = W_WIN * 2 / 19;
	const double H_MERCHANT = H_WIN * 2 / 9;

	const double W_CHEF = W_WIN / 22;
	const double H_CHEF = H_WIN / 6;

	const double W_MORTY = W_WIN / 14;
	const double H_MORTY = H_WIN / 5;

	const double W_PARROT = W_WIN / 16;
	const double H_PARROT = H_WIN / 8;

	const double W_SKELETON = W_WIN / 13;
	const double H_SKELETON = H_WIN / 6;

	const double W_CARTOGRAPHER = W_WIN / 6;
	const double H_CARTOGRAPHER = H_WIN / 3;
	#pragma region

	virtual void initState();
	void createNPCs();

	#pragma region Callbacks
	static void goIsland(Application* app);
	static void goStashState(Application* app);
	static void goMap(Application* app);
	static void goSaveState(Application* app);
	#pragma endregion
	//Sirve para cargar el estado
	virtual void loadState();
};