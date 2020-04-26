#include "GameManager.h"
#include "Application.h"
#include "Player.h"
#include "InventoryButton.h"
#include "EmpoweredSkill.h"
#include "WhirlwindSkill.h"
#include "RicochetSkill.h"
#include "PerforateSkill.h"
#include "ClonSelfDestructSkill.h"

using namespace jute;
unique_ptr<GameManager> GameManager::instance_;

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

void GameManager::loadSlot1()
{
	load("../Sources/save_data/save1.json");
}

void GameManager::loadSlot2()
{
	load("../Sources/save_data/save2.json");
}

void GameManager::loadSlot3()
{
	load("../Sources/save_data/save3.json");
}

void GameManager::save(ofstream& slot)
{
	//Json principal donde se guardará toda la info
	jValue mainJson(jType::JOBJECT);
	//Variables numericas
	saveJNUMBER(slot, mainJson);
	//Misiones empezadas
	saveMissions(slot, mainJson);
	//Habilidades equipadas
	saveSkills(slot, mainJson);
	//Objetos equipados
	saveEquipment(slot, mainJson);
	//Inventario
	#pragma region Inventario
	//for (InventoryButton* ob : *inventory_) {

	//}
	#pragma endregion
	//Alijo
	#pragma region Alijo
	//for (InventoryButton* ob : *stash_) {

	//}
	#pragma endregion

	//Se guarda todo en el archivo
	slot << mainJson.to_string();
	slot.close();
}

void GameManager::saveJNUMBER(ofstream& slot, jute::jValue& mainJson)
{
	jValue aux(jType::JNUMBER);
	//Isla actual
	aux.set_string(to_string((int)currIsland_));
	mainJson.add_property("currIsland", aux);
	//Última isla desbloqueada
	aux.set_string(to_string((int)unlockedIslands_));
	mainJson.add_property("unlockedIsland", aux);
	//Oro del inventario
	aux.set_string(to_string(inventoryGold_));
	mainJson.add_property("currGold", aux);
	//Oro del alijo
	aux.set_string(to_string(stashGold));
	mainJson.add_property("stashGold", aux);
	//Puntos de hazaña actuales
	aux.set_string(to_string(achievementPoints_));
	mainJson.add_property("skillPoints", aux);
	//Puntos de hazaña invertidos
	aux.set_string(to_string(precisionPoints_));//Rama combate
	mainJson.add_property("precision", aux);
	aux.set_string(to_string(meleePoints_));	//Rama precisión
	mainJson.add_property("melee", aux);
	aux.set_string(to_string(clonPoints_));		//Rama clon
	mainJson.add_property("clon", aux);
}

void GameManager::saveMissions(ofstream& slot, jute::jValue& mainJson)
{
	jValue questStarted(jType::JARRAY);
	jValue aux(jType::JBOOLEAN);
	for (int i = 0; i < missionsStarted.size(); i++) {
		switch (missionsStarted[i])
		{
		case true:
			aux.set_string("true");
		case false:
			aux.set_string("false");
		}
		questStarted.add_element(aux);
	}
	mainJson.add_property("questStarted", questStarted);
	////Misiones completadas
	jValue questFinished(jType::JARRAY);
	for (int i = 0; i < missionsComplete.size(); i++) {
		switch (missionsComplete[i])
		{
		case true:
			aux.set_string("true");
		case false:
			aux.set_string("false");
		}
		questFinished.add_element(aux);
	}
	mainJson.add_property("questFinished", questFinished);
}

void GameManager::saveSkills(ofstream& slot, jute::jValue& mainJson)
{
	jValue skillEquippedValue(jType::JARRAY);
	jValue aux(jType::JSTRING);
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
}

