#include "GameManager.h"
#include "Application.h"
#include "Player.h"

unique_ptr<GameManager> GameManager::instance_;

void GameManager::initGameManager(int currGold, Island unlockedIslands, int achievementPoints) {
	currGold_ = currGold;
	unlockedIslands_ = unlockedIslands;
	achievementPoints_ = achievementPoints;
	app_ = new Application();
}

const int GameManager::getFontSize()
{
	int fontSize;
	int width = app_->getWindowWidth();

	if (width >= 1920) fontSize = 25;
	else if (width >= 1600) fontSize = 20;
	else if (width >= 1280) fontSize = 16;
	else fontSize = 10;

	return fontSize;
}

const bool GameManager::isSkillAsign(SkillName skill) {
	int i = 0;
	while (i < skillsEquipped_.size() && skillsEquipped_[i] != skill)i++;
	return !(i == skillsEquipped_.size());
}

const Key GameManager::getEquippedSkillKey(SkillName skill) {
	int i = 0;
	while (i < skillsEquipped_.size() && skillsEquipped_[i] != skill)i++;
	return (Key)i;
}

const Point2D GameManager::getPlayerPos()
{
	return player_->getPos();
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

void GameManager::addToInventory(Equipment* ob) {
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_, ob->getItemTexture(), Vector2D{ 300,400 }, Vector2D{ 75,75 }, ob, nullptr);
	//A�adimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = inventory_->insert(inventory_->end(), b);
	b->setIterator(it);
}