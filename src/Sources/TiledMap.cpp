#include "TiledMap.h"
#include "../tmxLite/TileLayer.hpp"
#include "../tmxLite/Map.hpp"
#include "Camera.h"
#include "CollisionCtrl.h"
#include "Obstacle.h"

TiledMap::TiledMap(Application* app_, const string& filename,Texture* tileset, int filsTileset, int colsTileset, int tileTilesetHeight,
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

	//Si no se ha cargado el mapa lanzamos excepcion
	if (!success)throw exception("Mapa no cargado correctamente");
	else {

		//Cuantos tiles hay por fila y columna
		auto map_dimensions = map_.getTileCount();
		//Tamaño de los tiles del mapa
		auto tilesize = map_.getTileSize();

		///Cogemos todas las layers del archivo
		auto& map_layers = map_.getLayers();
		///Las recorremos una a una
		for (auto& layer : map_layers) {
			//Cogemos las capas que son solo tiles (no las de objetos)
			if (layer->getType() == tmx::Layer::Type::Tile) {

				auto* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());
				
				//Cogemos los tiles de la Layer
				auto layer_tiles = tile_layer->getTiles();

				///Recorremos toda la matriz que contiene la informacion de la capa que acabamos de 
				//coger
				for (auto y = 0; y < map_dimensions.y; y++) {
					///Como está en perspectiva isométrica, vamos a guardar directamente 
					///la información de la posición de los tiles teniendo en cuenta dicha
					///perspectiva
					int auxY = (iniPos.getY() + ((tileSize/ 4) * y));
					int auxX = (iniPos.getX() - ((tileSize / 2) * y));
					for (auto x = 0; x < map_dimensions.x; x++) {

						int tileIndex = x + (y * map_dimensions.y);
						int gid = layer_tiles[tileIndex].ID;

						///Si el tile no es vacío
						if (gid != 0) {
							Tile tile;
							//Lo guardamos en la posición del mapa que corresponda
							tile.worldPos_ = { (double)(auxX), (double)(auxY) };
							//Guardamos la posición del tile en el tilemap
							//gid-1 porque nuestra textura 0 se corresponde con el identificador 1(en el archivo de tiled) 
							//y así sucesivamente
							Vector2D aux = { (double)((gid-1) % tileset_.cols),(double)((gid-1) / tileset_.cols) };
							tile.tilesetPos_ = { aux.getX() * tileset_.tileWidth_, aux.getY() * tileset_.tileHeight_ };
							//Lo añadimos en la lista de tiles
							tilesToRender.push_back(tile);

							if (idCollisionTiles.end() != find(idCollisionTiles.begin(), idCollisionTiles.end(), gid)) {
								SDL_Rect collisionArea = { tile.worldPos_.getX() + tileSize_/4, tile.worldPos_.getY() + tileSize_ / 3, tileSize_/4, tileSize_/4 };
								Obstacle* newObstacle = new Obstacle(app_, collisionArea, nullptr, tile.worldPos_, Vector2D(tileSize_, tileSize_));
								mapObstacles_.push_back(newObstacle);
								CollisionCtrl::instance()->addObstacle(newObstacle);
							}
						}
						//Actualizamos la posición del mundo para el siguiente tile
						auxY += (tileSize / 4);
						auxX += (tileSize / 2);
					}

				}
			}
		}
	}

}

TiledMap::~TiledMap()
{
	for (Obstacle* ob : mapObstacles_) {
		delete ob;
	}
	mapObstacles_.clear();
}

const void TiledMap::draw()
{
	for (Tile ob : tilesToRender) {
		tileset_.textureTileset_->render({ (int)(ob.worldPos_.getX()-Camera::instance()->getCamera().getX()), (int)(ob.worldPos_.getY()- Camera::instance()->getCamera().getY()),tileSize_, tileSize_ },
			{ (int)ob.tilesetPos_.getX(), (int)ob.tilesetPos_.getY(), tileset_.tileWidth_, tileset_.tileHeight_ });
	}
}
