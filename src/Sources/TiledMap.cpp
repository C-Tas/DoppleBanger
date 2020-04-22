#include "TiledMap.h"
#include "Camera.h"
#include "CollisionCtrl.h"
#include "Obstacle.h"
#include "MonkeyCoco.h"
#include "Crab.h"
#include "EnemyPirate.h"
#include "Wolf.h"

TiledMap::TiledMap(Application* app, PlayState* state, const string& filename,Texture* tileset, int filsTileset, int colsTileset, int tileTilesetHeight,
	int tileTilesetWidth, Vector2D iniPos, int tileSize, const list<int>& idCollisionTiles)
{
	///Inicialización del mapa
	tmx::Map map_;
	///Carga del mapa dado un archivo .tmx
	bool success = map_.load(filename);

	///Información del tileset
	tileset_.textureTileset_ = tileset;
	tileset_.fils = filsTileset;
	tileset_.cols = colsTileset;
	tileset_.tileHeight_ = tileTilesetHeight;
	tileset_.tileWidth_ = tileTilesetWidth;

	tileSize_ = tileSize;
	app_ = app;
	iniPos_ = iniPos;
	idCollisionTiles_ = idCollisionTiles;
	state_ = state;

	//Si no se ha cargado el mapa lanzamos excepcion
	if (!success)throw exception("Mapa no cargado correctamente");
	else {

		//Cuantos tiles hay por fila y columna
		tmx::Vector2u map_dimensions = map_.getTileCount();
		//Tamaño de los tiles del mapa
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
				createTileLayer(layer_tiles, map_dimensions);
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
	///Con la información de cada tile, su posición en el mundo y la textura que va a usar, renderizamos todos
	for (Tile ob : tilesToRender) {
		tileset_.textureTileset_->render({ (int)(ob.worldPos_.getX()-Camera::instance()->getCamera().getX()), 
			(int)(ob.worldPos_.getY()- Camera::instance()->getCamera().getY()),tileSize_, tileSize_ },
			{ (int)ob.tilesetPos_.getX(), (int)ob.tilesetPos_.getY(), tileset_.tileWidth_, tileset_.tileHeight_ });
	}
}

void TiledMap::addObstacle(Tile tile)
{
	SDL_Rect collisionArea = { (int)tile.worldPos_.getX() + (tileSize_ / 4), (int)tile.worldPos_.getY() + (tileSize_ / 3), (tileSize_ / 4), (tileSize_ / 4) };
	Obstacle* newObstacle = new Obstacle(app_, collisionArea, nullptr, tile.worldPos_, Vector2D(tileSize_, tileSize_));
	//Los añadimos a esta lista para luego poder borrarlos desde el propio mapa
	mapObstacles_.push_back(newObstacle);
	CollisionCtrl::instance()->addObstacle(newObstacle);
}

void TiledMap::createTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions)
{
	///Recorremos toda la matriz que contiene la informacion de la capa que acabamos de coger
	for (unsigned int y = 0; y < map_dimensions.y; y++) {
		///Como está en perspectiva isométrica, vamos a guardar directamente 
		///la información de la posición de los tiles teniendo en cuenta dicha
		///perspectiva
		double auxY = (iniPos_.getY() + ((double)(tileSize_ / 4) * y));
		double auxX = (iniPos_.getX() - ((double)(tileSize_ / 2) * y));
		for (unsigned int x = 0; x < map_dimensions.x; x++) {

			int tileIndex = x + (y * map_dimensions.y);
			int gid = layer_tiles[tileIndex].ID;

			///Si el tile no es vacío
			if (gid != 0) {
				Tile tile;
				//Lo guardamos en la posición del mapa que corresponda
				tile.worldPos_ = { auxX, auxY };
				//Guardamos la posición del tile en el tilemap
				//gid-1 porque nuestra textura 0 se corresponde con el identificador 1(en el archivo de tiled) 
				//y así sucesivamente
				Vector2D aux = { (double)((gid - 1) % tileset_.cols),(double)((gid - 1) / tileset_.cols) };
				tile.tilesetPos_ = { aux.getX() * tileset_.tileWidth_, aux.getY() * tileset_.tileHeight_ };
				//Lo añadimos en la lista de tiles
				tilesToRender.push_back(tile);

				if (idCollisionTiles_.end() != find(idCollisionTiles_.begin(), idCollisionTiles_.end(), gid))
					addObstacle(tile);
			}
			//Actualizamos la posición del mundo para el siguiente tile
			auxY += (tileSize_ / 4);
			auxX += (tileSize_ / 2);
		}
	}
}

