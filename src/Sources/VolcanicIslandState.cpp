#include "VolcanicIslandState.h"
#include "Crab.h"
#include "WinState.h"

void VolcanicIslandState::initState()
{
	app_->resetMusicChannels();
	app_->resetSoundsChannels();

	//Temporal hasta que est� la m�sica de la isla Spooky
	app_->getAudioManager()->playChannel(Resources::CleonTheme, -1, Resources::MainMusicChannel);

	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	//Inicializamos el mapa de la zona 1
	//Creamos el mapa
	currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone_, wallTilesIdZone_);

	//Inicializamos el hud
	hud_ = new HUD(app_);
	Actor* boss = static_cast<Actor*>(gameObjects_.back());
	GameManager::instance()->activeHealthBoss(boss);
	player_->initSkills();

	//A�adimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);

	gm_->setCurrentZone(Zone::Volcanic);

}

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
	initState();
}

void VolcanicIslandState::update()
{
	if (enemies_.empty() && gm_->getCurrentZone() == Zone::Volcanic) {
		collisionCtrl_->clearList();
		app_->getGameStateMachine()->changeState(new WinState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		collisionCtrl_->volcanicCollision();
		PlayState::update();
	}
}
