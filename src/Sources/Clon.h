#pragma once
#include "Actor.h"
#include "Resources.h"
#include "Enemy.h"
#include <list>

class Player;


class Clon : public Actor
{
public:
	//Liberation es el nivel de la habilidad liberaci�n: 0 no se tiene, 1 nivel 1, 2 nivel 2.
	Clon(Application* app, Point2D pos, Vector2D scale, Player* player) : 
		Actor(app, pos, scale), player_(player) { initObject(); };
	~Clon() {};

	bool update();
	void onCollider() {};

	void shoot();
	void changeDuration(double dur) { duration_ = dur; }	//En caso de que se pueda modificar la duraci�n
	
	void initSelfDestruction();
	void initVanish();
	void addEnemy(GameObject* enemy) { 
		enemies_.push_back(static_cast<Enemy*>(enemy)); 
	}
	//<summary>Método para iniciar la animación de disparo del clon, recibe un vector2D que es la dirección hacia la que dispara</summary>
	void initShoot(Vector2D dir);

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
	double buletSpeed_ = 1000;
	double spawnTime_ = 0; //Ticks cuando se le hizo spawn
	double meleeTime_ = 0; //Ticks cuando se atac� por �ltima vez
	double duration_ = 0; //Duraci�n del clon
	bool alive_ = true;


	const double DURATION_ = 10; //En segundos
	const int CLON_TAUNT_RANGE = 500;

	Actor* objective_ = nullptr;
	Player* player_ = nullptr;
	list<Enemy*> enemies_;
	//<summary>Variable que guarda la dirección hacia la que va a disparar el clon
	//Se actualiza al llamar al initShoot desde el player</summary>
	Vector2D shootingDir_ = {0,0};

	virtual void initObject();
	void taunt();

#pragma region Animaciones
	virtual void initAnim();
	int frameAction_ = 0;
	
	void initIdle();
	void initMelee();
	void meleeAnim();


	const int W_H_CLON_FRAME = 100;

	//Idle
	vector<Anim> idleAnims_;                //Vector de las animaciones
	vector<Texture*> idleTx_;               //Vector de las texturas
	//Idle derecha
	const int IDLE_R_FRAMES = 4;			//Frames de la animación
	const int IDLE_R_FRAME_RATE = 500;		//Frame rate
	//Idle hacia arriba
	const int IDLE_U_FRAMES = 2;			//Frames de la animación
	const int IDLE_U_FRAME_RATE = 500;		//Frame rate
	//Idle hacia izquierda
	const int IDLE_L_FRAMES = 4;			//Frames de la animación
	const int IDLE_L_FRAME_RATE = 500;		//Frame rate
	//Idle hacia abajo
	const int IDLE_D_FRAMES = 2;			//Frames de la animación
	const int IDLE_D_FRAME_RATE = 500;		//Frame rate

	//Melee
	bool attacked_ = false;					//Para atacar una sola vez en el frame adecuado
	vector<Anim> meleeAnims_;				//Vector de las animaciones
	vector<Texture*> meleeTx_;				//Vector de las texturas
	//Melee derecha
	const int MELEE_R_FRAMES = 7;			//Frames de la animación
	const int MELEE_R_FRAME_RATE = 100;		//Frame rate
	//Melee hacia arriba
	const int MELEE_U_FRAMES = 5;			//Frames de la animación
	const int MELEE_U_FRAME_RATE = 200;		//Frame rate
	//Melee hacia izquierda
	const int MELEE_L_FRAMES = 7;			//Frames de la animación
	const int MELEE_L_FRAME_RATE = 100;		//Frame rate
	//Melee hacia abajo
	const int MELEE_D_FRAMES = 7;			//Frames de la animación
	const int MELEE_D_FRAME_RATE = 100;		//Frame rate

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

	//Disparo
	vector<Anim> shootAnims_;				//Vector de las animaciones
	vector<Texture*> shootTx_;				//Vector de las texturas
	//Disparo derecha
	const int SHOOT_R_FRAMES = 5;			//Frames de la animación
	const int SHOOT_R_FRAME_RATE = 100;		//Frame rate
	const int SHOOT_R_SHOOTINGFRAME = 1;	//Frame en el que se realiza el disparo
	//Disparo hacia arriba
	const int SHOOT_U_FRAMES = 8;			//Frames de la animación
	const int SHOOT_U_FRAME_RATE = 40;		//Frame rate
	const int SHOOT_U_SHOOTINGFRAME = 2;	//Frame en el que se realiza el disparo

	//Disparo hacia izquierda
	const int SHOOT_L_FRAMES = 5;			//Frames de la animación
	const int SHOOT_L_FRAME_RATE = 100;		//Frame rate
	const int SHOOT_L_SHOOTINGFRAME = 1;	//Frame en el que se realiza el disparo
	//Disparo hacia abajo
	const int SHOOT_D_FRAMES = 8;			//Frames de la animación
	const int SHOOT_D_FRAME_RATE = 40;		//Frame rate
	const int SHOOT_D_SHOOTINGFRAME = 2;	//Frame en el que se realiza el disparo

	//Vector que contiene los frames en los que se dispara en las distintas animaciones de disparo
	vector<int>shootingFrame_;

	//Desaparicion
	vector<Anim> vanishAnims_;				//Vector de las animaciones
	vector<Texture*> vanishTx_;				//Vector de las texturas
	//Desaparicion derecha
	const int VANISH_R_FRAMES = 5;			//Frames de la animación
	const int VANISH_R_FRAME_RATE = 100;		//Frame rate
	
	//Desaparicion  arriba
	const int VANISH_U_FRAMES = 5;			//Frames de la animación
	const int VANISH_U_FRAME_RATE = 100;		//Frame rate


	//Desaparicion  izquierda
	const int VANISH_L_FRAMES = 5;			//Frames de la animación
	const int VANISH_L_FRAME_RATE = 100;		//Frame rate
	
	//Desaparicion abajo
	const int VANISH_D_FRAMES = 5;			//Frames de la animación
	const int VANISH_D_FRAME_RATE = 100;		//Frame rate




	



#pragma endregion
};