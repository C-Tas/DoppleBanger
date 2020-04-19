#include "SpookyIslandState.h"
#include "Player.h"
#include "ShipState.h"

void backShipSpooky(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void SpookyIslandState::initState()
{

	map_ = new TiledMap("../Sources/assets/mapas/Isla1-1/Isla 1.tmx", app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, Vector2D(app_->getWindowWidth()/2,0), TILE_DRAWING_SIZE);

	cout << "mapa cargado correctamente" << endl;
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
	delete player_;
	delete hud_;
}
