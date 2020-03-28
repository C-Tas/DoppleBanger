#include "GameManager.h"
unique_ptr<GameManager> GameManager::instance_;

void GameManager::initGameManager(int currGold, int unlockedIslands, int achievementPoints) {
	currGold_ = currGold;
	unlockedIslands_ = unlockedIslands;
	achievementPoints_ = achievementPoints;
}