void GameManager::saveEquipment(ofstream& slot, jute::jValue& mainJson)
{
	jValue equipValue(jType::JARRAY);
	jValue aux(jType::JSTRING);
	//Auxilizar del equipo del player
	playerEquipment auxEquip = player_->getInfoEquip();
	//Informacion de los objetos que se va a guardar
	jValue objectsValue(jType::JARRAY);
	for (int i = 0; i < auxEquip.potions_.size(); i++) {
		if (auxEquip.potions_[i] != nullptr) {
			switch (auxEquip.potions_[i]->getType())
			{
			case potionType::Health:
				aux.set_string("Health");
				break;
			case potionType::Mana:
				aux.set_string("Mana");
				break;
			case potionType::Speed:
				aux.set_string("Speed");
				break;
			case potionType::Armor:
				aux.set_string("Armor");
				break;
			case potionType::Damage:
				aux.set_string("Dmg");
				break;
			case potionType::Crit:
				aux.set_string("Crit");
				break;
			}
		}
		else {
			aux.set_string("null");
		}
		objectsValue.add_element(aux);
	}
	mainJson.add_property("objects", objectsValue);
	//Auxliar del equipamiento del player
	vector<Equipment*> vEquip{
		auxEquip.armor_,
		auxEquip.gloves_,
		auxEquip.boots_,
		auxEquip.sword_,
		auxEquip.gun_
	};	
	//Información del equipamiento que se va a guardar
	vector<jValue> equip{
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
			equip[i].add_property("name", aux);
		}
		else {
			//Nombre
			aux.set_type(jType::JNUMBER);
			aux.set_string(to_string((int)vEquip[i]->getEquipType()));
			equip[i].add_property("name", aux);
			//Precio
			aux.set_string(to_string((int)vEquip[i]->getPrice()));
			equip[i].add_property("price", aux);
			equipType auxType = vEquip[i]->getEquipType();
			if (auxType == equipType::ArmorI || auxType == equipType::ArmorII) {
				aux.set_string(to_string(vEquip[i]->getArmor()));
				equip[i].add_property("armor", aux);
				aux.set_string(to_string(vEquip[i]->getHealth()));
				equip[i].add_property("health", aux); 
			}
			else if (auxType == equipType::GlovesI || auxType == equipType::GlovesII) {
				aux.set_string(to_string(vEquip[i]->getArmor()));
				equip[i].add_property("armor", aux);
				aux.set_string(to_string(vEquip[i]->getCrit()));
				equip[i].add_property("critic", aux);
			}
			else if (auxType == equipType::BootsI || auxType == equipType::BootsII) {
				aux.set_string(to_string(vEquip[i]->getArmor()));
				equip[i].add_property("armor", aux);
				aux.set_string(to_string(vEquip[i]->getSpeed()));
				equip[i].add_property("speed", aux);
			}
			else if (auxType == equipType::SwordI || auxType == equipType::SwordII 
				|| auxType == equipType::SaberI || auxType == equipType::SaberII
				|| auxType == equipType::PistolI || auxType == equipType::PistolII
				|| auxType == equipType::ShotgunI || auxType == equipType::ShotgunII) {
				aux.set_string(to_string(vEquip[i]->getMeleeRate()));
				equip[i].add_property("rate", aux);
				aux.set_string(to_string(vEquip[i]->getMeleeDmg()));
				equip[i].add_property("damage", aux);
			}
		}
		equipValue.add_element(equip[i]);
	}
	mainJson.add_property("equipment", equipValue);
}

void GameManager::load(string jsonName)
{
	parser parser_;
	jValue mainJson = parser_.parse_file(jsonName);
	//Variables numericas
	loadJNUMBER(mainJson);
	//Misiones
	loadMissions(mainJson);
	//Equipamiento
	player_->load(mainJson);
	//HUD
	loadHUD(mainJson);
	
}

void GameManager::loadJNUMBER(jute::jValue& mainJson){
	currIsland_ = (Island)mainJson["currIsland"].as_int();
	unlockedIslands_ = (Island)mainJson["unlockedIsland"].as_int();
	inventoryGold_ = mainJson["currGold"].as_int();
	stashGold = mainJson["stashGold"].as_int();
	achievementPoints_ = mainJson["skillPoints"].as_int();
	precisionPoints_ = mainJson["precision"].as_int();
	meleePoints_ = mainJson["melee"].as_int();
	clonPoints_ = mainJson["clon"].as_int();
}

