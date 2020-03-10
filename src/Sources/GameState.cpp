#include "GameState.h"
GameState::~GameState() {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		delete (*it);
	}
	gameObjects_.clear();
	objectsToRender_.clear();
	//objectEvent_.clear();
}

void GameState::update() {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		(*it)->update();
	}
}

void GameState::draw() const {
	for (auto it = objectsToRender_.begin(); it != objectsToRender_.end(); ++it) {
		(*it)->draw();
	}
}
void GameState::handleEvents(SDL_Event& event) {
	//for (HandleEventClass* hE: objectEvents_) {
	//	hE->HandleEvent(event);
	//}
}
void GameState::createButton(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, Application* app) {
	Button* button = new Button(texture, pos, scale, callBack,app);}

void GameState::addUpdateList(GameObject* obj) {
	gameObjects_.push_back(obj);
}

void GameState::addRenderList(Draw* obj) {
	objectsToRender_.push_back(obj);
}