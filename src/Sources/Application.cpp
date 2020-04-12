#include "Application.h"
#include "MainMenuState.h"
#include "HandleEvents.h"
#include <exception>
#include "GameManager.h"
#include "ShopState.h"

Application::Application(GameStateMachine* state) {
	initSDL();
	initResources();
	machine_ = new GameStateMachine();
	GameState* startState = new MainMenuState(this);
	machine_->pushState(startState);
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
	//Crear e inicializar textureManager
	textureManager_ = new TextureManager();
	textureManager_->initObject();

	//Crear e inicializar fontManager
	fontManager_ = new FontManager();
	fontManager_->initObject();

	//Crear e inicializar audioManager
	audioManager_ = new AudioManager();
	audioManager_->initObject();

	//Generador de randoms
	random_ = new SRandBasedGenerator();

	///<summary>Generador de equipo aleatorio</summary>
	equipGen_ = new RandEquipGen(this);

	//Creacion de las texturas
	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
		cout << "Creada textura de: " << image.textureId << endl;
	}

	//Creación de las fuentes
	for (auto& font : Resources::fontsRoutes) {
		fontManager_->loadFont(font.id, font.fileName, font.size);
		cout << "Creada fuente: " << font.id << endl;
	}

	//Creación de mensajes
	for (auto& txtmsg : Resources::messages) {
		textureManager_->loadFromText(txtmsg.id, renderer_, txtmsg.msg,
			fontManager_->getFont(txtmsg.fontId), txtmsg.color);
	}

	//Creación de los efectos de sonido
	for (auto& sound : Resources::soundRoutes) {
		audioManager_->loadSound(sound.audioId, sound.filename);
	}

	//Creación de la música
	for (auto& music : Resources::musicRoutes) {
		audioManager_->loadMusic(music.id, music.fileName);
	}
}

//Elimina los recursos
void Application::closeResources() {
	delete equipGen_;
	delete random_;
	delete audioManager_;
	delete fontManager_;
	delete textureManager_;
}