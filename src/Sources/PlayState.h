#pragma once
#include "GameState.h"
#include "CollisionCtrl.h"
#include <list>

class CollisionCtrl;
class HUD;
class Player;
class Enemy;
class Obstacle;

class PlayState : public GameState
{
public:
	///<summary>Constructora PlayState</summary>
	PlayState(Application* app = nullptr) : GameState(app) { initState(); };
	///<summary>Destructora</summary>
	virtual ~PlayState() {};

	//Método necesario para dibujar los textbox por encima del juego
	virtual void draw()const;
	///<summary>Llama al update del CollisionManager</summary>
	virtual void update();

	///<summary>A�ade un objeto a la lista enemies_, objectsToRender y gameObjects_</summary>
	void addEnemy(Enemy* obj);
	///<summary>Quita un objeto a la lista enemies_, objectsToRender y gameObjects_</summary>
	void removeEnemy(Enemy* obj);
	///<summary>Comprueba las posibles acciones del jugador</summary>
	void checkPlayerActions();
	///<summary>Comprueba si el jugador ha hecho click en algún enemigo, y de ser el caso, devuelve el que se renderiza el último</summary>
	Enemy* checkAttack();
	///<summary>Encuentra al enemigo más cercano a una posición</summary>
	Enemy* findClosestEnemy(Point2D pos);
	///<summary>Comprueba colisiones con los enemigos y devuelve el primer enemigo en caso de haber colisión</summary>
	Enemy* collidesWithEnemy(Point2D pos, Vector2D scale) {};

protected:
	Point2D playerEntry_ = Vector2D(0, 0);
	//Singleton de colisiones
	CollisionCtrl* collisionCtrl_ = nullptr;
	Player* player_ = nullptr;
	HUD* hud_ = nullptr;
	list<Obstacle*> obstacles_;
	list<Enemy*> enemies_;

	virtual void initState();
};