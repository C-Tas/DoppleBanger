#pragma once
#include <string>
#include "Texture.h"
#include "Vector2D.h"
#include "checkML.h"
#include <list>
#include "../tmxLite/TileLayer.hpp"
#include "../tmxLite/Map.hpp"
#include "Application.h"

enum class tileType{Wall, Obstacle, EndObstacle, Undefined};

class Obstacle;
class PlayState;
class GameManager;
class CollisionCtrl;

using namespace std;

struct TilesetInfo {
	///<summary>Puntero a la textura del tileset del mapa</summary>
	Texture* textureTileset_ = nullptr;
	///<summary>Numero de filas en la textura del tileset</summary>
	int fils = 0;
	///<summary>Numero de columnas en la textura del tileset</summary>
	int cols = 0;
	///<summary>Tama�o en pixeles del alto de un tile en el tileset</summary>
	int tileHeight_ = 0;
	///<summary>Tama�o en pixeles del ancho de un tile en el tileset</summary>
	int tileWidth_ = 0;
};

///<summary>Struct con la informaci�n de cada tile</summary>
struct Tile { 
	///<summary>Posici�n en x e y del tile dentro de la textura</summary>
	Vector2D tilesetPos_ = { 0,0 };
	///<summary>Posicion en x e y de un tile en el mundo</summary>
	Vector2D worldPos_ = { 0,0 };
};

class TiledMap
{
public:
	///<summary>Constructora del tilemap, necesita la direccion del archivo de tiled(.tmx), la textura del tileset
	//cuantas filas y cuantas columnas tiene ese tileset, el ancho y el alto de los tiles, la posici�n donde quieres que se pinte la esquina superior
	//izquierda del mapa (en perspectiva isom�trica) y el tama�o con el que queremos pintar los tiles</summary>
	TiledMap(Application* app_, PlayState* state,const string& filename, int tileTilesetHeight_, int tileTilesetWidth, int tileSize, Texture* tileset = nullptr, int filsTileset = 1 , int colsTileset = 1 ,
		Vector2D iniPos = Vector2D(0, 0), const list<int>& idCollisionTiles = { 1 }, const list<int>& idWallTiles = {});
	
	///<summary>Destructora del mapa, borra todos los obstaculos creados</summary>
	~TiledMap();

	///<summary>M�todo para pintar el mapa</summary>
	const void draw();

	Vector2D TileToPos(Vector2D tile);
	Vector2D PosToTile(Vector2D pos);

private:
	CollisionCtrl* collisionCtrl_ = nullptr;
	GameManager* gm_ = nullptr;
	///<summary>Puntero a la aplicaci�n (Para crear objetos de tipo Obstacle)</summary>
	Application* app_ = nullptr;
	///<summary>Tileset del mapa que estamos cargando</summary>
	TilesetInfo tileset_;
	//<summary>Tama�o al que queremos que se dibujen los tiles</summary>
	int tileSize_;
	///<summary>Vector que contiene la posici�n desde la que se empieza a pintar el mapa</summary>
	Vector2D iniPos_;
	///<summary>Lista que contiene los id de los tiles que van a tener colision en este mapa</summary>
	list<int>idCollisionTiles_;
	///<summary>Lista que contiene los id de los tiles que son paredes en este mapa</summary>
	list<int>idWallTiles_;
	///<summary>Lista que contiene los tiles a renderizar, siendo los primeros los de las
	///capas inferiores en tiled y empezando por la esquina superior izquierda</summary>
	list<Tile> tilesToRender;
	///<summary>Lista que contiene los objetos de tipo obstacle del mapa. Todos los objetos que el player no
	///vaya a poder atravesar deben de ir en esta lista</summary>
	list<Obstacle*> mapObstacles_;
	///<summary>Lista que contiene las paredes del juego. Los elementos que est�n en esta lista deben de
	///estar tambi�n incluidos a mapObstacles</summary>
	list<Obstacle*> map_Walls;
	///<summary>Lista que nos ayuda a la hora de debuggear las colisiones, descomentarla en todos los m�todos para visualizar
	//los colliders (no hay distinci�n entre los colliders que destruyen balas y los que no puede atravesar el jugador)</summary>
	//list<Obstacle*> collidersToRender_;
	///<summary>Puntero al estado en el que est� el mapa</summary>
	PlayState* state_ = nullptr;

	void setObstacleType(int gid, Obstacle* obstacle);
	
#pragma region ObjectsSize
	const double W_KRAKEN = app_->getWindowWidth() / 4;
	const double H_KRAKEN = app_->getWindowHeight() / 2.5;

	const double W_MONKEY = app_->getWindowWidth() / 12;
	const double H_MONKEY = app_->getWindowHeight() / 5;

