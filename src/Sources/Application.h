#pragma once
#include "SDL.h"
#include "GameStateMachine.h"
using namespace std;
//class GameStateMachine;
//Clase que llamará al estado actual desde la máquina de estados
class Application
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* machine_ = nullptr;
	bool appClosed = false;

	//Constantes pantalla
	const int winWidth = 1600;
	const int winHeight = 900;

	//Métodos auxiliares para la constructora
	void initSDL();

public:
	Application(GameStateMachine* state=nullptr);
	~Application(); 
	void runApp();
	
	//Setters
	void endGame() { appClosed = true; };
	
	//Getters
	GameStateMachine* getStateMachine() { return machine_; };
	bool isRunning() { return !appClosed; };
	int getWindowWidth() { return winWidth; };
	int getWindowHeight() { return winHeight; };
};

