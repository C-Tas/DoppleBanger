#include "Application.h"
#include "GameState.h"
#include <exception>

Application::Application(GameStateMachine* state) {
	
	initSDL();
	machine_ = new GameStateMachine();
	//Añadir estado mainMenu a la maquina de estados
}

Application::~Application() {
	
	delete machine_;

	//Destruimos render y window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	//Cerramos SDL
	SDL_Quit();
}

void Application::initSDL() {
	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Dopplebanger", winX, winY, winWidth_,
		winHeight_, SDL_WINDOW_SHOWN);

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) {
		throw exception("Game window or renderer was null");
	}
}

void Application::runApp() {
	while (!appClosed_) {

		//update state 
		//if(machine_ != nullptr)//machine_->getState()->update();
		//render state
		//if(machine_ != nullptr)//machine_->getState()->draw();

		//just for testing
		SDL_SetRenderDrawColor(renderer_, 180, 50, 0, 255);
		SDL_RenderClear(renderer_);
		SDL_RenderPresent(renderer_);
		SDL_Delay(5000);
		endGame();
	}
}