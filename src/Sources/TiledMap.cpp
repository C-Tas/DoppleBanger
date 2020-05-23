#include "TiledMap.h"
#include "Camera.h"
#include "CollisionCtrl.h"
#include "Obstacle.h"
#include "MonkeyCoco.h"
#include "Crab.h"
#include "EnemyPirate.h"
#include "Wolf.h"
#include "Skeleton.h"
#include "Kraken.h"
#include "Magordito.h"
#include "Altar.h"
#include "Skeleton.h"
#include "Pumpkin.h"
#include "PlayState.h"
#include "GameManager.h"
#include "Cleon.h"

TiledMap::TiledMap(Application* app, PlayState* state, const string& filename, int tileTilesetHeight, int tileTilesetWidth, int tileSize, 
	Texture* tileset, int filsTileset, int colsTileset,  Vector2D iniPos,  const list<int>& idCollisionTiles, const list<int>& idWallTiles)
{
	collisionCtrl_ = CollisionCtrl::instance();
	gm_ = GameManager::instance();
	///Inicializaci�n del mapa
	tmx::Map map_;
	///Carga del mapa dado un archivo .tmx
	bool success = map_.load(filename);

	///Informaci�n del tileset
	tileset_.textureTileset_ = tileset;
	tileset_.fils = filsTileset;
	tileset_.cols = colsTileset;
	tileset_.tileHeight_ = tileTilesetHeight;
	tileset_.tileWidth_ = tileTilesetWidth;

	tileSize_ = tileSize;
	app_ = app;
	iniPos_ = iniPos;
	idCollisionTiles_ = idCollisionTiles;
	idWallTiles_ = idWallTiles;
	state_ = state;
	state_->getGenerator()->setWorldSize({(int)map_.getTileCount().x,  (int)map_.getTileCount().y });

	//Si no se ha cargado el mapa lanzamos excepcion
	if (!success)throw exception("Mapa no cargado correctamente");
	else {
		auto orientation = map_.getOrientation();
		//Niveles con enemigos
		if (orientation == tmx::Orientation::Isometric) createIsometricMap(map_);
		//Colisiones del barco
		else if (orientation == tmx::Orientation::Orthogonal)createOrthogonalMap(map_);
	}

}

TiledMap::~TiledMap()
{
	//Borramos todos los obstaculos que hemos creado
	for (Obstacle* ob : mapObstacles_) {
		delete ob;
	}
	mapObstacles_.clear();
}

const void TiledMap::draw()
{
	///Con la informaci�n de cada tile, su posici�n en el mundo y la textura que va a usar, renderizamos todos
	for (Tile ob : tilesToRender) {
		tileset_.textureTileset_->render({ (int)(ob.worldPos_.getX() - Camera::instance()->getCamera().getX()),
			(int)(ob.worldPos_.getY() - Camera::instance()->getCamera().getY()),tileSize_, tileSize_ },
			{ (int)ob.tilesetPos_.getX(), (int)ob.tilesetPos_.getY(), tileset_.tileWidth_, tileset_.tileHeight_ });
	}

	//TEMPORAL, PARA COMPROBAR COLISIONES
	//Descomentar para visualizar
	/*for (Obstacle* ob : collidersToRender_) {
		app_->getTextureManager()->getTexture(Resources::CollisionTile)->render({ (int)ob->getColliderPos().getX()-(int)Camera::instance()->getCamera().getX(), (int)ob->getColliderPos().getY() - (int)Camera::instance()->getCamera().getY(),
			(int)ob->getColliderScale().getX(), (int)ob->getColliderScale().getY()}, ob->getCollisionRot());
	}*/

}

Vector2D TiledMap::PosToTile(Vector2D pos)
{
	return Vector2D(round((pos.getX() - iniPos_.getX() + 2 * (pos.getY() - iniPos_.getY())) / GameManager::instance()->getTileSize()),
					round(((pos.getX() - iniPos_.getX()) - 2 * (pos.getY() - iniPos_.getY())) / (-1 * GameManager::instance()->getTileSize())));
}

Vector2D TiledMap::TileToPos(Vector2D tile)
{
	return Vector2D((iniPos_.getX() - ((double)(GameManager::instance()->getTileSize() / 2) * tile.getY()) + ((double)(GameManager::instance()->getTileSize() / 2) * (double)tile.getX())),
					(iniPos_.getY() + ((double)(GameManager::instance()->getTileSize() / 4) * tile.getY()) + ((double)(GameManager::instance()->getTileSize() / 4) * (double)tile.getX())));
}

