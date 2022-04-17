#include "Application.h"
#include "MainMenuState.h"
#include "CaribbeanIslandState.h"
#include "HandleEvents.h"
#include <exception>
#include "GameManager.h"

// USABILIDAD
#include "Tracker.h"
#define PATH_TRACKER "../Events/"

Application::Application(GameStateMachine* state) {
	initSDL();
	initResources();
	gameManager_ = GameManager::instance();
	gameManager_->setApp(this);
	machine_ = new GameStateMachine();
	GameState* startState = new MainMenuState(this);
	machine_->pushState(startState);

	// USABILIDAD
	tracker_ = Tracker::GetInstance();
}

Application::~Application() {
	// USABILIDAD
	long long timest = Tracker::GetTimeStamp();
	auto sesion = gameManager_->getIdSesion();
	Logout* logout = (Logout*)(Tracker::CreateNewEvent(timest, gameManager_->getIdUser(), sesion, (int)EventInfo::EventType::Logout));
	Tracker::TrackEvent(logout);
	tracker_->End();
	tracker_->Free();

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

//USABILIDAD
bool Application::initTracker()
{
	if (trackerStarted_) {
		std::cout << "El tracker ya se habia inicializado...\n";
		return false;
	}

	if (gameManager_ == nullptr) {
		std::cout << "Error al inicializar el tracker. Gamemanager sin inicializar...\n";
		return false;
	}

	createIdUser();
	std::string mac = gameManager_->getIdUser();
	createIdSesion();
	std::string sesion = gameManager_->getIdSesion();

	if (!tracker_->Init(PersistenceType::FILE, TypeOfFile::Json, PATH_TRACKER))
		return false;
	
	long long timest = Tracker::GetTimeStamp();
	Login* login = (Login*)(Tracker::CreateNewEvent(timest, mac, sesion, (int)EventInfo::EventType::Login));
	Tracker::TrackEvent(login);

	return true;
}

void Application::runApp() {
	HandleEvents* input = HandleEvents::instance();
	while (!appClosed_) {
		//Resetea el negro
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderClear(renderer_); //Clear
		updateDelta(); //Actualizamos deltaTime

		if (machine_ != nullptr) machine_->getState()->handleEvents();
		if (machine_ != nullptr) machine_->getState()->update();
		if (machine_ != nullptr) machine_->getState()->draw();

		SDL_RenderPresent(renderer_); //Draw

	#ifdef _DEBUG
		if (input->isKeyDown(SDL_SCANCODE_P))
			appClosed_ = true;
	#endif
	}
	endGame();
}

void Application::resetMusicChannels()
{
	for (int i = 0; i < Resources::NumMusicChannels; i++) {
		audioManager_->haltChannel(i);
	}
}

void Application::resetSoundsChannels()
{
	for (int i = Resources::NumMusicChannels; i < Resources::NumSoundChannels; i++) {
		audioManager_->haltChannel(i);
	}
}

void Application::updateDelta()
{
	lastTicks_ = currTicks_;
	currTicks_ = SDL_GetPerformanceCounter();
	deltaTime_ = (double)((currTicks_ - lastTicks_) / (double)SDL_GetPerformanceFrequency());
}

void Application::createIdUser()
{
	// Comando de la consola de windows
	std::string cmd = "getmac";
	std::string auxFile = "macaddress.txt";

	system((cmd + ">" + auxFile).c_str());

	std::string line;
	// Fichero auxiliar temporal
	std::ifstream myfile("macaddress.txt");
	// Direccion mac final
	std::string mac;
	int i = 0;
	if (myfile.is_open()) {

		while (i < 4 && std::getline(myfile, line)) {
			i++;
		}
		mac = line.substr(0, 17);
		myfile.close();
	}
	else
		std::cout << "Unable to open the file";

	system(("del " + auxFile).c_str());

	gameManager_->setIdUser(mac);
}

void Application::createIdSesion()
{
	/* initialize random seed: */
	srand(time(NULL));
	int length = rand() % 16 + 10;
	std::string idSesion = "";
	for (int i = 0; i < length; i++) {
		int choice = (char)rand() % 3 + 0;
		switch (choice)
		{
		case 1:
			idSesion += rand() % ('9' - '0' + 1) + '0';;
			break;
		case 2:
			idSesion += rand() % ('Z' - 'A' + 1) + 'A';
			break;
		case 3:
		default:
			idSesion += rand() % ('z' - 'a' + 1) + 'a';
			break;
		}
	}

	gameManager_->setIdSesion(idSesion);
}

void Application::initResources() {
	//Crear e inicializar textureManager
	textureManager_ = new TextureManager();
	textureManager_->initObject();

	//Crear e inicializar fontManager
	fontManager_ = new FontManager();
	fontManager_->initObject();

	//Crear e inicializar audioManager
	audioManager_ = new AudioManager(Resources::NumSoundChannels);
	audioManager_->initObject();

	//Generador de randoms
	random_ = new SRandBasedGenerator();

	///<summary>Generador de equipo aleatorio</summary>
	equipGen_ = new RandEquipGen(this);

	//Creacion de las texturas
	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
	}

	//Creación de las fuentes
	for (auto& font : Resources::fontsRoutes) {
		fontManager_->loadFont(font.id, font.fileName, font.size);
	}

	//Creación de mensajes
	for (auto& txtmsg : Resources::messages) {
		textureManager_->loadFromText(txtmsg.id, renderer_, txtmsg.msg,
			fontManager_->getFont(txtmsg.fontId), txtmsg.color);
	}

	//Creación del sonido
	for (auto& sound : Resources::audioRoutes) {
		audioManager_->loadSound(sound.audioId, sound.filename);
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