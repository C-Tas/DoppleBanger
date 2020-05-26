#pragma once
#include "PlayState.h"
class VolcanicIslandState : public PlayState
{
private:
	void initState();
	TiledMap* currentMap_ = nullptr;
#pragma region TILESET
	const int TILESET_TILE_WIDTH = 256;
	const int TILESET_TILE_HEIGHT = 256;
	const int TILESET_COLS = 22;
	const int TILESET_FILS = 14;
	const int TILE_DRAWING_SIZE = gm_->getTileSize();

	///<summary>Direccion en la que se encuentra el archivo de Tiled del mapa de la zona del boss
	const std::string BOSSZONE_TILEMAP = "../Sources/assets/mapas/Isla3/Isla3.tmx";

	//Tiles que queremos que el player no atraviese
	const list <int> collisionTilesIdZone_ = { 1,121,122,123,124,162,163,164,179,180,181,182,248,249,250,251,252,253,254,255,256,257,258,287,288,289,290,291,292,293,294,295,296,297,298,299 };
	//Tiles que queremos que sean paredes (y por tanto que destruyan balas)
	const list <int> wallTilesIdZone_ = { 67,179,180,181,182,248,249,250,251,252,253,254,255,256,257,258,287,288,289,290,291,292,293,294,295,296,297,298,299 };
#pragma endregion
public:
	VolcanicIslandState(Application* app);
	virtual ~VolcanicIslandState() { delete currentMap_; };
	virtual void draw()const { currentMap_->draw(); PlayState::draw(); };
	virtual void update();
};

