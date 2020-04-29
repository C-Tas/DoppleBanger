#include "GameManager.h"
#include "Application.h"
#include "Player.h"
#include "usable.h"
#include "Armor.h"
#include "Boots.h"
#include "Gloves.h"
#include "Gun.h"
#include "Sword.h"
#include "InventoryButton.h"
#include "EmpoweredSkill.h"
#include "WhirlwindSkill.h"
#include "RicochetSkill.h"
#include "PerforateSkill.h"
#include "ClonSelfDestructSkill.h"

using namespace jute;
unique_ptr<GameManager> GameManager::instance_;

GameManager::GameManager() {
	unlockedIslands_ = Island::Volcanic;
	for (int i = 0; i < (int)missions::Size; i++) {
		missionsComplete[i] = false;
	}
	currEquip_.armor_ = new Armor(app_, 10, 10, 10, equipType::ArmorI);
	currEquip_.gloves_ = new Gloves(app_, 10, 10, 10, equipType::GlovesI);
	currEquip_.boots_ = new Boots(app_, 10, 10, 10, equipType::BootsI);
	currEquip_.sword_ = new Sword(app_, 10, 10, 10, equipType::SwordI);
	currEquip_.gun_ = new Gun(app_, 10, 10, 10, equipType::PistolI);
}
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
	saveInventory(slot, mainJson);
	//Alijo
	saveStash(slot, mainJson);
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
	//Informacion de los objetos que se va a guardar
	jValue objectsValue(jType::JARRAY);
	for (int i = 0; i < currEquip_.potions_.size(); i++) {
		if (currEquip_.potions_[i] != nullptr) {
			switch (currEquip_.potions_[i]->getType())
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
		currEquip_.armor_,
		currEquip_.gloves_,
		currEquip_.boots_,
		currEquip_.sword_,
		currEquip_.gun_
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

void GameManager::saveInventory(ofstream& slot, jute::jValue& mainJson)
{
}

void GameManager::saveStash(ofstream& slot, jute::jValue& mainJson)
{
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
	loadEquipment(mainJson);
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

void GameManager::loadEquipment(jute::jValue& mainJson){
	//Objetos equipados
	for (int i = 0; i < 2; i++) {
		if (mainJson["objects"][i].as_string() == "Health") {
			currEquip_.potions_[i] = new usable(app_, potionType::Health);
			objectsEquipped_.at(i) = ObjectName::Health;
			hud_->updateKey(i + (int)Key::One);
		}
		else if (mainJson["objects"][i].as_string() == "Mana") {
			currEquip_.potions_[i] = new usable(app_, potionType::Mana);
			objectsEquipped_.at(i) = ObjectName::Mana;
			hud_->updateKey(i + (int)Key::One);
		}
		else if (mainJson["objects"][i].as_string() == "Speed") {
			currEquip_.potions_[i] = new usable(app_, potionType::Speed);
			objectsEquipped_.at(i) = ObjectName::Speed;
			hud_->updateKey(i + (int)Key::One);
		}
		else if (mainJson["objects"][i].as_string() == "Armor") {
			currEquip_.potions_[i] = new usable(app_, potionType::Armor);
			objectsEquipped_.at(i) = ObjectName::Armor;
			hud_->updateKey(i + (int)Key::One);
		}
		else if (mainJson["objects"][i].as_string() == "Dmg") {
			currEquip_.potions_[i] = new usable(app_, potionType::Damage);
			objectsEquipped_.at(i) = ObjectName::Damage;
			hud_->updateKey(i + (int)Key::One);
		}
		else if (mainJson["objects"][i].as_string() == "Crit") {
			currEquip_.potions_[i] = new usable(app_, potionType::Crit);
			objectsEquipped_.at(i) = ObjectName::Crit;
			hud_->updateKey(i + (int)Key::One);
		}
	}
	//Se comprueba que no haya equipo ya definido (el equipamiento inicial)
	if (currEquip_.armor_ != nullptr) delete currEquip_.armor_;
	if (currEquip_.gloves_ != nullptr) delete currEquip_.gloves_;
	if (currEquip_.boots_ != nullptr) delete currEquip_.boots_;
	if (currEquip_.sword_ != nullptr) delete currEquip_.sword_;
	if (currEquip_.gun_ != nullptr) delete currEquip_.gun_;

	//Pechera
	double auxPrice = mainJson["equipment"][0]["price"].as_double();
	double auxStat1 = mainJson["equipment"][0]["health"].as_double();
	double auxStat2 = mainJson["equipment"][0]["armor"].as_double();
	equipType auxType = (equipType)mainJson["equipment"][0]["name"].as_int();
	currEquip_.armor_ = new Armor(app_, auxPrice, auxStat1, auxStat2, auxType);
	//Guantes
	auxPrice = mainJson["equipment"][1]["price"].as_double();
	auxStat1 = mainJson["equipment"][1]["critic"].as_double();
	auxStat2 = mainJson["equipment"][1]["armor"].as_double();
	auxType = (equipType)mainJson["equipment"][1]["name"].as_int();
	currEquip_.gloves_ = new Gloves(app_, auxPrice, auxStat1, auxStat2, auxType);
	//Botas
	auxPrice = mainJson["equipment"][2]["price"].as_double();
	auxStat1 = mainJson["equipment"][2]["speed"].as_double();
	auxStat2 = mainJson["equipment"][2]["armor"].as_double();
	auxType = (equipType)mainJson["equipment"][2]["name"].as_int();
	currEquip_.boots_ = new Boots(app_, auxPrice, auxStat1, auxStat2, auxType);
	//Espada
	auxPrice = mainJson["equipment"][3]["price"].as_double();
	auxStat1 = mainJson["equipment"][3]["damage"].as_double();
	auxStat2 = mainJson["equipment"][3]["rate"].as_double();
	auxType = (equipType)mainJson["equipment"][3]["name"].as_int();
	currEquip_.sword_ = new Sword(app_, auxPrice, auxStat1, auxStat2, auxType);
	//Pistola
	auxPrice = mainJson["equipment"][4]["price"].as_double();
	auxStat1 = mainJson["equipment"][4]["damage"].as_double();
	auxStat2 = mainJson["equipment"][4]["rate"].as_double();
	auxType = (equipType)mainJson["equipment"][4]["name"].as_int();
	currEquip_.gun_ = new Gun(app_, auxPrice, auxStat1, auxStat2, auxType);
	player_->load();
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
		else if (mainJson["objects"][i].as_string() == "Damage") {
			objectsEquipped_[i] = ObjectName::Damage;
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

	//Reseteo del equipamiento, se vuelve al inicial, sin pociones
	delete currEquip_.armor_;
	delete currEquip_.gloves_;
	delete currEquip_.boots_;
	delete currEquip_.sword_;
	delete currEquip_.gun_;
	currEquip_.armor_ = new Armor(app_, 10, 10, 10, equipType::ArmorI);
	currEquip_.gloves_ = new Gloves(app_, 10, 10, 10, equipType::GlovesI);
	currEquip_.boots_ = new Boots(app_, 10, 10, 10, equipType::BootsI);
	currEquip_.sword_ = new Sword(app_, 10, 10, 10, equipType::SwordI);
	currEquip_.gun_ = new Gun(app_, 10, 10, 10, equipType::PistolI);
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