#pragma once
#include <string>
#include "Texture.h"
#include "Vector2D.h"
#include "checkML.h"
#include "Application.h"
#include <list>
#include "Obstacle.h"
#include "../tmxLite/TileLayer.hpp"
#include "../tmxLite/Map.hpp"
#include "PlayState.h"

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
	TiledMap(Application* app_, PlayState* state,const string& filename, int tileTilesetHeight_, int tileTilesetWidth, int tileSize, Texture* tileset = nullptr, int filsTileset = 1 , int colsTileset = 1 ,
		 Vector2D iniPos = Vector2D(0,0),  const list<int>& idCollisionTiles = {1});
	
	///<summary>Destructora del mapa, borra todos los obstaculos creados</summary>
	~TiledMap();
	
	///<summary>Método para pintar el mapa</summary>
	const void draw();
private:
	///<summary>Puntero a la aplicación (Para crear objetos de tipo Obstacle)</summary>
	Application* app_ = nullptr;
	///<summary>Tileset del mapa que estamos cargando</summary>
	TilesetInfo tileset_;
	//<summary>Tamaño al que queremos que se dibujen los tiles</summary>
	int tileSize_;
	///<summary>Vector que contiene la posición desde la que se empieza a pintar el mapa</summary>
	Vector2D iniPos_;
	///<summary>Lista que contiene los id de los tiles que van a tener colision en este mapa</summary>
	list<int>idCollisionTiles_;
	///<summary>Lista que contiene los tiles a renderizar, siendo los primeros los de las
	///capas inferiores en tiled y empezando por la esquina superior izquierda</summary>
	list<Tile> tilesToRender;
	///<summary>Lista que contiene los objetos de tipo obstacle del mapa</summary>
	list<Obstacle*> mapObstacles_;
	///<summary>Puntero al estado en el que está el mapa</summary>
	PlayState* state_ = nullptr;
	
#pragma region ObjectsSize
	const int W_MONKEY = app_->getWindowWidth() / 20;
	const int H_MONKEY = app_->getWindowHeight() / 15;

	const int W_WOLF= app_->getWindowWidth() / 20;
	const int H_WOLF = app_->getWindowHeight() / 15;

	const int W_CRAB = app_->getWindowWidth() / 20;
	const int H_CRAB = app_->getWindowHeight() / 15;

	const int W_ENEMYPIRATE = app_->getWindowWidth() / 20;
	const int H_ENEMYPIRATE = app_->getWindowHeight() / 15;


	//Dimensiones de las entidades
	const int W_PLAYER = app_->getWindowWidth() / 40;
	const int H_PLAYER = app_->getWindowHeight() / 15;

#pragma endregion

	
	///<summary>Método auxiliar para crear un tile que no se pueda atravesar (isométrico) (no ocupa todo el tamaño del tile)</summary>
	void addIsometricObstacle(Tile tile);
	///<summary>Método auxiliar para crear un tile que no se pueda atravesar (ortogonal) (colision == tamaño de dibujado del tile)</summary>
	void addOrthogonalObstacle(Tile tile);
	
	///<summary>Método auxiliar que crea una layer de tiles isométricas (y las almacena para dibujarlas)</summary>
	void createIsometricTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions);
	///<summary>Método auxiliar que crea una layer de tiles órtogonales</summary>
	void createOrthogonalTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions, tmx::Vector2u tilesize);
	
	///<summary>Método auxiliar para crear todos los objetos de una capa
	//según el objectType que le pasemos(nombre de la capa), creará objetos de un tipo u otro</summary>
	void createObjects(vector<tmx::Object> object_tiles, tmx::Vector2u tilesize, string objectType);
	///<summary>Método complementario a createObjects que, según el objectType(nombre de la capa)
	///que le pases te crea un objeto de dicho tipo</summary>
	void createElement(Vector2D pos, string objectType);

	///<summary>Crea un mapa en perspectiva isométrica (niveles del juego)</summary>
	void createIsometricMap(const tmx::Map & map_);
	///<summary>Crea un mapa en perspectiva ortogonal (shipState)</summary>
	void createOrthogonalMap(const tmx::Map& map_);

};

