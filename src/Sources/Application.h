#pragma once

#include "SDL.h"
#include "GameStateMachine.h"
#include "RandEquipGen.h"

using namespace std;

//class GameStateMachine;
//Clase que llamará al estado actual desde la máquina de estados
class Application
{
private:
	//Variables básicas de la aplicación
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	GameStateMachine* machine_ = nullptr;
	bool appClosed_ = false;

	//Constantes pantalla
	static const int winWidth_ = 1600;
	static const int winHeight_ = 900;

	//Métodos auxiliares para la constructora
	void initSDL();

	//Area en la que se encuentra el jugador (1 - 3 -> primera isla, 4 - 6 -> segunda isla)
	int currArea_ = 1;
	RandEquipGen* equipGen_;

public:
	Application(GameStateMachine* state=nullptr);
	~Application(); 
	void runApp();
	
	//Setters
	void endGame() { appClosed_ = true; };
	
	//Getters
	GameStateMachine* getStateMachine() { return machine_; };
	bool isRunning() { return !appClosed_; };
	int getWindowWidth() { return winWidth_; };
	int getWindowHeight() { return winHeight_; };
	SDL_Window* getWindow() { return window_; };
	SDL_Renderer* getRenderer() { return renderer_; };
	GameStateMachine* getGameStateMachine() { return machine_; };
	int getCurrArea() { return currArea_; };

	//Generators
	Equipment* genEquip() { return equipGen_->genEquip(); };
	Equipment* genEquip(equipType type) { return equipGen_->genEquip(type); };
};