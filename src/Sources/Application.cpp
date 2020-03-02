#include "Application.h"
#include <exception>

Application::Application() {
	
	initSDL();

	//A�adir estado mainMenu a la maquina de estados

}

Application::~Application() {
	//Faltar�a vaciar m�quina de estados
	

	//Destruimos render y window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = nullptr;
	window = nullptr;

	//Cerramos SDL
	SDL_Quit();
}

void Application::initSDL() {
	int winX, winY; // Posici�n de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// Inicializaci�n del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Dopplebanger", winX, winY, winWidth,
		winHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		throw exception("Game window or renderer was null");
	}
}

void Application::runApp() {
	while (!appClosed) {

		//update state 
		//render state

		//just for testing
		SDL_SetRenderDrawColor(renderer, 180, 50, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
		endGame();
	}
}