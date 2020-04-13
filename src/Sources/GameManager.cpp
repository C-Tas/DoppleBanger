#include "GameManager.h"
unique_ptr<GameManager> GameManager::instance_;

void GameManager::initGameManager(int currGold, Island unlockedIslands, int achievementPoints) {
	currGold_ = currGold;
	unlockedIslands_ = unlockedIslands;
	achievementPoints_ = achievementPoints;
}

const bool GameManager::isSkillAsign(SkillName skill) {
	int i = 0;
	while (i < skillsEquipped_.size() && skillsEquipped_[i] != skill)i++;
	return !i == skillsEquipped_.size();
}

const Key GameManager::getEquippedSkillKey(SkillName skill) {
	int i = 0;
	while (i < skillsEquipped_.size() && skillsEquipped_[i] != skill)i++;
	return (Key)i;
}

void GameManager::setSkillCooldown(bool cooldown, Key key)
{
	skillsCooldown[(int)key] = cooldown;
	hud_->setSkillCooldown(cooldown, (int)key);
}

void GameManager::setSkillEquiped(SkillName newSkill, Key key)
{
	skillsEquipped_[(int)key] = newSkill;
	hud_->updateKey((int)key);
}

void GameManager::setObjectEquipped(ObjectName newObject, Key key)
{
	objectsEquipped[(int)key - (int)Key::One] = newObject;
	hud_->updateKey((int)key);
}