#include "TiledMap.h"
#include "../tmxLite/TileLayer.hpp"
#include "checkML.h"

TiledMap::TiledMap(const string& filename,Texture* tileset, int filsTileset, int colsTileset, int tileTilesetHeight, int tileTilesetWidth, Vector2D iniPos, int tileSize)
{
	///Inicializaci�n del mapa
	map_ = new tmx::Map();
	///Carga del mapa dado un archivo .tmx
	bool success = map_->load(filename);

	///Informaci�n del tileset
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
		auto map_dimensions = map_->getTileCount();
		//Tama�o de los tiles del mapa
		auto tilesize = map_->getTileSize();

		///Cogemos todas las layers del archivo
		auto& map_layers = map_->getLayers();
		///Las recorremos una a una
		for (auto& layer : map_layers) {
			//Cogemos las capas que son solo tiles (no las de objetos)
			if (layer->getType() == tmx::Layer::Type::Tile) {

				auto* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());
				
				//Cogemos los tiles de la Layer
				auto& layer_tiles = tile_layer->getTiles();

				///Recorremos toda la matriz que contiene la informacion de la capa que acabamos de 
				//coger
				for (auto y = 0; y < map_dimensions.y; y++) {
					///Como est� en perspectiva isom�trica, vamos a guardar directamente 
					///la informaci�n de la posici�n de los tiles teniendo en cuenta dicha
					///perspectiva
					int auxY = (iniPos.getY() + ((tileSize/ 4) * y));
					int auxX = (iniPos.getX() - ((tileSize / 2) * y));
					for (auto x = 0; x < map_dimensions.x; x++) {

						int tileIndex = x + (y * map_dimensions.y);
						int gid = layer_tiles[tileIndex].ID;

						///Si el tile no es vac�o
						if (gid != 0) {
							Tile tile;
							//Lo guardamos en la posici�n del mapa que corresponda
							tile.worldPos_ = { (double)(auxX), (double)(auxY) };
							//Guardamos la posici�n del tile en el tilemap
							Vector2D aux = { (double)((gid-1) % tileset_.cols),(double)((gid-1) / tileset_.cols) };
							tile.tilesetPos_ = { aux.getX() * tileset_.tileWidth_, aux.getY() * tileset_.tileHeight_ };
							//Lo a�adimos en la lista de tiles
							tilesToRender.push_back(tile);
						}
						//Actualizamos la posici�n del mundo para el siguiente tile
						auxY += (tileSize / 4);
						auxX += (tileSize / 2);
					}

				}
			}
		}
	}

}

const void TiledMap::draw()
{
	for (Tile ob : tilesToRender) {
		tileset_.textureTileset_->render({ (int)ob.worldPos_.getX(), (int)ob.worldPos_.getY(),tileSize_, tileSize_ },
			{ (int)ob.tilesetPos_.getX(), (int)ob.tilesetPos_.getY(), tileset_.tileWidth_, tileset_.tileHeight_ });
	}
}
