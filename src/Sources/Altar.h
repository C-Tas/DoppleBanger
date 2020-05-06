#pragma once
#include <vector>
#include "Draw.h"
#include "Enemy.h"
#include "Clon.h"	//Para agregar los mobs a la lista de enemigos del clon


class AltarSkeleton;

class Altar : public Draw
{
public:
	Altar(Application* app, Vector2D pos, Vector2D scale) :Draw(app, pos, scale) { initObject(); };
	Altar(Application* app, Vector2D pos, Vector2D scale,int numMobs) :Draw(app, pos, scale),numMobs_(numMobs) { initObject(); };
	~Altar() { mobs.clear(); };
	virtual bool update();
	//Activa la resurreción de este altar
	void activeResurrect() { resurrect_ = true; }
	//Desactiva la resurreción de mobs 
	void deactivateResurrect() { resurrect_ = false; }
	//Crea los esqueletos 
	void createMobs(PlayState* playState);
	//Determina si un esqueleto está fuera de rango de resurreción
	bool outRange(SDL_Rect skeletonRect);
	//Devuelve true si los mobs pueden resucitar
	bool canResurrect() { return resurrect_; }
	//Setea al clon los enemigos si son invocados después del taunt
	void setEnemyToMobs(Clon* enemy);
	//Devuelve true si quedan mobs vivos en este altar
	bool mobsAlive();
private:
	//puntero al magordito
	Enemy* magordito_ = nullptr;
	//Bool que representa si se puede resucitar a los mobs de este altar
	bool resurrect_ = false;
	//vector que representa los mobs asociados al altar
	vector <AltarSkeleton*> mobs;
	//Variable que representa la cantidad de mobs a crear en este altar
	int numMobs_ = 1;
	//Variable que representa el rango del resurrección del altar
	const double ALTAR_RANGE = 100;
	//constantes que representa la anchura del esqueleto
	const double SKELETON_W = 45;
	//constantes que representa la altura del esqueleto
	const double SKELETON_H = 75;
	//inicializa al altar
	virtual void initObject();
};

