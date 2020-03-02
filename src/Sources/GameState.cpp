#include "GameState.h"
GameState::~GameState() {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		delete (*it);
	}
	gameObjects_.clear();
	objectToRender_.clear();
	//objectEvent_.clear();
}

void GameState::update() {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		(*it)->update();
	}
}

void GameState::draw() const {
	for (auto it = objectToRender_.begin(); it != objectToRender_.end(); ++it) {
		(*it)->draw();
	}
}
void GameState::handleEvents(SDL_Event& event) {
	//for (HandleEventClass* hE: objectEvents_) {
	//	hE->HandleEvent(event);
	//}
}