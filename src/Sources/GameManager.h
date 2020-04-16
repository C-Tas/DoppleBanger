#pragma once
#include <memory>
#include <iostream>
#include <list>
#include "Equipment.h"
#include "InventoryButton.h"
#include "RandEquipGen.h"
#include <vector>
#include "checkML.h"
#include "Player.h"
#include "Clon.h"

class Application;

using namespace std;
class Item;
class Player;
using lista = list<InventoryButton*>*;

//Enumerados que representan la �ltima isla desbloqueada
enum class Zone : int {
	CaribeanA		= 1,
	CaribeanB		= 2,
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
	 Precision = 0,
	 Melee = 0,
	 Ghost = 0
};

enum class missions : int {
	gallegaEnProblemas = 0,
	papelesSiniestros
	//En caso de tener misión para el loro añadirla tb (o si se añade el esqueleto)
};

#pragma region Skills

///Tipos de Skills que puede haber
enum class SkillType { Active, Pasive };

//Nombre de cada una de las habilidades del jugador
enum class SkillNames : int {

	//Enums auxiliares para las pasivas y para las habilidades que no están equipadas
	Unequipped,

	//Ataque melee
	GolpeFuerte,
	Invencible,
	Torbellino,

	//Ataquea distancia
	DisparoPerforante,
	Raudo,
	Rebote,

	//Clon
	Clon,
	LiberacionI,
	Explosion,
	LiberacionII,
	
};

//Enum para identificar las teclas de las habilidades
enum class SkillEquiped : int {
	Q,
	W,
	E,
	R
};
#pragma endregion


class GameManager {
private:
	//Numero de misiones secundarias
	static const int NUM_MISION = 10;
	//Puntero unico para evitar copias
	static unique_ptr<GameManager> instance_;
	//Cantidad de oro que genera en un nivel
	int currGold_ = 0;
	//Enum de la �ltima isla desbloqueada
	Island unlockedIslands_ = Island::Caribbean;
	//Enum de la isla actual
	Island currIsland_ = Island::Caribbean;
	//Puntos de haza�a
	int achievementPoints_ = 350;
	//Puntos de haza�a gastados en la rama precisi�n
	spentPoints precision_ = spentPoints::Precision;
	//Puntos de haza�a gastados e la rama melee
	spentPoints melee_ = spentPoints::Melee;
	//Puntos de haza�a gastados de la rama ghost
	spentPoints ghost_ = spentPoints::Ghost;
	//Puntero a la lista de item del inventario
	list<InventoryButton*>* inventory_ = new list<InventoryButton*>;
	//Cantidad de dinero almacenada en el inventario
	int inventoryGold = 300;
	//Puntero a la lista de items del alijo
	list<InventoryButton*>* stash_ = new list<InventoryButton*>;
	//Cantidad de dinero almacenada en el alijo
	int stashGold = 1000;
	//Vector que representa las misiones secundarias completadas
	vector<bool> missionsComplete = vector<bool>(NUM_MISION);
	//Vector que representa las misiones secundarias empezadas
	vector<bool> missionsStarted = vector<bool>(NUM_MISION);

