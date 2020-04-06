#pragma once
#include <memory>
#include <iostream>
#include <list>
#include "Equipment.h"
#include "RandEquipGen.h"
#include <vector>
#include "checkML.h"
#include "Player.h"
#include "Skill.h"
#include "Clon.h"
#include "HUD.h"

using namespace std;
class Item;
using lista = list<Item>*;

//Enumerados que representan la última isla desbloqueada
enum class Zone : int {
	CaribeanA		= 0,
	CaribeanB		= 1,
	CaribeanC		= 3,
	CaribeanBoss	= 4,
	SpookyA			= 5,
	SpookyB			= 6,
	SpookyC			= 7,
	SpookyD			= 8,
	SpookyBoos		= 9,
	Volcanic		= 10
};
enum class Island : int {
	Caribbean,
	Spooky,
	Volcanic
};
enum class spentPoints : int {
	 Precision = 1,
	 Melee,
	 Ghost
};

enum class missions : int {
	nombreMision = 0,
	//Poner aqui nombre de las misiones
};

//Nombre de cada una de las habilidades del jugador
enum class SkillName : int {
	Unequipped,

	//Ataque melee
	GolpeFuerte,
	Torbellino,

	//Ataquea distancia
	DisparoPerforante,
	Rebote,

	//Clon
	Clon,
	Explosion
};

enum class ObjectName : int {
	Unequipped,

	//Pociones
	Health,
	Mana,
	Speed,
	Armor,
	Dmg,
	Crit
};

//Enum para identificar las teclas de las habilidades
enum class SkillKey : int {
	Q,
	W,
	E,
	R
};

//Enum para identificar las teclas de los objetos
enum class ObjectKey : int {
	One,
	Two
};

