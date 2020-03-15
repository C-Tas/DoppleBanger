#include "Application.h"
#include "MainMenuState.h"
#include "SelectLevelState.h"
#include"VolcanicIslandState.h"
#include "HandleEvents.h"
#include <exception>

Application::Application(GameStateMachine* state) {
	
	initSDL();
	initResources();
	machine_ = new GameStateMachine(); //Creación máquina de estados
	GameState* startState = /*new MainMenuState(this)*/new VolcanicIslandState(this);
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
	int winX, winY; // PosiciOn de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// InicializaciOn del sistema, ventana y renderer
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
		SDL_RenderClear(renderer_); //Clear
		updateDelta(); //Actualizamos deltaTime

		if (machine_ != nullptr) machine_->getState()->handleEvents();
		if (machine_ != nullptr) machine_->getState()->update();
		if (machine_ != nullptr) machine_->getState()->draw();

		SDL_RenderPresent(renderer_); //Draw

		if (input->isKeyDown(SDLK_ESCAPE))appClosed_ = true;
	
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
	//Inicializar generacion aleatoria de objetos
	equipGen_ = new RandEquipGen(this);
	//Crear e inicializar textureManager
	textureManager_ = new TextureManager();
	textureManager_->init();

	//Creacion de las texturas
	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
		cout << "Creada textura de: " << image.textureId << endl;
	}
}


void Application::closeResources() {
	//Faltaría el borrar los recursos que añadiesemos a posteriori
	delete textureManager_;
    delete equipGen_;
}