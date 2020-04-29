#pragma once
#include "Enemy.h"
class Pumpkin :
	public Enemy
{
private:
	uint wHSeed = app_->getWindowHeight() / 40;		//Tamaño de la semilla
	double seedVel = 700;							//Velocidad de la semilla
	double seedLife = 3;								//Vida del proyectil en segundos
	double explosionRange_ = 0;
	///<summary>Devuelve si hay un enemigo en rango y establece cual es el más cercano </summary>
	bool onDistRange();
	///<summary>Devuelve si hay un enemigo en rango melee y establece cual es el más cercano </summary>
	bool onMeleeRange();
	///<summary>Ataca a distancia </summary>
	void disAttack();
	///<summary>Inicializa el ataque</summary>
	void initObject();
	///<summary>Pierde el agro</summary>
	void lostAgro();
	///<summary>Inicializa las stats</summary>
	void initialStats();
	///<summary>Sigue al jugador o al clon</summary>
	void follow();
	///<summary>Move a la calabaza siguiendo al clon o al player</summary>
	void move(Point2D posToReach);
	///<summary>Metodo que realiza al colisionar</summary>
	void onCollider() { initExplosion(); }
	//Inicializa todas las animaciones
	void initAnims();
	//inicializa las recompenzas que la calabaza da
	virtual void initRewards();

#pragma region Anims
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_PUMPKIN_FRAME = 70;			//Ancho del frame, estándar para todas
	const int H_PUMPKIN_FRAME = 45;			//Alto del frame, estándar para todas
	const int FRAME_ACTION_SHOOT = 10;
	bool shooted_ = false;
	//Idle
	void initIdle();
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	//Idle derecha
	const int IDLE_R_FRAMES = 16;			//Frames de la animación
	const int IDLE_R_FRAME_RATE = 100;		//Frame rate
	//Idle hacia arriba
	const int IDLE_U_FRAMES = 16;			//Frames de la animación
	const int IDLE_U_FRAME_RATE = 100;		//Frame rate
	//Idle hacia izquierda
	const int IDLE_L_FRAMES = 16;			//Frames de la animación
	const int IDLE_L_FRAME_RATE = 100;		//Frame rate
	//Idle hacia abajo
	const int IDLE_D_FRAMES = 16;			//Frames de la animación
	const int IDLE_D_FRAME_RATE = 100;		//Frame rate

	//Attack
	void initAttack();
	vector<Anim> attackAnims_;
	vector<Texture*> attackTx_;
	//Attack derecha
	const int ATTACK_R_FRAMES = 16;			//Frames de la animación
	const int ATTACK_R_FRAME_RATE = 100;		//Frame rate
	//Attack hacia arriba
	const int ATTACK_U_FRAMES = 16;			//Frames de la animación
	const int ATTACK_U_FRAME_RATE = 100;		//Frame rate
	//Attack hacia izquierda
	const int ATTACK_L_FRAMES = 16;			//Frames de la animación
	const int ATTACK_L_FRAME_RATE = 100;		//Frame rate
	//Attack hacia abajo
	const int ATTACK_D_FRAMES = 16;			//Frames de la animación
	const int ATTACK_D_FRAME_RATE = 100;		//Frame rate
	//Explosion
	bool explosion_ = false;
	const int FRAME_ACTION_EXPLOSION = 14;
	void initExplosion();
	bool explosionAnim();
	vector<Anim> explosionAnims_;
	vector<Texture*> explosionTx_;
	//Explosion derecha
	const int EXPLOSION_R_FRAMES = 17;			//Frames de la animación
	const int EXPLOSION_R_FRAME_RATE = 30;		//Frame rate
	//Explosion hacia arriba
	const int EXPLOSION_U_FRAMES = 17;			//Frames de la animación
	const int EXPLOSION_U_FRAME_RATE = 30;		//Frame rate
	//Explosion hacia izquierda
	const int EXPLOSION_L_FRAMES = 17;			//Frames de la animación
	const int EXPLOSION_L_FRAME_RATE = 30;		//Frame rate
	//Explosion hacia abajo
	const int EXPLOSION_D_FRAMES = 17;			//Frames de la animación
	const int EXPLOSION_D_FRAME_RATE = 30;		//Frame rate

	//Movimiento
	void initMove();
	void updateDirVisEnemy();
	void shootAnim();
	vector<Anim> moveAnims_;
	vector<Texture*> moveTx_;
	//Movimiento derecha
	const int MOVE_R_FRAMES = 12;			//Frames de la animación
	const int MOVE_R_FRAME_RATE = 36;		//Frame rate
	//Movimiento hacia arriba
	const int MOVE_U_FRAMES = 12;			//Frames de la animación
	const int MOVE_U_FRAME_RATE = 36;		//Frame rate
	//Movimiento hacia izquierda
	const int MOVE_L_FRAMES = 12;			//Frames de la animación
	const int MOVE_L_FRAME_RATE = 36;		//Frame rate
	//Movimiento hacia abajo
	const int MOVE_D_FRAMES = 12;			//Frames de la animación
	const int MOVE_D_FRAME_RATE = 36;		//Frame rate

#pragma endregion

public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Pumpkin(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 } ):Enemy(app, pos, scale) {initObject();};
	//<summary>Constructor por copia</summary>
	Pumpkin(Pumpkin& other) :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Constructor por movimiento<summary>
	Pumpkin(Pumpkin&& other)noexcept :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Destructora<summary>
	~Pumpkin() {};
};

