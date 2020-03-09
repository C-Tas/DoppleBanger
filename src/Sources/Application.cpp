#include "Application.h"
#include "MainMenuState.h"
#include <exception>

Application::Application(GameStateMachine* state) {
	
	initSDL();
	machine_ = new GameStateMachine();
	GameState* startState = new MainMenuState(this);
	machine_->pushState(startState);
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
	HandleEvents* input = HandleEvents::instance();
	while (!appClosed_) {
		SDL_RenderClear(renderer_);

		//update state 
		if(machine_ != nullptr) machine_->getState()->update();
		//render state
		if(machine_ != nullptr) machine_->getState()->draw();
		SDL_RenderPresent(renderer_);
		input->update();
	}
	endGame();
}