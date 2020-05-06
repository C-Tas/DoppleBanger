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
	const double KIRIN_DMG = 50;
	const double KIRIN_CD = 1000;
	const double KIRIN_RANGE_ATTACK = 200;
#pragma endregion

#pragma region ANIMS
	//Kirin
	Draw* kirinA = nullptr;
	Anim kirinAnim_ = { 0,0,0,0,false };
	vector<Anim> kirinAnims_;
	vector<Texture*> kirinTx_;
	const int KIRIN_FRAMES = 7;				//Frames de la animaci�n
	const int KIRIN_FRAME_RATE = 500;		//Frame rate
	const int W_FRAME_KIRIN = 128;
	const int H_FRAME_KIRIN = 512;
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
	//inicializa el ataque kirin
	void kirin();
	//Inicializa la animaci�n del kirin
	void initKirinAnim();
#pragma region teleport
	//Representa el rango que se usa para determinar si el enemigo est� muy cerca
	const double RANGE_TO_TP = 100;
	//Devuelve true si el player est� dentro del rango que se considera cerca del magordito
	inline bool enemyIsTooClose();
	//CD para realizar el teleport en ms
	const double TP_CD = 2000; 
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