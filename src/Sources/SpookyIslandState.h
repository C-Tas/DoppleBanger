#pragma once
#include "PlayState.h"
#include "TiledMap.h"
class SpookyIslandState : public PlayState
{
private:
	void initState();
	TiledMap* map_;
#pragma region TILESET
	const int TILESET_TILE_WIDTH = 32;
	const int TILESET_TILE_HEIGHT = 32;
	const int TILESET_COLS = 25;
	const int TILESET_FILS = 9;
	const int TILE_DRAWING_SIZE = 128;
	const std::string ZONE1_MAP_DIR = "../Sources/assets/mapas/Isla1-1/Isla 1.tmx";
	//Tiles que queremos que tengan la funcionalidad del colisionar
	const list<int> COLLISION_TILES_ID = { 202,203,204,205,206,207,208,209,210,211,212 };
#pragma endregion

public:
	SpookyIslandState(Application* app);
	virtual ~SpookyIslandState();
	virtual void draw()const { map_->draw(); PlayState::draw(); };
	virtual void update();

};

