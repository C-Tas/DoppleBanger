#pragma once
#include "Enemy.h"
#include "Altar.h"
#include "GameManager.h" //Para setear el actual enemigo del magordito al perder el agro

class Magordito : public Enemy {
public:
	Magordito(Application* app = nullptr, Point2D pos = { 0, 0 }, Vector2D scale = { 0, 0 }) : 
		Enemy(app, pos, scale) { initObject(); };

	~Magordito() {}
	virtual bool update();
	virtual void onCollider() {};
	virtual void initialStats();
	virtual void initRewards();
	void teleport();
	inline bool isAlive() { return currState_ == STATE::DYING ? false : true; }
	//Agrega un altar al magordio
	inline void setAltar(Altar* altar) { altars.push_back(altar); }
	virtual void lostAggro();
private:
	//puntero al player
	Player* player_ = nullptr;
	//Vector de altares
	vector<Altar*> altars;
	#pragma region Kirin
	double lastKirin_ = 0;
	const double AREA_DMG_W = 100;
	const double AREA_DMG_H = 100;
	const double KIRIN_CD = 2;
	const double KIRIN_RANGE_ATTACK = 500;
#pragma endregion

#pragma region ANIMS
	//Inicia la animación
	void initIdle();
	void initTeleport();
	void initKirinAnim();

	//Gestor de animacion
	void teleportAnim();
	void kirinAnim();

	bool firstAttack = true;
	bool firstIdle = true;

	const int W_H_FRAME = 100;
	//Idle
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	const int IDLE_FRAMES = 7;
	const int IDLE_FRAME_RATE = 200;

	//Viaje Astral
	vector<Anim> tpAnims_;
	vector<Texture*> tpTx_;
	const int TP_FRAMES = 13;
	const int TP_FRAME_RATE = 90;

	//Kirin
	vector<Anim> kirinAnims_;
	vector<Texture*> kirinTx_;
	bool kirined_ = false;				//Para llamar al metodo kirin() una sola vez
	const int KIRIN_ACTION = 4;
	const int KIRIN_FRAMES = 8;
	const int KIRIN_FRAME_RATE = 200;	//Frame rate

	//Calcula hacia dónde mira en función del player
	virtual void updateDirVisObjective(GameObject* objective);
#pragma endregion

	//Posiciones de los puntos de teletransporte
	Point2D MagorditoSpots_[5] {
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	};

	//Inicializa objetos
	virtual void initObject();
	//Inicializa animaciones
	virtual void initAnims();
	virtual void updateCooldowns();
	//inicializa el ataque kirin
	void kirin();
#pragma region teleport
	//Representa el rango que se usa para determinar si el enemigo est� muy cerca
	const double RANGE_TO_TP = 100;
	//Devuelve true si el player est� dentro del rango que se considera cerca del magordito
	inline bool enemyIsTooClose();
	//CD para realizar el teleport en ms
	const double TP_CD = 2; 
	//�ltimo TP hecho
	double lastTeleport_ = 0;
	//Vector con las posiciones a las que se puede teleportar
#pragma endregion

#pragma region Constantes
	//Animacion idle de Magordito
	const int NUM_FRAMES_IDLE = 0;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const uint W_FRAME_IDLE = 0;
	const uint H_FRAME_IDLE = 0;
	const int FRAME_RATE_IDLE= 0;
	const string NAME_IDLE = "idle";

	//Animacion del teletransporte (junto a invocaci�n al final)
	const int NUM_FRAMES_TELEPORT = 0;
	const int NUM_FRAMES_ROW_TELEPORT = 0;
	const uint W_FRAME_TELEPORT = 0;
	const uint H_FRAME_TELEPORT = 0;
	const int FRAME_RATE_TELEPORT = 0;
	const string NAME_TELEPORT = "teleport";
#pragma endregion
};