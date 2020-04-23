#pragma once
#include "PlayState.h"
class Player;

class CaribbeanIslandState : public PlayState
{
public:
	//<summary>Constructor de la isla caribeña</summary>
	CaribbeanIslandState(Application* app) : PlayState(app) { initState(); }
	//<summary>Destructor de la isla caribeña</summary>
	virtual ~CaribbeanIslandState() { if (currentMap_ != nullptr)delete currentMap_; };

	virtual void update();
	virtual void draw()const { currentMap_->draw(); PlayState::draw(); };

protected:
#pragma region Tilemap_Const

	const int TILESET_TILE_WIDTH = 32;
	const int TILESET_TILE_HEIGHT = 32;
	const int TILESET_COLS = 25;
	const int TILESET_FILS = 9;
	const int TILE_DRAWING_SIZE = 128;

	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 1</summary>
	const std::string ZONE1_TILEMAP = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 2</summary>
	const std::string ZONE2_TILEMAP = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 3</summary>
	const std::string ZONE3_TILEMAP = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	//Tiles que queremos que tengan la funcionalidad del colisionar
	const list <int> collisionTilesIdZone1 = { 202,203,204,205,206,207,208,209,210,211,212 };
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