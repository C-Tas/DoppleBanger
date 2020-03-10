#pragma once

#include "SDL.h"
#include "GameStateMachine.h"
#include "RandEquipGen.h"
#include "TextureManager.h"
using namespace std;

//class GameStateMachine;
//Clase que llamar� al estado actual desde la m�quina de estados
class Application
{
private:
	//Variables b�sicas de la aplicaci�n
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	GameStateMachine* machine_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	RandEquipGen* equipGen_ = nullptr;
	
	bool appClosed_ = false;

	//Constantes pantalla
	static const int winWidth_ = 1600;
	static const int winHeight_ = 900;

	//M�todos auxiliares para la constructora
	void initSDL();
	void initResources();
	void closeResources();

	//Constantes y m�todos relacionados con delta time
	Uint64 currTicks_ = SDL_GetPerformanceCounter();
	Uint64 lastTicks_ = 0;
	double deltaTime_;
	void updateDelta();

	//Area en la que se encuentra el jugador (1 - 3 -> primera isla, 4 - 6 -> segunda isla)
	int currArea_ = 1;

public:
	Application(GameStateMachine* state=nullptr);
	virtual ~Application(); 
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
	double getDeltaTime() { return deltaTime_; }
	int getCurrArea() { return currArea_; }; //Mover a GameManager cuando tengamos
	TextureManager* getTextureManager() { return textureManager_; };
	//Generators
	Equipment* genEquip() { return equipGen_->genEquip(); };
	Equipment* genEquip(equipType type) { return equipGen_->genEquip(type); };
};
