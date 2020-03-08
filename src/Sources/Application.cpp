#include "Application.h"
#include "MainMenuState.h"
#include "SelectLevelState.h"
#include "HandleEvents.h"
#include <exception>

Application::Application(GameStateMachine* state) {
	
	initSDL();
	initResources();
	machine_ = new GameStateMachine();
	GameState* startState = new MainMenuState(this);
	machine_->pushState(/*startState*/ new SelectLevelState(this, 3));
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
		SDL_RenderClear(renderer_);

		//actualize input handler
		HandleEvents* ih = HandleEvents::instance();
		ih->update();

		//update state 
		if(machine_ != nullptr) machine_->getState()->update();
		//render state
		if(machine_ != nullptr) machine_->getState()->draw();

		SDL_RenderPresent(renderer_);
	}
	endGame();
}

void Application::initResources() {
	//De momento solo voy a introducir las imagenes
	textureManager_ = new TextureManager();
	textureManager_->init();

	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
		cout << "Creada textura de: " << image.textureId << endl;
	}
}

//De momento en este método solo se llama al delete de textureManager puesto que todavía no están creados ni inicializados
//el resto de objetos con recursos del juego
void Application::closeResources() {
	delete textureManager_;
}