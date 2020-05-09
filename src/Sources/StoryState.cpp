#include "StoryState.h"
#include "ShipState.h"
#include "tutorialState.h"

void StoryState::goToGame(Application* app) {
	app->getGameStateMachine()->changeState(new tutorialState(app));
}

void StoryState::draw() const {

	//Dibujamos en toda la pantalla, tomando como origen el (0,0)
	scenes.top().sceneTexture->render({ 0,0,app_->getWindowWidth(), app_->getWindowHeight() });

	GameState::draw(); //Despu�s, dibujamos encima los botones
}

void StoryState::update() {

	bool stateChanged = false; //Booleano para comprobar si ya se ha cambiado de estado

	//Comprobamos si la duraci�n de la escena ya se ha completado
	if (SDL_GetTicks() - timeSinceUpdate > scenes.top().duration) {
		timeSinceUpdate = SDL_GetTicks();
		//Pasamos a la siguiente
		scenes.pop();
		//Si ya no hay m�s escenas, pasamos al juego
		if (scenes.empty()) {
			goToGame(app_); //Go to PlayState
			stateChanged = true;
		}
	}

	//Si ya se ha acabado la secuencia de escenas, no se procesa el estado de los objetos del juego
	//(pq estar�a en PlayState ya)
	if(!stateChanged)GameState::update();
	
}

void StoryState::initState() {
	//De momento estoy metiendo los fondos de esta forma, pero si a alguien se le ocurre
	//como hacerlo de una forma mejor se aceptan sugerencias

	//Como es una pila, las escenas se meten en el orden inverso al que aparecen en pantalla
	scenes.push({ 2000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene3) });
	scenes.push({ 3000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene2) });
	scenes.push({ 2000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene1) });

	//Bot�n para saltarse la secuencia de escenas
	createButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkipButton), { 10,10 }, { 50,50 }, goToGame);
}

