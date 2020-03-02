#pragma once
#include "SDL.h"

using namespace std;
//Clase que llamará al estado actual desde la máquina de estados
class Application
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool appClosed = false;

	//Constantes pantalla
	const int winWidth = 1600;
	const int winHeight = 900;

	//Faltaría la máquina de estados

	//Métodos auxiliares para la constructora
	void initSDL();

public:
	Application();
	~Application(); 
	void runApp();
	
	//Setters
	void endGame() { appClosed = true; };
	
	//Getters
	bool isRunning() { return !appClosed; };
	int getWindowWidth() { return winWidth; };
	int getWindowHeight() { return winHeight; };
};

