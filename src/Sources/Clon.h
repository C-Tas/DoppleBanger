#pragma once
#include "Collider.h"
#include "Resources.h"
#include "Enemy.h"
class Player;

const double DURATION_ = 2; //En segundos

class Clon : public Draw
{
public:
	//Liberation es el nivel de la habilidad liberaci�n: 0 no se tiene, 1 nivel 1, 2 nivel 2.
	Clon(Application* app, Point2D pos, Vector2D scale, Player* player) : Draw(app, pos, scale), player_(player) { initObject(); }
	~Clon() {};

	bool update();
	//void onCollider() {}; Eliminar si no va a heredar de collider

	void changeDuration(double dur) { duration_ = dur; } //En caso de que se pueda modificar la duraci�n
	void explode() { die(); }; //Crea una explosi�n y mata al clon (lo deletea)

private:
	int ad_ = 0;
	int cost_ = 100;
	int range_ = 0;
	int meleeRate_ = 0;
	bool explotion_ = false; //�Se tiene la habilidad?
	double spawnTime_ = 0; //Ticks cuando se le hizo spawn
	double meleeTime_ = 0; //Ticks cuando se atac� por �ltima vez
	double duration_ = 0; //Duraci�n del clon

	Actor* objective_ = nullptr;
	Player* player_ = nullptr;

	void init(int ad, int meleeRate, int lib) {
		spawnTime_ = SDL_GetTicks();
		duration_ = DURATION_;
		ad_ = (ad / 2) * lib;
		meleeRate = (meleeRate / 2) * lib;
	};

	virtual void initObject();
	void die();
};

