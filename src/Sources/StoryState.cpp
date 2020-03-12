#include "StoryState.h"
#include "PlayState.h"
void StoryState::goToGame() {
	app_->getStateMachine()->changeState(new PlayState(app_));
}

void StoryState::draw() const {
	//Dibujamos en toda la pantalla, tomando como origen el (0,0)
	scenes[currentScene].sceneTexture->render({ 0,0,app_->getWindowWidth(), app_->getWindowHeight() });
}

void StoryState::update() {
	//Comprobamos si la duración de la escena ya se ha completado
	if (SDL_GetTicks() - timeSinceUpdate > scenes[currentScene].duration) {
		timeSinceUpdate = SDL_GetTicks();
		//Pasamos a la siguiente
		currentScene++;
		//Si ya no hay más escenas, pasamos al juego
		if (currentScene >= scenes.size()) goToGame();
	}
}

void StoryState::initState() {
	//De momento estoy metiendo los fondos de esta forma, pero si a alguien se le ocurre
	//como hacerlo de una forma mejor se aceptan sugerencias
	scenes[0] = { 2000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene1) };
	scenes[1] = { 3000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene2) };
	scenes[2] = { 2000, app_->getTextureManager()->getTexture(Resources::TextureId::Scene3) };
}

