#pragma once
#include "PlayState.h"
class Player;

class CaribbeanIslandState : public PlayState
{
private:
	//Chest* chest_ = nullptr; //temporal
	Point2D posChest = Vector2D(200, 200);
	Vector2D scaleChest = Vector2D(100, 100);
public:
	//<summary>Constructor de la isla caribeña</summary>
	CaribbeanIslandState(Application* app) : PlayState(app) { initState(); }
	//<summary>Destructor de la isla caribeña</summary>
	virtual ~CaribbeanIslandState() { if (currentMap_ != nullptr)delete currentMap_; };

	virtual void update();
	virtual void draw()const { 
		currentMap_->draw(); 
		PlayState::draw(); 
	};

protected:
#pragma region Tilemap_Const

	const int TILESET_TILE_WIDTH = 256;
	const int TILESET_TILE_HEIGHT = 256;
	const int TILESET_COLS = 22;
	const int TILESET_FILS = 14;
	const int TILE_DRAWING_SIZE = 128;

	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 1</summary>
	const std::string ZONE1_TILEMAP = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 2</summary>
	const std::string ZONE2_TILEMAP = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 3</summary>
	const std::string ZONE3_TILEMAP = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	//Tiles que queremos que tengan la funcionalidad del colisionar
	const list <int> collisionTilesIdZone1 = { 13,66,67,68,69,70,71,72,73,74,75,76,77,129,131,132,133,178,179,180,181,246,247,248,249,250,251,252,253,254};
#pragma endregion

	virtual void initState();
	///<summary>Inicializa el mapa de la zona 1 de la isla</summary>
	void initZone1();
	///<summary>Inicializa el mapa de la zona 2 de la isla
	///Como todavía no está hecho hace falta definirlo</summary>
	void initZone2();
	///<summary>Inicializa el mapa de la zona 2 de la isla
	///Como todavía no está hecho hace falta definirlo</summary>
	void initZone3();

private:
	TiledMap* currentMap_;
};