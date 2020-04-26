#pragma once
#include "Actor.h"
#include "Resources.h"
#include "Enemy.h"
#include <list>

class Player;

const double DURATION_ = 2; //En segundos
const int CLON_TAUNT_RANGE = 500;

class Clon : public Actor
{
public:
	//Liberation es el nivel de la habilidad liberaci�n: 0 no se tiene, 1 nivel 1, 2 nivel 2.
	Clon(Application* app, Point2D pos, Vector2D scale, Player* player) : 
		Actor(app, pos, scale), player_(player) { initObject(); initAnim(); };
	~Clon() {};

	bool update();
	void onCollider() {};

	void shoot(Vector2D dir);
	void changeDuration(double dur) { duration_ = dur; }	//En caso de que se pueda modificar la duraci�n
	void initSelfDestruction();

	void die();
	//Devuelve el coste de maná de la habilidad
	int getCost() { return cost_; };

private:
	int meleeDmg_ = 0;
	int distDmg_ = 0;
	int cost_ = 10;
	int range_ = 0;
	int meleeRate_ = 0;
	double distRange_ = 0;
	double buletSpeed_ = 0;
	double spawnTime_ = 0; //Ticks cuando se le hizo spawn
	double meleeTime_ = 0; //Ticks cuando se atac� por �ltima vez
	double duration_ = 0; //Duraci�n del clon
	bool alive_ = true;

	Actor* objective_ = nullptr;
	Player* player_ = nullptr;
	list<Enemy*> enemies_;

	virtual void initObject();
	void taunt();

#pragma region Animaciones
	virtual void initAnim();

	const int W_H_CLON_FRAME = 100;

	//Autodestrucción
	bool selfDestruct_ = false;						//Para disparar una sola vez en el frame adecuado
	vector<Anim> selfDestructAnims_;				//Vector de las animaciones
	vector<Texture*> selfDestructTx_;				//Vector de las texturas
	//Autodestrucción derecha
	const int SELFDESTRUCT_R_FRAMES = 8;			//Frames de la animación
	const int SELFDESTRUCT_R_FRAME_RATE = 100;		//Frame rate
	//Autodestrucción hacia arriba
	const int SELFDESTRUCT_U_FRAMES = 8;			//Frames de la animación
	const int SELFDESTRUCT_U_FRAME_RATE = 100;		//Frame rate
	//Autodestrucción hacia izquierda
	const int SELFDESTRUCT_L_FRAMES = 8;			//Frames de la animación
	const int SELFDESTRUCT_L_FRAME_RATE = 100;		//Frame rate
	//Autodestrucción hacia abajo
	const int SELFDESTRUCT_D_FRAMES = 8;			//Frames de la animación
	const int SELFDESTRUCT_D_FRAME_RATE = 100;		//Frame rate
#pragma endregion
};