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
	machine_->pushState(startState /*new SelectLevelState(this, 3)*/);
}

Application::~Application() {
	

	delete machine_;
	closeResources();

	//Destruimos render y window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	//Cerramos SDL
	SDL_Quit();
}

void Application::initSDL() {
	int winX, winY; // Posici�n de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// Inicializaci�n del sistema, ventana y renderer
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
		updateDelta();

		if (machine_ != nullptr) machine_->getState()->handleEvents();
		if (machine_ != nullptr) machine_->getState()->update();
		if (machine_ != nullptr) machine_->getState()->draw();

		SDL_RenderPresent(renderer_);
		HandleEvents* ih = HandleEvents::instance();
		if (ih->isKeyDown(SDLK_ESCAPE))appClosed_ = true;
	
	}
	endGame();
}

void Application::updateDelta()
{
	lastTicks_ = currTicks_;
	currTicks_ = SDL_GetPerformanceCounter();
	deltaTime_ = (double)((currTicks_ - lastTicks_) / (double)SDL_GetPerformanceFrequency());
}

void Application::initResources() {
	equipGen_ = new RandEquipGen(this);
	//De momento solo voy a introducir las imagenes
	textureManager_ = new TextureManager();
	textureManager_->init();

	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
		cout << "Creada textura de: " << image.textureId << endl;
	}
}

//De momento en este m�todo solo se llama al delete de textureManager puesto que todav�a no est�n creados ni inicializados
//el resto de objetos con recursos del juego
void Application::closeResources() {
	delete textureManager_;
    delete equipGen_;
}