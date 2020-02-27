#include "GameState.h"

GameState::~GameState() {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		delete (*it);
	}
	gameObjects_.clear();
}

void GameState::update() {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		(*it)->update();
	}
}

void GameState::draw() const {
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		(*it)->draw();
	}
}