	Application* app_ = nullptr;
	//Puntero al player a falta de estipular las variables que van a ir en gameManager sobre el player
	GameObject* player_ = nullptr;
	//Puntero al clon
	GameObject* clon_ = nullptr;
	//Vector que contiene las habilidades equipadas
	vector<SkillNames> skillsEquiped_ = {SkillNames::Unequipped,SkillNames::Unequipped,SkillNames::Unequipped,SkillNames::Clon };
	//Vector que contiene las habilidades desbloquedadas v[Skillname] corresponde con si está desbloqueda
	vector<bool> skillsUnlocked_ = { false, false ,false, false, false, false, false, true, false, false, false }; //Clon inicializada por defecto
	//Pendiente de guardar y cargar

public:
	//Constructor vac�o
	GameManager() {
		unlockedIslands_ = Island::Volcanic;
		for (int i = 0; i < NUM_MISION; i++) {
			missionsComplete[i] = false;
		}
	}
	//Destructor
	~GameManager() {
		for (InventoryButton* ob : *inventory_)delete ob;
		for (InventoryButton* ob : *stash_)delete ob;
		delete inventory_;
		delete stash_;
		delete app_;
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
	//Inicializa el oro, la actual isla y los puntos de haza�a
	inline void initGameManager(int currGold, Island unlockedIslands, int achievementPoints);

#pragma region getters
	//Devuelve el inventario
	const lista getInventory() { return inventory_; };
	//Devuelve el alijo
	const lista getStash() { return stash_; };
	//Devuelve el tamaño de fuente según el tamaño de la ventana
	const int getFontSize();
	//Devuelve el total de misiones secundarias
	const int getNumMission() { return NUM_MISION; };
	//Devuelve el oro conseguido
	const int getGold() { return currGold_; };
	//Devuelve los puntos de haza�a
	const int getAchievementPoints() { return achievementPoints_; };
	//Devuelve el n�mero de islas desbloqueadas
	const Island getUnlockedIslands() { return unlockedIslands_; };
	//Devuelve la isla actual
	const Island getCurrIsland() { return currIsland_; }
	//Devuelve los puntos gastados en la rama presici�n
	const spentPoints getPresicionPoints() { return precision_; };
	//Devuelve los puntos gastados en la rama melee
	const spentPoints getMeleePoints() { return melee_; };
	//Devuelve los puntos gastados en la rama fantasma
	const spentPoints getGhostPoints() { return ghost_; };
	//Devuelve true si la misi�n ha sido pasada
	const bool isThatMissionPass(missions mission) { return missionsComplete[(int)mission]; };
	//Devuelve true si la misi�n est� empezada
	const bool isThatMissionStarted(missions mission) { return missionsStarted[(int)mission]; };
	
	//Revisar
	//Devuelve la posici�n del player
	const Point2D getPlayerPos() { return player_->getPos(); };
	//Devuelve al jugador
	GameObject* getPlayer() { return player_; };
	//Devuelve al clon
	GameObject* getClon() { return clon_; };
	//Devuelve el dinero del inventario
	const int getInventoryGold() { return inventoryGold; }
	//Devuelve el dinero del alijo
	const int getStashGold() { return stashGold; }
	//Devuele la habilidad equipada
	const SkillNames getSkillEquiped(SkillEquiped skill) { return skillsEquiped_[(int)skill]; }
	//Devuelve la tecla en la que está equipada la habilidad
	const SkillEquiped getEquippedSkillKey(SkillNames skill) { int i = 0; 
		while (i < skillsEquiped_.size() && skillsEquiped_[i] != skill)i++;
		return (SkillEquiped)i;
	}
	//Devuelve el vector de skills
	const vector<SkillNames>& getAllSkillsEquipped() { return skillsEquiped_; }
	//Devuelve si la skill está desbloqueda
	const bool isSkillUnlocked(SkillNames skill) { return skillsUnlocked_[(int)skill]; }
	//Devuelve si la skill está equipada
	const bool isSkillAsign(SkillNames skill) { int i = 0; 
		while (i < skillsEquiped_.size() && skillsEquiped_[i] != skill)i++; 
		return !i == skillsEquiped_.size(); }
	
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
	//Asigna la isla actual
	inline void setIsland(int island) { currIsland_ = (Island)island; };
	//Asigna los archievement points
	inline void setArchievementPoints(int value) { achievementPoints_ = value; }
	//Asigna los puntos gastados a la rama precision
	inline void setPrecisionPoints(int value) { precision_ = (spentPoints)value; };
	//Asigna los puntos gastados a la rama melee
	inline void setMeleePoints(int value) { melee_ = (spentPoints)value; };
	//Asigna los puntos gastados a la rama Ghost
	inline void setGhostPoints(int value) { ghost_ = (spentPoints)value; };
	//Completa una misi�n secundaria
	inline void setCompleteMission(missions mission) { missionsComplete[(int)mission] = true; };
	//Empieza una misi�n secundaria
	inline void setStartedMission(missions mission) { missionsStarted[(int)mission] = true; };

	//Asigna al puntero de player
	inline void setPlayer(GameObject* player) { player_ = player; };
	//Asigna al puntero de clon
	inline void setClon(GameObject* clon) { clon_ = clon; };
	//borra al clon
	inline void deleteClon() { clon_ = nullptr; };
	//Añade(+) /Quita(-) dinero del inventario
	inline void addInventoryGold(int money) { inventoryGold += money; }
	////Añade(+) /Quita(-) dinero del alijo
	inline void addStashGold(int money) { stashGold += money; }
	///Asigna money como cantidad de dinero en el inventario
	inline void setInventoryGold(int money) { inventoryGold = money; }
	///Asigna money como cantidad de dinero en el alijo
	inline void setStashGold(int money) { stashGold = money; }
	//Actualiza la habilidad equipada
	inline void setSkillEquiped(SkillNames newSkill, SkillEquiped key) { skillsEquiped_[(int)key] = newSkill; }
	//Marca como desbloqueda la skill que pases como parámetro
	inline void setSkillUnlocked(SkillNames skill) { skillsUnlocked_[(int)skill] = true; }
#pragma endregion
};