#pragma once
#include "GameObject.h"

class Application;
class Player;

//Callbacks
//Callback para cambiar de zona. Se necesita el player para cosérvarlo si se cambia del barco a las islas y viceversa
using ChangeZone = void(Application * app, int island); 

class Trigger : public GameObject
{
protected:
	SDL_Rect triggerArea_;
	ChangeZone* cbZone_ = nullptr;
	int island_ = 1;

public:
	Trigger() : triggerArea_({0,0,0,0}) {};

	///<summary> Constructora de trigger para cambiar de zona. Hay que pasar al player para conservarlo en la siguiente zona</summary>
	Trigger(Application* app ,SDL_Rect triggerArea, Point2D pos, Vector2D scale, ChangeZone* cbZone, Player* player, int island)
		:GameObject(app,pos, scale), triggerArea_(triggerArea), cbZone_(cbZone), island_(island){};

	bool update() { return false; }
	void onOverlap() {
		if (cbZone_ != nullptr) cbZone_(app_, island_); //Callback de cambiar de zona

		//Si se quieren crear más callBacks añadir aquí la condición para ejecutarlos
		//	if(callback != nullptr) callback(...); de manera que solo haya un método overlap
	};

	const SDL_Rect getTriggerArea() { return triggerArea_; };
	void setTriggerArea(SDL_Rect newArea) { triggerArea_ = newArea; };
};