void TiledMap::setObstacleType(int gid, Obstacle* obstacle)
{
	//Tiles que son bloques (gid es su identificador en el tilemap)
	if (gid >= FIRST_CUBE_TILE && gid < LAST_CUBE_TILE)
		obstacle->setObstacleType(ObstacleType::Block);
	//upLeftBorder
	else if (UPLEFT_BORDER_TILES.end() != find(UPLEFT_BORDER_TILES.begin(), UPLEFT_BORDER_TILES.end(), gid))
		obstacle->setObstacleType(ObstacleType::BorderUL);
	//upRightBorder
	else if (UPRIGHT_BORDER_TILES.end() != find(UPRIGHT_BORDER_TILES.begin(), UPRIGHT_BORDER_TILES.end(), gid))
		obstacle->setObstacleType(ObstacleType::BorderUR);
	//downLeftBorder
	else if (DOWNLEFT_BORDER_TILES.end() != find(DOWNLEFT_BORDER_TILES.begin(), DOWNLEFT_BORDER_TILES.end(), gid))
		obstacle->setObstacleType(ObstacleType::BorderDL);
	//downRightBorder
	else if (DOWNRIGHT_BORDER_TILES.end() != find(DOWNRIGHT_BORDER_TILES.begin(), DOWNRIGHT_BORDER_TILES.end(), gid))
		obstacle->setObstacleType(ObstacleType::BorderDR);
	//Tomb1
	else if (gid == TOMB1_TILE)
		obstacle->setObstacleType(ObstacleType::Tomb1);
	//Tomb2
	else if (gid == TOMB2_TILE)
		obstacle->setObstacleType(ObstacleType::Tomb2);
	//LittleRock
	else if (gid == LITTLEROCK_TILE)
		obstacle->setObstacleType(ObstacleType::LittleRock);
	//BigRock
	else if (gid == BIGROCK_TILE)
		obstacle->setObstacleType(ObstacleType::BigRock);
	//Calaveras
	else if (SKULL_TILES.end() != find(SKULL_TILES.begin(), SKULL_TILES.end(), gid))
		obstacle->setObstacleType(ObstacleType::Skull);
	//Bush1
	else if (BUSH1_TILE == gid)
		obstacle->setObstacleType(ObstacleType::Bush1);
	else if (BUSH_TYPE2_TILE.end() != find(BUSH_TYPE2_TILE.begin(), BUSH_TYPE2_TILE.end(), gid))
		obstacle->setObstacleType(ObstacleType::Bush2);
	else if (TRUNK_TILES.end() != find(TRUNK_TILES.begin(), TRUNK_TILES.end(), gid))
		obstacle->setObstacleType(ObstacleType::Trunk);

	///TEMPORAL PARA VER LOS COLLIDERS
	//Descomentar para visualizar
	//collidersToRender_.push_back(obstacle);
	
	//Una vez que se tiene el tipo del tile, le ajustamos su collider
	obstacle->adjustTileCollider();
}

void TiledMap::addIsometricObstacle(Tile tile, int gid, tileType tileType_)
{
	SDL_Rect collisionArea = { (int)tile.worldPos_.getX() + (tileSize_ / 3), (int)tile.worldPos_.getY() + (tileSize_ / 4), (tileSize_), (tileSize_) };
	Obstacle* newObstacle = new Obstacle(app_, collisionArea, app_->getTextureManager()->getTexture(Resources::CollisionTile), Vector2D(tile.worldPos_.getX(), tile.worldPos_.getY() + (tileSize_ / 8))
		, Vector2D(tileSize_, (double)(tileSize_ / 2) + (double)(tileSize_ / 8)));
	//Los a�adimos a esta lista para luego poder borrarlos desde el propio mapa
	mapObstacles_.push_back(newObstacle);
	
	//Vemos de que tipo es el obst�culo y se lo setteamos
	setObstacleType(gid, newObstacle);

	newObstacle->setGid(gid);

	//Si es una pared, la marcamos como pared
	if (tileType_ == tileType::Wall) {
		newObstacle->isTileWall();
		collisionCtrl_->addObstacle(newObstacle);
	}
	//Si es un obst�culo, lo a�adimos como obst�culo
	else if(tileType_ == tileType::Obstacle)
		collisionCtrl_->addObstacleWithRotation(newObstacle);
	else if (tileType_ == tileType::EndObstacle) {
		collisionCtrl_->addEndObstacle(newObstacle);
	}

}

