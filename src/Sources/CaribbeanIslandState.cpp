#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"
#include "EndState.h"
#include "WinState.h"


void CaribbeanIslandState::update()
{
	if (enemies_.empty()) {
		collisionCtrl_->clearList();
		app_->getGameStateMachine()->changeState(new WinState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}

void CaribbeanIslandState::initState()
{
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();

	//Inicializamos el mapa de la zona 1
	initZone1();

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->setElementsHUD();

	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);
}

void CaribbeanIslandState::initZone1()
{
	//Creamos el mapa
	currentMap_ = new TiledMap(app_, this, ZONE1_TILEMAP, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, Vector2D(app_->getWindowWidth() / 2, 0), TILE_DRAWING_SIZE, collisionTilesIdZone1);
}

