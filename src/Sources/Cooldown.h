#pragma once
#include <iostream>
#include "SDL.h"

using namespace std;

class Cooldown {
public:
	//Constructora vacia
	Cooldown() {};
	//Constructora con duracion
	Cooldown(double duration) : duration_(duration), lastTick_(SDL_GetTicks()) {};
	//Destructora
	~Cooldown() {};

	void updateCooldown() {
		//Recoge 
		double currTick = SDL_GetTicks();

		//Comprueba que no se haya estado en pausa
		if (currTick - lastTick_ < PAUSE_COOLDOWN) {
			duration_ -= (currTick - lastTick_);
		}

		//Actualiza el último tick
		lastTick_ = currTick;
	};

	//Devuelve true si el cooldown está activo
	bool isCooldownActive() {
		if (duration_ <= 0) return false;
		else return true;
	};

	//Establece la duracion del cooldown
	void initCooldown(double duration) { 
		duration_ = duration;
		lastTick_ = SDL_GetTicks();
	};
	//Establece la duracion del cooldown
	void setDuration(double duration) { duration_ = duration; };
	//Método para terminar un coolDown
	void endCoolDown() { duration_ = 0; }
	//Establece la duracion del cooldown
	void setLastTick() { lastTick_ = SDL_GetTicks(); };
	//Te devuelve la duracion que le queda
	double getDuration() { return duration_; };
private:
	//Si la diferencia de ticks es mayor que PAUSE_COOLDOWN, no se resta duracion
	const double PAUSE_COOLDOWN = 200;
	//Duracion que queda de cooldown
	double duration_ = 0;
	//Último tick actualizado
	double lastTick_ = 0;
};