void TiledMap::addOrthogonalObstacle(Tile tile)
{
	SDL_Rect collisionArea = { (int)tile.worldPos_.getX(), (int)tile.worldPos_.getY(), tileSize_ , tileSize_ };
	Obstacle* newObstacle = new Obstacle(app_, collisionArea, nullptr, tile.worldPos_, Vector2D(tileSize_, tileSize_));
	//Los a�adimos a esta lista para luego poder borrarlos desde el propio mapa
	mapObstacles_.push_back(newObstacle);
	collisionCtrl_->addObstacle(newObstacle);

}

void TiledMap::createIsometricTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions, string layerName)
{
	///Recorremos toda la matriz que contiene la informacion de la capa que acabamos de coger
	for (unsigned int y = 0; y < map_dimensions.y; y++) {
		///Como est� en perspectiva isom�trica, vamos a guardar directamente 
		///la informaci�n de la posici�n de los tiles teniendo en cuenta dicha
		///perspectiva
		double auxY = (iniPos_.getY() + ((double)(tileSize_ / 4) * y));
		double auxX = (iniPos_.getX() - ((double)(tileSize_ / 2) * y));
		for (unsigned int x = 0; x < map_dimensions.x; x++) {

			int tileIndex = x + (y * map_dimensions.x);
			int gid = layer_tiles[tileIndex].ID;

			///Si el tile no es vac�o
			if (gid != 0) {
				Tile tile;
				//Lo guardamos en la posici�n del mapa que corresponda
				tile.worldPos_ = { auxX, auxY };
				//Guardamos la posici�n del tile en el tilemap
				//gid-1 porque nuestra textura 0 se corresponde con el identificador 1(en el archivo de tiled) 
				//y as� sucesivamente
				Vector2D aux = { (double)((gid - 1) % tileset_.cols),(double)((gid - 1) / tileset_.cols) };
				tile.tilesetPos_ = { aux.getX() * tileset_.tileWidth_, aux.getY() * tileset_.tileHeight_ };
				//Lo a�adimos en la lista de tiles
				tilesToRender.push_back(tile);

				if (layerName != "EndLevel") {

					if (idCollisionTiles_.end() != find(idCollisionTiles_.begin(), idCollisionTiles_.end(), gid))
						addIsometricObstacle(tile, gid - 1, tileType::Obstacle);
					if (idWallTiles_.end() != find(idWallTiles_.begin(), idWallTiles_.end(), gid))
						addIsometricObstacle(tile, gid - 1, tileType::Wall);
				}
				else addIsometricObstacle(tile, gid - 1, tileType::EndObstacle);
				
			}
			//Actualizamos la posici�n del mundo para el siguiente tile
			auxY += (tileSize_ / 4);
			auxX += (tileSize_ / 2);
		}
	}
}

void TiledMap::createIsometricPathLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions)
{
	///Recorremos toda la matriz que contiene la informacion de la capa que acabamos de coger
	for (unsigned int y = 0; y < map_dimensions.y; y++) {
		for (unsigned int x = 0; x < map_dimensions.x; x++) {

			int tileIndex = x + (y * map_dimensions.x);
			int gid = layer_tiles[tileIndex].ID;

			///Si el tile es vac�o
			if (gid == 0) {
				state_->getGenerator()->addCollision({ (int)x , (int)y });
			}
		}
	}
}

void TiledMap::createObjects(vector<tmx::Object> object_tiles, tmx::Vector2u map_tilesize, string objectType)
{
	for (tmx::Object ob : object_tiles) {
		tmx::Vector2f pos = ob.getPosition();
		///TILESIZE_Y = TILESIZE_X/2 por la perspectiva isom�trica de los tiles
		pos.x /= map_tilesize.y;
		pos.y /= map_tilesize.y;

		//Posici�n en la que deber�a empezar a dibujarse seg�n como estamos pintando el mapa
		double auxY = (iniPos_.getY() + ((double)(tileSize_ / 4) * pos.y) + ((tileSize_ / 4) * (double)pos.x));
		double auxX = (iniPos_.getX() - ((double)(tileSize_ / 2) * pos.y) + ((tileSize_ / 2) * (double)pos.x));

		createElement(Vector2D(auxX, auxY), objectType);
	}
}

