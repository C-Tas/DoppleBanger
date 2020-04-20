#pragma once
#include <string>
#include "Texture.h"
#include "Vector2D.h"
#include "checkML.h"
#include "Application.h"
#include <list>
#include "Obstacle.h"

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
	///<summary>Constructora del tilemap, necesita la direccion del archivo de tiled(.tmx), la textura del tileset
	//cuantas filas y cuantas columnas tiene ese tileset, el ancho y el alto de los tiles, la posición donde quieres que se pinte la esquina superior
	//izquierda del mapa (en perspectiva isométrica) y el tamaño con el que queremos pintar los tiles</summary>
	TiledMap(Application* app_, const string& filename, Texture* tileset, int filsTileset, int colsTileset, int tileTilesetHeight_, int tileTilesetWidth, Vector2D iniPos, int tileSize, const list<int>& idCollisionTiles);
	~TiledMap();
	
	///<summary>Método para pintar el mapa</summary>
	const void draw();
private:
	
	///<summary>Tileset del mapa que estamos cargando</summary>
	TilesetInfo tileset_;
	
	//<summary>Tamaño al que queremos que se dibujen los tiles</summary>
	int tileSize_;
	
	///<summary>Lista que contiene los tiles a renderizar, siendo los primeros los de las
	///capas inferiores en tiled y empezando por la esquina superior izquierda</summary>
	list<Tile> tilesToRender;
	
	///<summary>Lista que contiene los objetos de tipo obstacle del mapa</summary>
	list<Obstacle*> mapObstacles_;
};

