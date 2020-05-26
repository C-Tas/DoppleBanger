#pragma once
#include "Collider.h"
#include "Cooldown.h"


class Cleon;

enum class BARREL_STATE
{
	ASSEMBLING,
	READY,
	INIT_EXPLOTION,
	EXPLODING
};

class Barrel :
	public Collider
{
public:
	Barrel(Application* app, Vector2D pos, Vector2D scale, Cleon* cleon) : Collider(app, pos, scale), cleon_(cleon) { initObject(); };

	BARREL_STATE getBarrelState() { return currState_; }

	virtual bool update()override;
	virtual void onCollider() override;
private:
	//Puntero a Cleón
	Cleon* cleon_ = nullptr;
	//Rango de explosión del barril
	const double EXPL_BARREL_RANGE = 100;
	//Daño que produce el barril
	const int BARREL_DMG = 20;
	//Tiempo de vida del barril
	const double BARREL_TIME_LIFE = 4000;
	//Tiempo que tarda el barril en armarse
	const double BARREL_TIME_ACTIVE = 500;

	//Cooldown que representa cuando se autodestruye el barril
	Cooldown explosion_;
	//Cooldown que representa el tiempo en que se arma el barril
	Cooldown activeBarrel_;
	//Estado del barril
	BARREL_STATE currState_ = BARREL_STATE::ASSEMBLING;

	//Animaciones
		//Explosión
	Texture* explosionTex_;
	Anim explosionAnim_ = { 0,0,0,0,false };

	const int EXPLOTION_FRAMES = 11;			//Frames de la animación
	const int EXPLOTION_FRAME_RATE = 80;		//Frame rate
	const int EXPLOTION_H = 150;
	const int EXPLOTION_W = 150;
	const int EXPLOTION_ACTION = 3;


		//InitExplosión
	bool explote_ = false;
	bool applyDmg_ = false;
	Texture* mechaExplosionTex_;
	Anim mechaExplosionAnim_ = { 0,0,0,0,false };
	const int INIT_EXPLOTION_FRAMES = 6;			//Frames de la animación
	const int INIT_EXPLOTION_FRAME_RATE = 666;


	virtual void initObject()override;
	virtual void initAnims() override;

	//Aplica el daño a todos los enemigos cercanos al barril
	void applyRangeDmg();
	//
	void updateCooldowns();

	void initMecha();
	void initExplotion();
};

