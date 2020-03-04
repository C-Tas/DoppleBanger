#pragma once
#include "SDL.h"
#include "GameStateMachine.h"
using namespace std;
//class GameStateMachine;
//Clase que llamará al estado actual desde la máquina de estados
class Application
{
private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	GameStateMachine* machine_ = nullptr;
	bool appClosed_ = false;

	//Constantes pantalla
	static const int winWidth_ = 1600;
	static const int winHeight_ = 900;

	//Métodos auxiliares para la constructora
	void initSDL();

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
};

