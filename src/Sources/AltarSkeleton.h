#pragma once
#include "Skeleton.h"
#include "Altar.h"

//Enum que representa el estado de un mob que puede resucitar
enum class MOBSTATE
{
	ALIVE, DIE, RISEABLE, UNRISEABLE
};

class AltarSkeleton :
	public Skeleton
{
public:
	AltarSkeleton(Application* app, Vector2D pos, Vector2D scale, Altar* altar) :Skeleton(app, pos, scale), altarOwner_(altar) { initObject(); };
	void resurrect() { currState_ = STATE::IDLE; }
	virtual ~AltarSkeleton() {};
	virtual bool update();
	virtual void die();
private:
	virtual void initObject();
	void selectTarget();
	virtual void move(Vector2D posToReach);
	//Puntero al altar que pertence
	Altar* altarOwner_ = nullptr;
	//Estado del mob que tiene la habilidad de resucitar
	MOBSTATE mobState_ = MOBSTATE::RISEABLE;
};

