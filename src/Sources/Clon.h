#pragma once

#include "Collider.h"
#include "Resources.h"

const double DURATION_ = 2; //En segundos

class Clon : public Draw
{
public:
	//Liberation es el nivel de la habilidad liberación: 0 no se tiene, 1 nivel 1, 2 nivel 2.
	Clon(Application* app, Point2D pos, int ad, int meleeRate, int liberation, bool explotion, Vector2D scale) : explotion_(explotion),
		Draw(app, app->getTextureManager()->getTexture(Resources::TextureId::Timon), pos, scale) { init(ad, meleeRate, liberation); };
	~Clon() {};

	bool update();
	//void onCollider() {}; Eliminar si no va a heredar de collider

	void changeDuration(double dur) { duration_ = dur; } //En caso de que se pueda modificar la duración
	void explode() { die(); }; //Crea una explosión y mata al clon (lo deletea)

private:
	int ad_ = 0;
	int cost_ = 100;
	int range_ = 0;
	int meleeRate_ = 0;
	bool explotion_ = false; //¿Se tiene la habilidad?
	double timeSpawn_ = 0; //Ticks cuando se le hizo spawn
	double duration_ = 0; //Duración del clon

	void init(int ad, int meleeRate, int lib) {
		timeSpawn_ = SDL_GetTicks();
		duration_ = DURATION_;
		ad_ = (ad / 2) * lib;
		meleeRate = (meleeRate / 2) * lib;
	};

	void die();
};

