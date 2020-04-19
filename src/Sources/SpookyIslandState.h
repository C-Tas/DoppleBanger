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
#pragma endregion
	const int TILE_DRAWING_SIZE = 32;

public:
	SpookyIslandState(Application*);
	virtual ~SpookyIslandState();
	virtual void draw()const { map_->draw(); };
};

