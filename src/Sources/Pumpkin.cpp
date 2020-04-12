#include "Pumpkin.h"
#include "GameManager.h"
bool Pumpkin::update() {
	return false;
}
bool Pumpkin::attack() {
	if (isATargetInRange()) return true;
	else return false;
}
bool Pumpkin::isATargetInRange() {
	GameManager* gm = GameManager::instance();
	return true;
}