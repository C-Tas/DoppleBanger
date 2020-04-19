#pragma once
#include "../tmxLite/Map.hpp"
#include <string>
#include "Texture.h"
#include "Vector2D.h"
#include "checkML.h"

using namespace std;

struct TilesetInfo {
	///<summary>Puntero a la textura del tileset del mapa</summary>
	Texture* textureTileset_ = nullptr;
	///<summary>Numero de filas en la textura del tileset</summary>
	int fils = 0;
	///<summary>Numero de columnas en la textura del tileset</summary>
	int cols = 0;
	///<summary>Tamaño en pixeles del alto de un tile en el tileset</summary>
	int tileHeight_ = 0;
	///<summary>Tamaño en pixeles del ancho de un tile en el tileset</summary>
	int tileWidth_ = 0;
};

///<summary>Struct con la información de cada tile</summary>
struct Tile { 
	///<summary>Posición en x e y del tile dentro de la textura</summary>
	Vector2D tilesetPos_ = { 0,0 };
	///<summary>Posicion en x e y de un tile en el mundo</summary>
	Vector2D worldPos_ = { 0,0 };
};

class TiledMap
{
public:
	TiledMap(const string & filename, Texture* tileset, int filsTileset, int colsTileset, int tileTilesetHeight_ , int tileTilesetWidth, Vector2D iniPos, int tileSize);
	~TiledMap() { delete map_; };
	///<summary>Método para pintar el mapa</summary>
	const void draw();
private:
	///<summary>Mapa que contiene la información del tilemap. Igual no es necesario mantenerlo durante
	///todo el tiempo puesto que solo se utiliza en la constructora. Por el momento se mantiene
	//por si es necesario cuando añadamos las colisiones</summary>
	tmx::Map* map_;
	TilesetInfo tileset_;

	//Tamaño al que queremos que se dibujen los tiles
	int tileSize_;

	///<summary>Vector que contiene los tiles a renderizar, siendo los primeros los de las
	///capas inferiores en tiled y empezando por la esquina superior izquierda
	///</summary>
	vector<Tile> tilesToRender;
};

