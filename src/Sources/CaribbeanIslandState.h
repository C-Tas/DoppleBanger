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
	//Tiles que queremos que el player no atraviese
	const list <int> collisionTilesIdZone1 = {1,121,122,123,124,162,163,164,179,180,181,182,248,249,250,251,252,253,254,255,256,257,258,287,288,289,290,291,292,293,294,295,296,297,298,299 };
	//Tiles que queremos que sean paredes (y por tanto que destruyan balas)
	const list <int> wallTilesIdZone1 = { 12,13,162,163,164,179,180,181,182,248,249,250,251,252,253,254,255,256,257,258,287,288,289,290,291,292,293,294,295,296,297,298,299 };
#pragma endregion

	virtual void initState();
	///<summary>Inicializa el mapa de la zona 1 de la isla</summary>
	void initZone1();
	///<summary>Inicializa el mapa de la zona 2 de la isla
	///Como todavía no está hecho hace falta definirlo</summary>
	void initZone2();
	///<summary>Inicializa el mapa de la zona 3 de la isla
	///Como todavía no está hecho hace falta definirlo</summary>
	void initZone3();

private:
	TiledMap* currentMap_;
};