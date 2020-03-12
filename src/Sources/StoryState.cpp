#include "StoryState.h"
#include "PlayState.h"
void StoryState::goToGame(Application* app) {
	app->getStateMachine()->changeState(new PlayState(app));
}

void StoryState::draw() const {

	GameState::draw();

	//Dibujamos en toda la pantalla, tomando como origen el (0,0)
	scenes[currentScene].sceneTexture->render({ 0,0,app_->getWindowWidth(), app_->getWindowHeight() });
}

void StoryState::update() {

	bool stateChanged = false; //Booleano para comprobar si ya se ha cambiado de estado

	//Comprobamos si la duración de la escena ya se ha completado
	if (SDL_GetTicks() - timeSinceUpdate > scenes[currentScene].duration) {
		timeSinceUpdate = SDL_GetTicks();
		//Pasamos a la siguiente
		currentScene++;
		//Si ya no hay más escenas, pasamos al juego
		if (currentScene >= scenes.size()) {
			goToGame(app_); //Go to PlayState
			stateChanged = true;
		}
	}

	//Si ya se ha acabado la secuencia de escenas, no se procesa el estado de los objetos del juego
	//(pq estaría en PlayState ya)
	if(!stateChanged)GameState::update();
	
}

void StoryState::initState() {
	//De momento estoy metiendo los fondos de esta forma, pero si a alguien se le ocurre
	//como hacerlo de una forma mejor se aceptan sugerencias
	scenes[0] = { 2000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene1) };
	scenes[1] = { 3000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene2) };
	scenes[2] = { 2000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene3) };

	//Botón para saltarse la secuencia de escenas
	createButton(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 10,10 }, { 50,50 }, goToGame, app_);
}