void TiledMap::createElement(Vector2D pos, string objectType){
	if (objectType == "Monkey") {
		MonkeyCoco* monkey = new MonkeyCoco(app_, pos, Vector2D(W_MONKEY, H_MONKEY));
		//state_->addRenderUpdateLists(monkey);
		monkey->setIniPosMap_(iniPos_);
		monkey->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		state_->addEnemy(monkey);
		collisionCtrl_->addEnemy(monkey);
	}
	else if (objectType == "Chest") {
		///A�adir cofre
		Chest* chest = new Chest(app_, pos, Vector2D(W_CHEST,H_CHEST));
		state_->addRenderUpdateLists(chest);

	}
	else if (objectType == "Crab") {
		//A�adir cangrejo
		////Por ahora parece que no se pueden crear pero creo que es por las texturas
		Crab* crab = new Crab(app_, pos, Vector2D(W_CRAB, H_CRAB));
		state_->addEnemy(crab);
		crab->setIniPosMap_(iniPos_);
		crab->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		CollisionCtrl::instance()->addEnemy(crab);
	}
	else if (objectType == "Wolf") {
		//A�adir lobo
		//Falta a�adir lo de patrol pero no estoy segura de como funciona
		Wolf* wolf = new Wolf(app_, pos, Vector2D(W_WOLF, H_WOLF));
		wolf->setIniPosMap_(iniPos_);
		wolf->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		state_->addEnemy(wolf);
		collisionCtrl_->addEnemy(wolf);
	}
	else if (objectType == "Skeleton") {
		//A�adir esqueleto
		Skeleton* skeleton = new Skeleton(app_, pos, Vector2D(W_SKELETON, H_SKELETON));
		//state_->addRenderUpdateLists(monkey);
		skeleton->setIniPosMap_(iniPos_);
		skeleton->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		state_->addEnemy(skeleton);
		CollisionCtrl::instance()->addEnemy(skeleton);
	}
	else if (objectType == "Pumpkin") {
		Pumpkin* pumpkin = new Pumpkin(app_, pos, Vector2D(W_PUMPKIN, H_PUMPKIN));
		pumpkin->setIniPosMap_(iniPos_);
		pumpkin->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		state_->addEnemy(pumpkin);
		collisionCtrl_->addEnemy(pumpkin);
	}
	else if (objectType == "Kraken") {
		Kraken* kraken = new Kraken(app_, pos, Vector2D(W_KRAKEN,H_KRAKEN));
		kraken->setIniPosMap_(iniPos_);
		//state_->addRenderUpdateLists(monkey);
		state_->addEnemy(kraken);
		collisionCtrl_->addEnemy(kraken);
	}
	else if (objectType == "Magordito") {
		//A�adir Magordito
		Magordito* magordito = new Magordito(app_, pos, Vector2D(W_WOLF, H_WOLF));
		magordito->setIniPosMap_(iniPos_);
		magordito->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		state_->addEnemy(magordito);
		collisionCtrl_->addEnemy(magordito);
	}
	else if (objectType == "EnemyPirate") {
		//A�adir Pirata naufrago
		//Falta a�adir lo de patrol pero no estoy segura de como funciona
		EnemyPirate* pirate = new EnemyPirate(app_, pos, Vector2D(W_ENEMYPIRATE, H_ENEMYPIRATE));
		pirate->setIniPosMap_(iniPos_);
		pirate->setPathPos({ (int)PosToTile(pos).getX(),(int)PosToTile(pos).getY() });
		state_->addEnemy(pirate);
		collisionCtrl_->addEnemy(pirate);
	}
	else if (objectType == "Cleon") {
		Cleon* cleon = new Cleon(app_, pos, Vector2D(W_PLAYER, H_PLAYER));
		state_->addEnemy(cleon);
		collisionCtrl_->addEnemy(cleon);
	}
	else if (objectType == "Chef") {
		if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
			NPC* chef;
			chef = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Cooker), pos, Vector2D(W_NPC_CHEF, H_NPC_CHEF), 2);
			state_->addRenderUpdateLists(chef);
			state_->addObject(chef);
		}
	}
	else if (objectType == "Morty") {
		if (!gm_->isThatMissionPass(missions::papelesSiniestros)) {
			NPC* morty;
			morty = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Morty), pos, Vector2D(W_NPC_MORTY, H_NPC_MORTY), 3);
			state_->addRenderUpdateLists(morty);
			state_->addObject(morty);
		}
	}
	else if (objectType == "Nami") {
		if (!gm_->isThatMissionPass(missions::arlongPark)) {
			NPC* nami;			
			nami = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Cartographer), pos, Vector2D(W_NPC_NAMI, H_NPC_NAMI), 6);
			state_->addRenderUpdateLists(nami);
			state_->addObject(nami);
		}
	}
	else if (objectType == "Player") {
		Player* player = new Player(app_, pos, Vector2D(W_PLAYER, H_PLAYER));
		state_->addRenderUpdateLists(player);
		state_->setPlayer(player);
		player->setHealth(gm_->getCurrentPlayerLife());
		player->setMana(gm_->getCurrentPlayerMana());

		gm_->setPlayer(player);
		collisionCtrl_->setPlayer(player);
		player->setColliderPos(Vector2D((player->getScale().getX() / 3), 2* (player->getScale().getY() / 4)));
		player->setColliderScale(Vector2D((player->getScale().getX() / 3),  (player->getScale().getY() / 4)));
	}
	else if (objectType == "Altar") {
		Altar* altar = new Altar(app_, pos, { 100,100 });
		state_->addRenderUpdateLists(altar);
		altar->createMobs(state_);
	}

	
}

