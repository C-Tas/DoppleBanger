#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"
#include "MonkeyCoco.h"
#include "EnemyPirate.h"
#include "Wolf.h"
#include "Skeleton.h"
#include "EndState.h"
#include "WinState.h"

CaribbeanIslandState::~CaribbeanIslandState() {
	if (currentMap_ != nullptr) delete currentMap_;
	//Reseteo de misiones
	if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		gm_->setStartedMission(missions::gallegaEnProblemas, false);
		gm_->resetMissionCounter(missions::gallegaEnProblemas);
	}
};

void CaribbeanIslandState::update()
{
	if (enemies_.empty() && gm_->getCurrentZone() == Zone::CaribeanBoss) {
		collisionCtrl_->clearList();
		gm_->setUnlockedIslands(Island::Spooky);

		// USABILIDAD
		gm_->setCompletedZone(Zone::CaribeanBoss, true);
		long long timest = Tracker::GetTimeStamp();
		std::string idUser = gm_->getIdUser();
		auto sesion = gm_->getIdSesion();
		LogoutZone* logoutZone = (LogoutZone*)(Tracker::CreateNewEvent(timest, idUser, sesion, (int)EventInfo::EventType::LogoutZone));
		int zone = gm_->generateZoneUsa();
		logoutZone->setZone(zone);
		logoutZone->setNext(0);
		Tracker::TrackEvent(logoutZone);
		//

		app_->getGameStateMachine()->changeState(new ShipState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}

void CaribbeanIslandState::initState()
{
	//Resteo de la isla
	gm_->setCurrentZone(Zone::CaribeanA);
	gm_->setCurrIsland(Island::Caribbean);
	//Inicializamos la musica
	app_->resetMusicChannels();
	app_->resetSoundsChannels();

	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	//Inicializamos el mapa de la zona 1
	initZone1();

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->initSkills();
	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);
}

void CaribbeanIslandState::initZone1()
{
	//Se inicia la música
	app_->getAudioManager()->playChannel(Resources::Isle1Zone1, -1, Resources::MainMusicChannel);

	//Se inicia la mision de la cocinera si no se ha completado ya
	if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		gm_->setStartedMission(missions::gallegaEnProblemas, true);
	}

	//Creamos el mapa
	currentMap_ = new TiledMap(app_, this, ZONE1_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone1);

	//USABILIDAD
	long long timest = Tracker::GetTimeStamp();
	auto sesion = gm_->getIdSesion();
	LoginZone* loginzone = (LoginZone*)(Tracker::CreateNewEvent(timest, gm_->getIdUser(), sesion, (int)EventInfo::EventType::LoginZone));
	int zone = gm_->generateZoneUsa();
	loginzone->setZone(zone);
	loginzone->setCompleted(gm_->getCompletedZone(Zone::CaribeanA));
	Tracker::TrackEvent(loginzone);
}

void CaribbeanIslandState::initZone2()
{
	//Se inicia la música
	app_->getAudioManager()->playChannel(Resources::Isle1Zone2, -1, Resources::MainMusicChannel);

	currentMap_ = new TiledMap(app_, this, ZONE2_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
	//USABILIDAD
	long long timest = Tracker::GetTimeStamp();
	auto sesion = gm_->getIdSesion();
	LoginZone* loginzone = (LoginZone*)(Tracker::CreateNewEvent(timest, gm_->getIdUser(), sesion, (int)EventInfo::EventType::LoginZone));
	int zone = gm_->generateZoneUsa();
	loginzone->setZone(zone);
	loginzone->setCompleted(gm_->getCompletedZone(Zone::CaribeanB));
	Tracker::TrackEvent(loginzone);
}

void CaribbeanIslandState::initZone3()
{
	GameManager* gm_ = GameManager::instance();
	if (!gm_->isThatMissionPass(missions::masValePajaroEnMano)) {
		gm_->setMissionFinished(missions::masValePajaroEnMano, true);
	}

	//Se inicia la música
	app_->getAudioManager()->playChannel(Resources::Isle1Zone3, -1, Resources::MainMusicChannel);

	currentMap_ = new TiledMap(app_, this, ZONE3_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
	//USABILIDAD
	long long timest = Tracker::GetTimeStamp();
	auto sesion = gm_->getIdSesion();
	LoginZone* loginzone = (LoginZone*)(Tracker::CreateNewEvent(timest, gm_->getIdUser(), sesion, (int)EventInfo::EventType::LoginZone));
	int zone = gm_->generateZoneUsa();
	loginzone->setZone(zone);
	loginzone->setCompleted(gm_->getCompletedZone(Zone::CaribeanC));
	Tracker::TrackEvent(loginzone);
}

void CaribbeanIslandState::initBossZone()
{
	app_->getAudioManager()->playChannel(Resources::KrakenMusic, -1, Resources::KrakenMusicChannel);
	currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);

	Actor* boss = static_cast<Actor*>(gameObjects_.back());
	GameManager::instance()->activeHealthBoss(boss);

	//USABILIDAD
	long long timest = Tracker::GetTimeStamp();
	auto sesion = gm_->getIdSesion();
	LoginZone* loginzone = (LoginZone*)(Tracker::CreateNewEvent(timest, gm_->getIdUser(), sesion, (int)EventInfo::EventType::LoginZone));
	int zone = gm_->generateZoneUsa();
	loginzone->setZone(zone);
	loginzone->setCompleted(gm_->getCompletedZone(Zone::CaribeanBoss));
	Tracker::TrackEvent(loginzone);
}

void CaribbeanIslandState::changeZone()
{
	// USABILIDAD
	long long timest = Tracker::GetTimeStamp();
	auto sesion = gm_->getIdSesion();
	LogoutZone* logoutZone = (LogoutZone*)(Tracker::CreateNewEvent(timest, gm_->getIdUser(), sesion, (int)EventInfo::EventType::LogoutZone));
	int zone = gm_->generateZoneUsa();
	logoutZone->setZone(zone);
	Tracker::TrackEvent(logoutZone);
	//
	delete currentMap_;
	collisionCtrl_->clearList();

	enemies_.clear();
	if (gm_->getCurrentZone() == Zone::CaribeanA) {
		gm_->setCompletedZone(Zone::CaribeanA, true);
		// Zona 2
		logoutZone->setNext(12);
		deleteExceptHUD(Zone::CaribeanB);
		initZone2();
		addRenderUpdateLists(hud_);
	}
	else if (gm_->getCurrentZone() == Zone::CaribeanB) {
		gm_->setCompletedZone(Zone::CaribeanB, true);
		int zone = gm_->generateZoneUsa();
		logoutZone->setZone(zone);
		// Zona 3
		logoutZone->setNext(13);
		deleteExceptHUD(Zone::CaribeanC);
		initZone3();
		addRenderUpdateLists(hud_);
	}
	else if (gm_->getCurrentZone() == Zone::CaribeanC) {
		gm_->setCompletedZone(Zone::CaribeanC, true);
		int zone = gm_->generateZoneUsa();
		logoutZone->setZone(zone);
		// Zona del boss
		logoutZone->setNext(14);
		deleteExceptHUD(Zone::CaribeanBoss);
		initBossZone();
		addRenderUpdateLists(hud_);
	}
	hud_->setPlayerInHUD(player_);
	player_->initSkills();

	Tracker::End();
}