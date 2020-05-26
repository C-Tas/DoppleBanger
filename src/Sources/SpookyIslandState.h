#pragma once
#include "PlayState.h"
#include "checkML.h"

/*
Cambios realizados por We Balance Team #2:
	- Modificados los precios de los objetos.
	- Nerfeado el esqueleto
	- Nerfeado el pirata
	- Bufado el esqueleto
	- Nerfeado el lobo
	- Arreglado pila bugs
	- Nerfeado la calabaza
	- Nerfeado el esqueleto
	- Arreglado pila bugs, otra vez
*/

class SpookyIslandState : public PlayState
{
private:
	void initState();
	TiledMap* currentMap_;
#pragma region TILESET
	const int TILESET_TILE_WIDTH = 256;
	const int TILESET_TILE_HEIGHT = 256;
	const int TILESET_COLS = 22;
	const int TILESET_FILS = 14;
	const int TILE_DRAWING_SIZE = gm_->getTileSize();

	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona 1</summary>
	const std::string ZONE1_TILEMAP = "../Sources/assets/mapas/Isla2/Zona 1/Isla2.1.tmx";
	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona del boss
	const std::string BOSSZONE_TILEMAP = "../Sources/assets/mapas/Isla2/Zona 3/Isla2_Boss.tmx";

	//Tiles que queremos que el player no atraviese
	const list <int> collisionTilesIdZone_ = { 1,121,122,123,124,162,163,164,179,180,181,182,248,249,250,251,252,253,254,255,256,257,258,287,288,289,290,291,292,293,294,295,296,297,298,299 };
	//Tiles que queremos que sean paredes (y por tanto que destruyan balas)
	const list <int> wallTilesIdZone_ = { 67,179,180,181,182,248,249,250,251,252,253,254,255,256,257,258,287,288,289,290,291,292,293,294,295,296,297,298,299 };
#pragma endregion

public:
	SpookyIslandState(Application* app);
	virtual ~SpookyIslandState();
	virtual void draw()const { currentMap_->draw(); PlayState::draw(); };
	virtual void update();
	///<summary>Método para cambiar de zona(Redefinido)</summary>
	virtual void changeZone();
	
};