class GameManager {
private:
	//Numero de misiones secundarias
	static const int NUM_MISION = 10;
	//Puntero unico para evitar copias
	static unique_ptr<GameManager> instance_;
	//Cantidad de oro que genera en un nivel
	int currGold_ = 0;
	//Enum de la última isla desbloqueada
	Island unlockedIslands_ = Island::Caribbean;
	//Enum de la isla actual
	Island currIsland_ = Island::Caribbean;
	//Puntos de hazaña
	int achievementPoints_ = 100;
	//Puntos de hazaña gastados en la rama precisión
	spentPoints precision_ = spentPoints::Precision;
	//Puntos de hazaña gastados e la rama melee
	spentPoints melee_ = spentPoints::Melee;
	//Puntos de hazaña gastados de la rama ghost
	spentPoints ghost_ = spentPoints::Ghost;
	//Puntero a la lista de item del inventario
	list<Item>* inventory_ = nullptr;
	//Puntero a la lista de items del alijo
	list<Item>* stash_ = nullptr;
	//Vector que representa las misiones secundarias completadas
	vector<bool> missionsComplete = vector<bool>(NUM_MISION);
	//Vector que representa las misiones secundarias empezadas
	vector<bool> missionsStarted = vector<bool>(NUM_MISION);
	//Vector de cooldowns de las habilidades equipadas
	vector<bool> skillsCooldown = vector<bool>(4);
	//Vector que contiene las habilidades equipadas
	vector<SkillName> skillsEquipped = vector<SkillName>(4);
	//Vector que contiene los objetos equipados
	vector<ObjectName> objectsEquipped = vector<ObjectName>(2);
	//Puntero al player a falta de estipular las variables que van a ir en gameManager sobre el player
	Draw* player_ = nullptr;
	//Puntero al clon
	Draw* clon_ = nullptr;
	//Puntero al HUD
	HUD* hud_ = nullptr;
	//Pendiente de guardar y cargar

public:
	//Constructor vacío
	GameManager() {
		unlockedIslands_ = Island::Volcanic;
		for (int i = 0; i < NUM_MISION; i++) {
			missionsComplete[i] = false;
		}
		for (int i = 0; i < 4; i++) {
			skillsCooldown[i] = false;
			skillsEquipped[i] = SkillName::Rebote;
		}
		for (int i = 0; i < 2; i++) {
			objectsEquipped[i] = ObjectName::Crit;
		}
	}
	//Destructor
	~GameManager() {
		inventory_, stash_ = nullptr;
	}
	//Construye un nuevo gameManger si es null
	static GameManager* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new GameManager());
		}
		return instance_.get();
	}
	GameManager(GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	//Inicializa el oro, la actual isla y los puntos de hazaña
	inline void initGameManager(int currGold, Island unlockedIslands, int achievementPoints);

#pragma region getters
	//Devuelve el inventario
	const lista getInventory() { return inventory_; };
	//Devuelve el alijo
	const lista getStash() { return stash_; };
	//Devuelve el oro conseguido
	const int getGold() { return currGold_; };
	//Devuelve los puntos de hazaña
	const int getAchievementPoints() { return achievementPoints_; };
	//Devuelve el número de islas desbloqueadas
	const Island getUnlockedIslands() { return unlockedIslands_; };
	//Devuelve la isla actual
	const Island getCurrIsland() { return currIsland_; }
	//Devuelve los puntos gastados en la rama presición
	const spentPoints getPresicionPoints() { return precision_; };
	//Devuelve los puntos gastados en la rama melee
	const spentPoints getMeleePoints() { return melee_; };
	//Devuelve los puntos gastados en la rama fantasma
	const spentPoints getGhostPoints() { return ghost_; };
	//Devuelve true si la misión ha sido pasada
	const bool isThatMissionPass(missions mission) { return missionsComplete[(int)mission]; };
	//Devuelve true si la misión está empezada
	const bool isThatMissionStarted(missions mission) { return missionsStarted[(int)mission]; };
	//Devuelve si está activo el cooldown de la habilidad
	const bool getSkillCooldown(int skill) { return skillsCooldown[skill]; };
	//Devuele la habilidad equipada
	const SkillName getSkillEquipped(int skill) { return skillsEquipped[skill]; };
	//Devuelve el objeto equipado
	const ObjectName getObjectEquipped(int object) { return objectsEquipped[object]; };
	//Revisar
	//Devuelve la posición del player
	const Point2D getPlayerPos() { return player_->getPos(); };
	//Devuelve al jugador
	Draw* getPlayer() { return player_; };
	//Devuelve al clon
	Draw* getClon() { return clon_; };
#pragma endregion

#pragma region setters
	//Asigna el puntero al inventario
	inline void setInventoryPointer(lista inv) { inventory_ = inv; };
	//Asigna el puntero al alijo
	inline void setStashPointer(lista stash) { stash_ = stash; };
	//Asigna a la ultima isla desbloqueada
	inline void setUnlockedIslands(Island island) { unlockedIslands_ = island; };
	//Asigna la nueva isla actual
	inline void setCurrIsland(Island newIsland) { currIsland_ = newIsland; }
	//Asigna los puntos gastados a la rama precision
	inline void setPrecisionPoints(int value) { precision_ = (spentPoints)value; };
	//Asigna los puntos gastados a la rama melee
	inline void setMeleePoints(int value) { melee_ = (spentPoints)value; };
	//Asigna los puntos gastados a la rama Ghost
	inline void setGhostPoints(int value) { ghost_ = (spentPoints)value; };
	//Completa una misión secundaria
	inline void setCompleteMission(missions mission) { missionsComplete[(int)mission] = true; };
	//Empieza una misión secundaria
	inline void setStartedMission(missions mission) { missionsStarted[(int)mission] = true; };
	//Actualiza el estado del cooldown, no es inline por el HUD
	void setSkillCooldown(bool cooldown, SkillKey key);
	//Actualiza la habilidad equipada en el HUD y en el vector, no es inline por el HUD
	void setSkillEquiped(SkillName newSkill, SkillKey key);
	//Actualiza el objeto equipado en el HUD y en el vector, no es inline por el HUD
	void setObjectEquipped(ObjectName newObject, ObjectKey key);
	//Asigna al puntero de player
	inline void setPlayer(Draw* player) { player_ = player; };
	//Asigna al puntero de clon
	inline void setClon(Draw* clon) { clon_ = clon; };
	//Asigna el puntero de hud
	inline void setHUD(HUD* hud) { hud_ = hud; }
	//borra al clon
	inline void deleteClon() { clon_ = nullptr; };
#pragma endregion
};