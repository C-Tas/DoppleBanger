#include "GameManager.h"
unique_ptr<GameManager> GameManager::instance_;

void GameManager::initGameManager(int currGold, Island currIsland, int achievementPoints) {
	currGold_ = currGold;
	currIsland_ = currIsland;
	achievementPoints_ = achievementPoints;
}
