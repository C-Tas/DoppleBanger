#include "GameManager.h"
#include "Application.h"
#include "Player.h"
#include "jute.h"
#include "InventoryButton.h"

using namespace jute;
unique_ptr<GameManager> GameManager::instance_;

void GameManager::initGameManager(int currGold, Island unlockedIslands, int achievementPoints) {
	currGold_ = currGold;
	unlockedIslands_ = unlockedIslands;
	achievementPoints_ = achievementPoints;
	app_ = new Application();
}
/*
{
"currIsland": 0,
"unlockedIsland": 1,
"skillPoints": 0,
"currGold": 0,
"stashGold": 0,
"skillTree":[0, 0, 0],
"skills": [null, null, null],
"objects": [null, null],
"missionStarted": [],
"missionCompleted":	[],
"stash":[],
"inventory":[]
}
*/
void GameManager::saveSlot1()
{
	ofstream slot_("../Sources/save_data/save1.json");
	save(slot_);
}

void GameManager::saveSlot2()
{
	ofstream slot_("../Sources/save_data/save2.json");
	save(slot_);
}

void GameManager::saveSlot3()
{
	ofstream slot_("../Sources/save_data/save3.json");
	save(slot_);
}

void GameManager::save(ofstream& slot)
{
	jValue aux(jType::JNUMBER);
	//Apertura del cuerpo
	slot << "{" << endl;
	//Isla actual
	aux.set_string(to_string((int)currIsland_));
	slot << "\"currIsland\":" << " " << aux.as_int() << "," << endl;
	//Última isla desbloqueada
	aux.set_string(to_string((int)currIsland_));
	slot << "\"unlockedIsland\":" << " " << aux.as_int() << "," << endl;
	//Puntos de hazaña actuales
	aux.set_string(to_string(achievementPoints_));
	slot << "\"skillPoints\":" << " " << aux.as_int() << "," << endl;
	//Oro del inventario
	aux.set_string(to_string(inventoryGold));
	slot << "\"currGold\":" << " " << aux.as_int() << "," << endl;
	//Oro del alijo
	aux.set_string(to_string(stashGold));
	slot << "\"stashGold\":" << " " << aux.as_int() << "," << endl;
	//Cambio del tipo del jValue
	jValue skillTreeValue(jType::JARRAY);
		//Puntos de hazaña invertidos
		//aux.set_string("0");	//Rama combate
		//mainJValue.add_element(aux);
		//aux.set_string("0");	//Rama precisión
		//mainJValue.add_element(aux);
		//aux.set_string("0");	//Rama clon
		//mainJValue.add_element(aux);
	//Habilidades equipadas
	jValue skillEquippedValue(jType::JARRAY);
	aux.set_type(jType::JSTRING);
	for (int i = 0; i < skillsEquipped_.size() - 1; i++) {
		switch (skillsEquipped_[i])
		{
		case SkillName::Unequipped:
			aux.set_string("null");
			break;
		case SkillName::GolpeFuerte:
			aux.set_string("GolpeFuerte");
			break;
		case SkillName::Torbellino:
			aux.set_string("Torbellino");
			break;
		case SkillName::DisparoPerforante:
			aux.set_string("Perforante");
			break;
		case SkillName::Rebote:
			aux.set_string("Rebote");
			break;
		case SkillName::Explosion:
			aux.set_string("Explosion");
			break;
		}
		skillEquippedValue.add_element(aux);
	}
	slot << "\"skills\":" << " " << skillEquippedValue.to_string() << "," << endl;

	jValue objectsValue(jType::JARRAY);
	for (int i = 0; i < objectsEquipped.size(); i++) {
		switch (objectsEquipped[i])
		{
		case ObjectName::Unequipped:
			aux.set_string("null");
			break;
		case ObjectName::Health:
			aux.set_string("Health");
			break;
		case ObjectName::Mana:
			aux.set_string("Mana");
			break;
		case ObjectName::Speed:
			aux.set_string("Speed");
			break;
		case ObjectName::Armor:
			aux.set_string("Armor");
			break;
		case ObjectName::Dmg:
			aux.set_string("Dmg");
			break;
		case ObjectName::Crit:
			aux.set_string("Crit");
			break;
		}
		objectsValue.add_element(aux);
	}
	slot << "\"objects\":" << " " << objectsValue.to_string() << "," << endl;

	//Misiones empezadas
	//vector<bool> questStarted = missionsStarted;
	////Misiones completadas
	//vector<bool> questFinished = missionsComplete;

	////Inventario
	//for (InventoryButton* ob : *inventory_) {

	//}

	//for (InventoryButton* ob : *stash_) {

	//}
	slot << "}";
	slot.close();
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