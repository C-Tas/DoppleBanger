#include "TestState.h"


void TestState::initState()
{
	app_->getAudioManager()->haltChannel(Resources::MainMusicChannel);
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	currentMap_ = new TiledMap(app_, this, ZONE1_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone1);

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->initSkills();

	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);
}
