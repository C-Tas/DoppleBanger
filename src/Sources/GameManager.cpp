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

const SkillKey GameManager::getEquippedSkillKey(SkillName skill) {
	int i = 0;
	while (i < skillsEquipped_.size() && skillsEquipped_[i] != skill)i++;
	return (SkillKey)i;
}

void GameManager::setSkillCooldown(bool cooldown, SkillKey key)
{
	skillsCooldown[(int)key] = cooldown;
	hud_->setSkillCooldown(cooldown, (int)key);
}

void GameManager::setSkillEquiped(SkillName newSkill, SkillKey key)
{
	skillsEquipped_[(int)key] = newSkill;
	hud_->updateSkillKey((int)key);
}

void GameManager::setObjectEquipped(ObjectName newObject, ObjectKey key)
{
	objectsEquipped[(int)key] = newObject;
	hud_->updateObjectKey((int)key);
}