	const double W_SKELETON = app_->getWindowWidth() / 12;
	const double H_SKELETON = app_->getWindowHeight() / 5;

	const double W_WOLF= app_->getWindowWidth() / 20;
	const double H_WOLF = app_->getWindowHeight() / 15;

	const double W_PUMPKIN = app_->getWindowWidth() / 20;
	const double H_PUMPKIN = app_->getWindowHeight() / 15;

	const double W_CRAB = app_->getWindowWidth() / 20;
	const double H_CRAB = app_->getWindowHeight() / 15;

	const double W_ENEMYPIRATE = app_->getWindowWidth() / 20;
	const double H_ENEMYPIRATE = app_->getWindowHeight() / 15;

	const double W_NPC_CHEF = app_->getWindowWidth() / 20;
	const double H_NPC_CHEF = app_->getWindowHeight() / 8;

	const double W_NPC_MORTY= app_->getWindowWidth() / 20;
	const double H_NPC_MORTY= app_->getWindowHeight() / 8;

	const double W_NPC_NAMI = app_->getWindowWidth() / 12;
	const double H_NPC_NAMI = app_->getWindowHeight() / 6;

	//Dimensiones de las entidades
	const double W_PLAYER = app_->getWindowWidth() / 12;
	const double H_PLAYER = app_->getWindowHeight() / 6;

	const double W_CHEST = app_->getWindowWidth() / 12.8;
	const double H_CHEST = app_->getWindowWidth() / 12.8;


#pragma endregion
#pragma region TilesIdentifiers
	//Primer tile con forma de cubo
	const int FIRST_CUBE_TILE = 0;
	//�ltimo tile con forma de cubo 
	const int LAST_CUBE_TILE = 76;

	//Listas con los tiles de los bordes (siendo la primera textura del tile el 0)
	const list<int> UPLEFT_BORDER_TILES = {92,120};
	const list<int> UPRIGHT_BORDER_TILES = {93,121};
	const list<int> DOWNLEFT_BORDER_TILES = {95,123};
	const list<int> DOWNRIGHT_BORDER_TILES = {94,122};

	//Lista con los tiles de calaveras
	const list <int> SKULL_TILES = { 161,162,163 };

	//Identificadores de los tiles con tumbas
	const int TOMB1_TILE = 178;
	const int TOMB2_TILE = 179;

	//Identificadores con los tiles de las rocas
	const int LITTLEROCK_TILE = 180;
	const int BIGROCK_TILE = 181;

	//Arbustos
	const int BUSH1_TILE = 247;
	const list <int>BUSH_TYPE2_TILE = { 251,252,253,254,255,256};

	//Troncos de los �rboles
	const list <int> TRUNK_TILES = {286,287,288,289,290,291,292,293,294,295,296,297,298};


#pragma endregion
	///<summary>M�todo auxiliar para crear un tile que no se pueda atravesar (isom�trico) (no ocupa todo el tama�o del tile)
	//si el gid de ese tile corresponde con alguno de las paredes lo a�ade tambi�n a la correspondiente lista</summary>
	void addIsometricObstacle(Tile tile, int gid, tileType tileType);
	///<summary>M�todo auxiliar para crear un tile que no se pueda atravesar (ortogonal) (colision == tama�o de dibujado del tile)</summary>
	void addOrthogonalObstacle(Tile tile);
	
	///<summary>M�todo auxiliar que crea una layer de tiles isom�tricas (y las almacena para dibujarlas)</summary>
	void createIsometricTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions, string layerName);
	void createIsometricPathLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions);
	///<summary>M�todo auxiliar que crea una layer de tiles �rtogonales</summary>
	void createOrthogonalTileLayer(vector<tmx::TileLayer::Tile> layer_tiles, tmx::Vector2u map_dimensions, tmx::Vector2u tilesize);
	
	///<summary>M�todo auxiliar para crear todos los objetos de una capa
	//seg�n el objectType que le pasemos(nombre de la capa), crear� objetos de un tipo u otro</summary>
	void createObjects(vector<tmx::Object> object_tiles, tmx::Vector2u tilesize, string objectType);
	///<summary>M�todo complementario a createObjects que, seg�n el objectType(nombre de la capa)
	///que le pases te crea un objeto de dicho tipo</summary>
	void createElement(Vector2D pos, string objectType);
	///<summary>Crea un mapa en perspectiva isom�trica (niveles del juego)</summary>
	void createIsometricMap(const tmx::Map & map_);
	///<summary>Crea un mapa en perspectiva ortogonal (shipState)</summary>
	void createOrthogonalMap(const tmx::Map& map_);
};