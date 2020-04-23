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
"precision": 0,
"melee": 0,
"clon": 0,
"skillTree":[0, 0, 0],
"objects": [null, null],
"missionStarted": [],
"missionCompleted":	[],
"stash":[],
"inventory":[]
}
*/
void GameManager::saveSlot1()
{
	ifstream input("../Sources/save_data/save1.json");
	if (input.fail()) cout << "No hay partida guardada" << endl;
	input.close();
	ofstream slot_("../Sources/save_data/save1.json");
	save(slot_);
}

void GameManager::saveSlot2()
{
	ifstream input("../Sources/save_data/save2.json");
	if (input.fail()) cout << "No hay partida guardada" << endl;
	input.close();
	
	ofstream slot_("../Sources/save_data/save2.json");
	save(slot_);
}

void GameManager::saveSlot3()
{
	ifstream input("../Sources/save_data/save3.json");
	if (input.fail()) cout << "No hay partida guardada" << endl;
	input.close();
	ofstream slot_("../Sources/save_data/save3.json");
	save(slot_);
}

void GameManager::save(ofstream& slot)
{
	jValue mainJson(jType::JOBJECT);
	jValue aux(jType::JNUMBER);
	//Isla actual
	aux.set_string(to_string((int)currIsland_));
	mainJson.add_property("currIsland", aux);
	//Última isla desbloqueada
	aux.set_string(to_string((int)currIsland_));
	mainJson.add_property("unlockedIsland", aux);
	//Oro del inventario
	aux.set_string(to_string(inventoryGold));
	mainJson.add_property("currGold", aux);
	//Oro del alijo
	aux.set_string(to_string(stashGold));
	mainJson.add_property("stashGold", aux);
	//Puntos de hazaña actuales
	aux.set_string(to_string(achievementPoints_));
	mainJson.add_property("skillPoints", aux);
	//Puntos de hazaña invertidos
	aux.set_string(to_string(precisionPoints_));	//Rama combate
	mainJson.add_property("precision", aux);
	aux.set_string(to_string(meleePoints_));	//Rama precisión
	mainJson.add_property("melee", aux);
	aux.set_string(to_string(clonPoints_));	//Rama clon
	mainJson.add_property("clon", aux);
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
	mainJson.add_property("skills", skillEquippedValue);

	//Objetos equipados
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
	mainJson.add_property("objects", objectsValue);

	//Equipamiento del player
	jValue equipValue(jType::JARRAY);
	playerEquipment auxEquip = player_->getInfoEquip();
	vector<Equipment*> vEquip{
		auxEquip.armor_,
		auxEquip.boots_,
		auxEquip.gloves_,
		auxEquip.sword_,
		auxEquip.gun_
	};
	vector<jValue> objects{
		(jType::JOBJECT),
		(jType::JOBJECT),
		(jType::JOBJECT),
		(jType::JOBJECT),
		(jType::JOBJECT)
	};
	//const enum equipType { Armor_, Boots_, Gloves_, Sword_, Saber_, Pistol_, Shotgun_ };
	for (int i = 0; i < vEquip.size(); i++) {
		if (vEquip[i] == nullptr) {
			aux.set_type(jType::JSTRING);
			aux.set_string("null");
		}
		else {
			switch (vEquip[i]->getEquipTye())
			{
			case equipType::Armor_:
				aux.set_type(jType::JSTRING);
				aux.set_string("Armor");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getArmor()));
				objects[i].add_property("armor", aux);
				aux.set_string(to_string(vEquip[i]->getHealth()));
				objects[i].add_property("health", aux);
				//Armor y health
				break;
			case equipType::Boots_:
				aux.set_type(jType::JSTRING);
				aux.set_string("Boots");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getArmor()));
				objects[i].add_property("armor", aux);
				aux.set_string(to_string(vEquip[i]->getSpeed()));
				objects[i].add_property("speed", aux);
				//speed y armor
				break;
			case equipType::Gloves_:
				aux.set_type(jType::JSTRING);
				aux.set_string("Gloves");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getArmor()));
				objects[i].add_property("armor", aux);
				aux.set_string(to_string(vEquip[i]->getCrit()));
				objects[i].add_property("critic", aux);
				//Crítico y armor
				break;
			case equipType::Sword_:
				aux.set_type(jType::JSTRING);
				aux.set_string("Sword");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getMeleeRate()));
				objects[i].add_property("rate", aux);
				aux.set_string(to_string(vEquip[i]->getMeleeDmg()));
				objects[i].add_property("damage", aux);
				//MeleeRate y ad
				break;
			case equipType::Saber_:
				aux.set_type(jType::JSTRING);
				aux.set_string("Saber");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getMeleeRate()));
				objects[i].add_property("rate", aux);
				aux.set_string(to_string(vEquip[i]->getMeleeDmg()));
				objects[i].add_property("damage", aux);
				//MeleeRate y ad
				break;
			case equipType::Pistol_:
				aux.set_type(jType::JSTRING);
				aux.set_string("Pistol");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getDistRate()));
				objects[i].add_property("rate", aux);
				aux.set_string(to_string(vEquip[i]->getDistDmg()));
				objects[i].add_property("damage", aux);
				//DistRate y disDmg
				break;
			case equipType::Shotgun_:
				aux.set_type(jType::JSTRING);
				aux.set_string("ShotGun");
				objects[i].add_property("name", aux);
				aux.set_type(jType::JNUMBER);
				aux.set_string(to_string(vEquip[i]->getDistRate()));
				objects[i].add_property("rate", aux);
				aux.set_string(to_string(vEquip[i]->getDistDmg()));
				objects[i].add_property("damage", aux);
				//DistRate y distDmg
				break;
			}
		}
		equipValue.add_element(objects[i]);
	}
	mainJson.add_property("equipment", equipValue);
	//Misiones empezadas
	//vector<bool> questStarted = missionsStarted;
	////Misiones completadas
	//vector<bool> questFinished = missionsComplete;

	////Inventario
	//for (InventoryButton* ob : *inventory_) {

	//}

	//for (InventoryButton* ob : *stash_) {

	//}
	slot << mainJson.to_string();
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