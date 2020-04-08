#pragma once

#include "Collider.h"
#include "Resources.h"
#include "Enemy.h"

const double DURATION_ = 2; //En segundos

class Clon : public Draw
{
public:
	//Liberation es el nivel de la habilidad liberación: 0 no se tiene, 1 nivel 1, 2 nivel 2.
	Clon(Application* app, Point2D pos, int ad, int meleeRate, int range, int liberation, Vector2D scale) : range_(range),
		Draw(app, app->getTextureManager()->getTexture(Resources::TextureId::Timon), pos, scale) { init(ad, meleeRate, liberation); };
	~Clon() {};

	bool update();
	//void onCollider() {}; Eliminar si no va a heredar de collider
	void changeDuration(double dur) { duration_ = dur; } //En caso de que se pueda modificar la duración
	void die();

private:
	int ad_ = 0;
	int cost_ = 100;
	int range_ = 0;
	int meleeRate_ = 0;
	double spawnTime_ = 0; //Ticks cuando se le hizo spawn
	double meleeTime_ = 0; //Ticks cuando se atacó por última vez
	double duration_ = 0; //Duración del clon

	Enemy* objective_ = nullptr;

	void init(int ad, int meleeRate, int lib) {
		spawnTime_ = SDL_GetTicks();
		duration_ = DURATION_;
		ad_ = (ad / 2) * lib;
		meleeRate = (meleeRate / 2) * lib;
	};
};