void GameManager::loadMissions(jute::jValue& mainJson){
	for (int i = 0; i < missionsStarted.size(); i++) {
		missionsStarted[i] = mainJson["questStarted"][i].as_bool();
	}
	for (int i = 0; i < missionsComplete.size(); i++) {
		missionsComplete[i] = mainJson["questFinished"][i].as_bool();
	}
}

void GameManager::loadSkills(jute::jValue& mainJson)
{
	for (int i = 0; i < skillsEquipped_.size() - 1; i++) {
		if (mainJson["skills"][i].as_string() == "null") {
			setSkillEquiped(SkillName::Unequipped, (Key)i);
		}
		else if (mainJson["skills"][i].as_string() == "GolpeFuerte") {
			setSkillEquiped(SkillName::GolpeFuerte, (Key)i);
		}
		else if (mainJson["skills"][i].as_string() == "Torbellino") {
			setSkillEquiped(SkillName::Torbellino, (Key)i);
		}
		else if (mainJson["skills"][i].as_string() == "Perforante") {
			setSkillEquiped(SkillName::DisparoPerforante, (Key)i);
		}
		else if (mainJson["skills"][i].as_string() == "Rebote") {
			setSkillEquiped(SkillName::Rebote, (Key)i);
		}
		else if (mainJson["skills"][i].as_string() == "Explosion") {
			setSkillEquiped(SkillName::Explosion, (Key)i);
		}
	}
	player_->initSkills();
}

void GameManager::loadHUD(jute::jValue& mainJson)
{
	for (int i = 0; i < 2; i++) {
		if (mainJson["objects"][i].as_string() == "null") {
			objectsEquipped_[i] = ObjectName::Unequipped;
		}
		else if (mainJson["objects"][i].as_string() == "Health") {
			objectsEquipped_[i] = ObjectName::Health;
		}
		else if (mainJson["objects"][i].as_string() == "Mana") {
			objectsEquipped_[i] = ObjectName::Mana;
		}
		else if (mainJson["objects"][i].as_string() == "Speed") {
			objectsEquipped_[i] = ObjectName::Speed;
		}
		else if (mainJson["objects"][i].as_string() == "Armor") {
			objectsEquipped_[i] = ObjectName::Armor;
		}
		else if (mainJson["objects"][i].as_string() == "Dmg") {
			objectsEquipped_[i] = ObjectName::Dmg;
		}
		else if (mainJson["objects"][i].as_string() == "Crit") {
			objectsEquipped_[i] = ObjectName::Crit;
		}
	}
	//Habilidades equipadas
	loadSkills(mainJson);
}

void GameManager::resetGame()
{
	currIsland_ = Island::Caribbean;
	unlockedIslands_ = Island::Caribbean;
	inventoryGold_ = 0;
	stashGold = 0;
	achievementPoints_ = 0;
	precisionPoints_ = 0;
	meleePoints_ = 0;
	clonPoints_ = 0;
	for (int i = 0; i < missionsStarted.size(); i++) {
		missionsStarted[i] = false;
		missionsComplete[i] = false;
	}
	for (int i = 0; i < skillsEquipped_.size() - 1; i++) {
		skillsEquipped_[i] = SkillName::Unequipped;
	}
	for (int i = 0; i < objectsEquipped_.size(); i++) {
		objectsEquipped_[i] = ObjectName::Unequipped;
	}
	for (InventoryButton* ob : *inventory_)delete ob;
	inventory_->clear();
	for (InventoryButton* ob : *stash_)delete ob;
	stash_->clear();
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
	objectsEquipped_[(int)key - (int)Key::One] = newObject;
	hud_->updateKey((int)key);
}

void GameManager::addToInventory(Equipment* ob) {
	//creamos un boton
	InventoryButton* b = new InventoryButton(app_, Vector2D{ 300,400 }, Vector2D{ 75,75 }, ob, nullptr);
	//A�adimos el boton a la lista y le asignamos un iterador con su posicion
	list <InventoryButton*>::iterator it = inventory_->insert(inventory_->end(), b);
	b->setIterator(it);
}