void TiledMap::createIsometricMap(const tmx::Map& map_)
{
	//Cuantos tiles hay por fila y columna
	tmx::Vector2u map_dimensions = map_.getTileCount();
	//Tama�o de los tiles del mapa
	tmx::Vector2u map_tilesize = map_.getTileSize();

	///Cogemos todas las layers del archivo
	auto& map_layers = map_.getLayers();
	///Las recorremos una a una
	for (auto& layer : map_layers) {
		//Capas con tiles
		if (layer->getType() == tmx::Layer::Type::Tile) {

			auto* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());
			//Cogemos los tiles de la Layer
			auto layer_tiles = tile_layer->getTiles();
			if (layer->getName() == "pathfinding")
				createIsometricPathLayer(layer_tiles, map_dimensions);
			else
			createIsometricTileLayer(layer_tiles, map_dimensions, tile_layer->getName());
		}
		//Capas con objetos
		else if (layer->getType() == tmx::Layer::Type::Object) {
			auto* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());
			//Cogemos los objetos de la layer
			auto layer_objects = object_layer->getObjects();
			createObjects(layer_objects, map_tilesize, object_layer->getName());
		}
	}
}

void TiledMap::createOrthogonalMap(const tmx::Map& map_)
{
	//Cuantos tiles hay por fila y columna
	tmx::Vector2u map_dimensions = map_.getTileCount();
	//Tama�o de los tiles del mapa
	tmx::Vector2u map_tilesize = map_.getTileSize();

	///Cogemos todas las layers del archivo
	auto& map_layers = map_.getLayers();
	///Las recorremos una a una
	for (auto& layer : map_layers) {
		//Capas con tiles
		if (layer->getType() == tmx::Layer::Type::Tile) {

			auto* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());
			//Cogemos los tiles de la Layer
			auto layer_tiles = tile_layer->getTiles();
			createOrthogonalTileLayer(layer_tiles, map_dimensions, map_tilesize);
		}
	}
}

void TiledMap::createOrthogonalTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions,tmx::Vector2u tilesize)
{
	///Recorremos toda la matriz que contiene la informacion de la capa que acabamos de coger
	for (unsigned int y = 0; y < map_dimensions.y; ++y) {

		for (unsigned int x = 0; x < map_dimensions.x; ++x) {

			int tileIndex = x + (y * map_dimensions.x);
			int gid = layer_tiles[tileIndex].ID;

			///Si el tile no es vac�o
			if (gid != 0) {
				Tile tile;
				//Lo guardamos en la posici�n del mapa que corresponda
				tile.worldPos_ = { iniPos_.getX() + ((double)tileSize_ * (double)x),iniPos_.getY() + ((double)tileSize_ * (double)y) };
				Vector2D aux = { (double)((gid - 1) % tileset_.cols),(double)((gid - 1) / tileset_.cols) };
				tile.tilesetPos_ = { aux.getX() * tileset_.tileWidth_, aux.getY() * tileset_.tileHeight_ };

				//TEMPORAL, PARA QUE SE VEAN DONDE EST�N LAS COLISIONES
				//tilesToRender.push_back(tile);

				//En las capas ortogonales solo vamos a pintar la imagen, asi que cualquier tile que no sea vacio
				//es un tile de colision
				addOrthogonalObstacle(tile);
			}
		}
	}
}
