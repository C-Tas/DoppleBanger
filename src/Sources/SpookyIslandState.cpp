#include "SpookyIslandState.h"
#include "Player.h"
#include "ShipState.h"

void backShipSpooky(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void SpookyIslandState::initState()
{
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();

	map_ = new TiledMap(app_,"../Sources/assets/mapas/Isla1-1/Isla 1.tmx", app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, Vector2D(app_->getWindowWidth() / 2, 0), TILE_DRAWING_SIZE, {202,203,204,205,206,207,208,209});

	cout << "mapa cargado correctamente" << endl;

	//Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
	playerEntry_ = Vector2D(((app_->getWindowWidth() * 5 / 8) - W_PLAYER), ((app_->getWindowHeight() * 8 / 10) - H_PLAYER));
	player_->setPos(playerEntry_);
	player_->setScale({ (double)W_PLAYER,(double)H_PLAYER });
	addRenderUpdateLists(player_);
	addRenderUpdateLists(hud_);

	collisionCtrl_->setPlayer(player_);

	//addRenderList(new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::InventaryMenu)));
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
	//delete player_;
	//delete hud_;
}

void SpookyIslandState::update()
{
	collisionCtrl_->islandCollisions();
	PlayState::update();
}
