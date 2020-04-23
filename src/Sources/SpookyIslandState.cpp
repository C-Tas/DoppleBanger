#include "SpookyIslandState.h"
#include "ShipState.h"
#include "WinState.h"

void backShipSpooky(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void SpookyIslandState::initState()
{
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();

	//Creamos el mapa
	map_ = new TiledMap(app_,this,ZONE1_MAP_DIR, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS,  Vector2D(app_->getWindowWidth() / 2, 0),  COLLISION_TILES_ID);

	addRenderUpdateLists(hud_);
}

SpookyIslandState::SpookyIslandState(Application* app) : PlayState(app)
{
	initState();
	#ifdef _DEBUG
	printf("SpookyIsland");
	#endif
}

SpookyIslandState::~SpookyIslandState()
{
	delete map_;
}

void SpookyIslandState::update()
{
	if (enemies_.size() != 0) {
		///Para comprobar las colisiones con el mapa
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
	else {
		collisionCtrl_->clearList();
		app_->getGameStateMachine()->changeState(new WinState(app_));
	}
}
