#pragma once

#include <memory>
#include <iostream>
#include <list>
#include "Equipment.h"
#include "InventoryButton.h"
#include "RandEquipGen.h"
#include <vector>
#include "checkML.h"


using namespace std;
class Item;
using lista = list<InventoryButton*>;

//Enumerados que representan la �ltima isla desbloqueada
enum class Island : int {
	CaribeanA		= 1,
	CaribeanB		= 2,
	CaribeanC		= 3,
	CaribeanBoss	= 4,
	SpookyA			= 5,
	SpookyB			= 6,
	SpookyC			= 7,
	SpookyBoos		= 8,
	Volcanic		= 9
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


class GameManager {
private:
	//Numero de misiones secundarias
	static const int NUM_MISION = 10;
	//Puntero unico para evitar copias
	static unique_ptr<GameManager> instance_;
	//Cantidad de oro que genera en un nivel
	int currGold_ = 0;
	//Enum de la �ltima isla desbloqueada
	Island currIsland_;
	//Puntos de haza�a
	int achievementPoints_ = 0;
	//Puntos de haza�a gastados en la rama precisi�n
	spentPoints precision_ = spentPoints::Precision;
	//Puntos de haza�a gastados e la rama melee
	spentPoints melee_ = spentPoints::Melee;
	//Puntos de haza�a gastados de la rama ghost
	spentPoints ghost_ = spentPoints::Ghost;
	//Puntero a la lista de item del inventario
	list<InventoryButton*> inventory_;
	//Puntero a la lista de items del alijo
	list<InventoryButton*> stash_;
	//Vector que representa las misiones secundarias completadas
	vector<bool> missionsComplete = vector<bool>(NUM_MISION);
	//Vector que representa las misiones secundarias empezadas
	vector<bool> missionsStarted = vector<bool>(NUM_MISION);
	//Pendiente de guardar y cargar
public:
	//Constructor vac�o
	GameManager() {
		currIsland_ = Island::CaribeanA;
		for (int i = 0; i < NUM_MISION; i++) {
			missionsComplete[i] = false;
		}
	}
	//Destructor
	~GameManager() {
		for (InventoryButton* ob : inventory_)delete ob;
		for (InventoryButton* ob : stash_)delete ob;
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
	inline void initGameManager(int currGold, Island currIsland, int achievementPoints);

#pragma region getters
	//Devuelve el inventario
	const lista getInventory() { return inventory_; };
	//Devuelve el alijo
	const lista getStash() { return stash_; };
	//Devuelve el oro conseguido
	const int getGold() { return currGold_; };
	//Devuelve los puntos de haza�a
	const int getAchievementPoints() { return achievementPoints_; };
	//Devuelve la actual isla
	const int getCurrIsland() { return (int)currIsland_; };
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
#pragma endregion

#pragma region setters
	//Asigna el puntero al inventario
	inline void setInventoryPointer(lista inv) { inventory_ = inv; };
	//Asigna el puntero al alijo
	inline void setStashPointer(lista stash) { stash_ = stash; };
	//Asigna a la ultima isla desbloqueada
	inline void setIsland(Island island) { currIsland_ = island; };
	inline void setIsland(int island) { currIsland_ = (Island)island; };
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
#pragma endregion
};