void TiledMap::createObjects(vector<tmx::Object> object_tiles,tmx::Vector2u map_tilesize, string objectType)
{
	for (tmx::Object ob : object_tiles) {
		tmx::Vector2f pos = ob.getPosition();
		//Esto debería de ser map_tilesize.x pero como en el mapa de tile de momento no tienen todos los tiles el
		//mismo tamaño pues de momento uso esto como apaño
		pos.x /= map_tilesize.y;
		pos.y /= map_tilesize.y;

		//Posición en la que debería empezar a dibujarse según como estamos pintando el mapa
		double auxY = (iniPos_.getY() + ((double)(tileSize_ / 4) * pos.y) + ((tileSize_/4)* (double)pos.x));
		double auxX = (iniPos_.getX() - ((double)(tileSize_ / 2) * pos.y) + ((tileSize_/2)* (double)pos.x));

		createElement(Vector2D(auxX, auxY), objectType);
	}
}

void TiledMap::createElement(Vector2D pos, string objectType)
{
	if (objectType == "Monkey") {
		MonkeyCoco* monkey = new MonkeyCoco(app_, pos, Vector2D(W_MONKEY, H_MONKEY));
		//state_->addRenderUpdateLists(monkey);
		state_->addEnemy(monkey);
		CollisionCtrl::instance()->addEnemy(monkey);
	}
	else if (objectType == "Chest") {
		///Añadir cofre
	}
	else if (objectType == "Crab") {
		//Añadir cangrejo
		//Por ahora parece que no se pueden crear pero creo que es por las texturas
		Crab* crab = new Crab(app_, pos, Vector2D(W_CRAB, H_CRAB));
		state_->addEnemy(crab);
		CollisionCtrl::instance()->addEnemy(crab);
	}
	else if (objectType == "Wolf") {
		//Añadir lobo
		//Falta añadir lo de patrol pero no estoy segura de como funciona
		Wolf* wolf = new Wolf(app_, pos, Vector2D(W_WOLF, H_WOLF));
		state_->addEnemy(wolf);
		CollisionCtrl::instance()->addEnemy(wolf);
	}
	else if (objectType == "Skeleton") {
		//Añadir esqueleto
	}
	else if (objectType == "Pumpkin") {
		//Añadir calabaza
	}
	else if (objectType == "Kraken") {
		//Añadir Kraken
	}
	else if (objectType == "Magordito") {
		//Añadir Magordito
	}
	else if (objectType == "EnemyPirate") {
		//Añadir Pirata naufrago
		//Falta añadir lo de patrol pero no estoy segura de como funciona
		EnemyPirate* pirate = new EnemyPirate(app_, pos, Vector2D(W_ENEMYPIRATE, H_ENEMYPIRATE));
		state_->addRenderUpdateLists(pirate);
		CollisionCtrl::instance()->addEnemy(pirate);
	}
	else if (objectType == "Cleon") {
		//Añadir Cleon
	}
	else if (objectType == "Player") {
		Player* player = new Player(app_, pos, Vector2D(W_PLAYER, H_PLAYER));
		state_->addRenderUpdateLists(player);
		state_->setPlayer(player);
		GameManager::instance()->setPlayer(player);
		CollisionCtrl::instance()->setPlayer(player);
	}
	
}
