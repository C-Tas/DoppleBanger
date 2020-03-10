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
		if((*it)->update())return;
	}
}

void GameState::draw() const {
	for (auto it = objectsToRender_.begin(); it != objectsToRender_.end(); ++it) {
		(*it)->draw();
	}
}
void GameState::handleEvents() {
	eventHandler_->update();
}
void GameState::createButton(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, Application* app) {
	Button* button = new Button(app,texture, pos, scale, callBack);}

void GameState::addUpdateList(GameObject* obj) {
	gameObjects_.push_back(obj);
}

void GameState::addRenderList(Draw* obj) {
	objectsToRender_.push_back(obj);
}

void GameState::addRenderUpdateLists(Draw* obj) {
	addUpdateList(obj);
	addRenderList(obj);
}