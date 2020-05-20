#pragma once
#include <memory>
#include <list>
#include <vector>
#include <iostream>
#include "InventoryButton.h"
#include "RandEquipGen.h"
#include "Equipment.h"
#include "Clon.h"
#include "HUD.h"
#include "checkML.h"
#include "jute.h"

using namespace std;
class Item;
using lista = list<InventoryButton*>*;
class Application;
class Player;
class Armor;
class Gloves;
class Boots;
class Sword;
class Gun;
class usable;

//Enumerados que representan la �ltima isla desbloqueada
enum class Zone : int {
	CaribeanA = 1,
	CaribeanB = 2,
	CaribeanC = 3,
	CaribeanBoss = 4,
	SpookyA = 5,
	SpookyB = 6,
	SpookyC = 7,
	SpookyD = 8,
	SpookyBoss = 9,
	Volcanic = 10
};
enum class Island : int {
	Caribbean,
	Spooky,
	Volcanic
};
enum class PointsTree : int {
	Precision = 0,
	Melee = 0,
	Ghost = 0
};

enum class missions : int {
	gallegaEnProblemas = 0,
	papelesSiniestros,
	masValePajaroEnMano,
	arlongPark,
	//En caso de tener misión para el loro añadirla tb (o si se añade el esqueleto)

	//Para saber el tamaño
	Size
};

#pragma region Skills

///Tipos de Skills que puede haber
enum class SkillType { Active, Pasive };

//Nombre de cada una de las habilidades del jugador
enum class SkillName : int {
	//Ataque a distancia
	DisparoPerforante,
	Raudo,
	Rebote,

	//Ataque melee
	GolpeFuerte,
	Invencible,
	Torbellino,

	//Clon
	Clon,
	LiberacionI,
	Explosion,
	LiberacionII,

	//Enums auxiliares para las pasivas y para las habilidades que no están equipadas
	Unequipped
};

//Enum para identificar las teclas de las habilidades
enum class Key : int {
	Q,
	W,
	E,
	R,
	One,
	Two
};
#pragma endregion
#pragma region Objetos
enum class ObjectName : int { Health, Mana, Speed, Armor, Damage, Crit, Unequipped};
#pragma endregion

struct playerEquipment
{
	//Equipamiento del jugador
	Armor* armor_ = nullptr;
	Gloves* gloves_ = nullptr;
	Boots* boots_ = nullptr;
	Sword* sword_ = nullptr;
	Gun* gun_ = nullptr;

	vector<usable*> potions_{
		nullptr,
		nullptr
	};
};

class GameManager {
private:
	//Puntero unico para evitar copias
	static unique_ptr<GameManager> instance_;
	//Milisegundo para considerar una pausa
	const int DELAYTIME = 200;
	//Puntos de haza�a
	int achievementPoints_ = 0;
	//Cantidad de dinero almacenada en el inventario
	int inventoryGold_ = 0;
	//Cantidad de dinero almacenada en el alijo
	int stashGold_ = 0;
	//Booleano que indica si estamos en el barco
	bool onShip_ = true;
	//Enum de la �ltima isla desbloqueada
	Island unlockedIslands_ = Island::Caribbean;
	//Enum de la isla actual
	Island currIsland_ = Island::Caribbean;
	//Maximo de los puntos de hazaña
	int maxPoints_ = 1000;
	//Puntos de haza�a gastados en la rama precisi�n
	int precisionPoints_ = 0;
	//Puntos de haza�a gastados e la rama melee
	int meleePoints_ = 0;
	//Puntos de haza�a gastados de la rama ghost
	int clonPoints_ = 0;
	//Puntero a la lista de item del inventario
	list<InventoryButton*>* inventory_ = new list<InventoryButton*>;
	//Puntero a la lista de items del alijo
	list<InventoryButton*>* stash_ = new list<InventoryButton*>;
	//Puntero a la lista de items de la tienda
	list<InventoryButton*>* shop_ = new list<InventoryButton*>;
	//Vector que representa las misiones secundarias completadas
	vector<bool> missionsComplete_ = vector<bool>((int)missions::Size);
	//Vector que representa las misiones secundarias empezadas
	vector<bool> missionsStarted_ = vector<bool>((int)missions::Size);
	//Vector de cooldowns de las habilidades equipadas
	vector<bool> skillsCooldown_ = { false, false, false, false };
	//Vector que contiene las habilidades desbloquedadas v[Skillname] corresponde con si está desbloqueda
	vector<bool> skillsUnlocked_ = { false, false ,false, false, false, false, true, false, false, false }; //Clon inicializada por defecto
	//Vector que contiene los puntos invertidos en cada rama
	vector<int> pointrTree_ = { 0, 0, 0 };
	//Vector que contiene la cantidad de enemigos que se han muerto de la mision correspondiente
	//<gallegaEnProblemas, papelesSiniestros, masValePajaroEnMano, arlongPark >
	vector<int> countEnemiesMission_ = { 0, 0, 0, 0 };
	//Recompensas de las misiones
	//Oro <gallegaEnProblemas, papelesSiniestros, masValePajaroEnMano, arlongPark >
	vector <int> goldReward_ = { 200, 200, 200, 200 };
	//Hazaña <gallegaEnProblemas, papelesSiniestros, masValePajaroEnMano, arlongPark >
	vector <int> pointsReward_ = { 200, 200, 200, 200 };
	//Vector que contiene el numero de enemigos que se tiene que matar en cada mision
	//<gallegaEnProblemas, papelesSiniestros, masValePajaroEnMano, arlongPark >
	vector<int> enemiesMission_ = { 4, 3, 2, 3 };
	//Vector que contiene las habilidades equipadas
	vector<SkillName> skillsEquipped_ = { SkillName::Unequipped, SkillName::Unequipped, SkillName::Unequipped, SkillName::Clon };
	//Vector que contiene los objetos equipados
	vector<ObjectName> objectsEquipped_ = { ObjectName::Unequipped, ObjectName::Unequipped };
	//Constante del tamaño de pintado de los tiles
	const int tileSize = 128;
 

	//Puntero al player a falta de estipular las variables que van a ir en gameManager sobre el player
	Player* player_ = nullptr;
	//Equipamento del player
	playerEquipment currEquip_;
	//Puntero al clon
	GameObject* clon_ = nullptr;
	//Puntero al HUD
	HUD* hud_ = nullptr;
	//puntero a la aplicacion
	Application* app_ = nullptr;
	//actual zona en la que nos encontramos
	Zone currentZone_ = Zone::CaribeanA;
	//vida actual del player(para guardarla al pasar de zona)
	double currPlayerLife_ = 0;
	//mana actual del player(para guardarlo al pasar de zona)
	double currPlayerMana_ = 0;
	//Metodos para guardar y cargar partida
	#pragma region Guardar/Cargar
		#pragma region Guardar
		//Guarda los datos en el json pasado como parámetro
		void save(ofstream& slot);
		//Guarda los datos de tipo JNUMBER
		void saveJNUMBER(jute::jValue& mainJson);
		//Guarda las misiones
		void saveMissions(jute::jValue& mainJson);
		//Guarda las habilidades equipadas
		void saveSkills(jute::jValue& mainJson);
		//Guarda el equipamiento del player
		void saveEquipment(jute::jValue& mainJson);
		//Guarda el inventario
		void saveInventory_Stash(jute::jValue& mainJson);
		#pragma endregion
		#pragma region Cargar
		//Carga los datos desde el json pasado como parámetro
		void load(string jsonName);
		//Carga los datos de tipo JNUMBER
		void loadJNUMBER(jute::jValue& mainJson);
		//Carga las habilidades
		void loadSkills(jute::jValue& mainJson);
		//Carga las misiones
		void loadMissions(jute::jValue& mainJson);
		//Carga el equipamiento
		void loadEquipment(jute::jValue& mainJson);
		//Carga las texturas del HUD
		void loadHUD(jute::jValue& mainJson);
		//Carga el inventario
		void loadInventory_Stash(jute::jValue& mainJson);
		//Carga un objeto de tipo Equipment
		void loadEquipType(jute::jValue& mainJson, string tag, int i);
		//Carga un objeto de tipo usable
		void loadUsableType(jute::jValue& mainJson, string tag, int i);
		#pragma endregion
	#pragma endregion

	bool hudActive_ = false;
	//Fases de los NPCS
	bool tutorial = false;
	int venancioPhase = 0;

public:
	//Constructor vacio
	GameManager();
	//Destructor
	~GameManager() {
		for (InventoryButton* ob : *inventory_)delete ob;
		for (InventoryButton* ob : *stash_)delete ob;
		for (InventoryButton* ob : *shop_)delete ob;
		delete shop_;
		delete inventory_;
		delete stash_;
		//Se borra el equipo
		if (currEquip_.armor_ != nullptr) delete currEquip_.armor_;
		if (currEquip_.gloves_ != nullptr) delete currEquip_.gloves_;
		if (currEquip_.boots_ != nullptr) delete currEquip_.boots_;
		if (currEquip_.sword_ != nullptr) delete currEquip_.sword_;
		if (currEquip_.gun_ != nullptr) delete currEquip_.gun_;
		for (int i = 0; i < currEquip_.potions_.size(); i++) {
			if(currEquip_.potions_.at(i) != nullptr)
				delete currEquip_.potions_.at(i);
		}
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

#pragma region Guardar/Cargar
	//Guardar en slot1
	void saveSlot1();
	//Guardar en slot2
	void saveSlot2();
	//Guardar en slot3
	void saveSlot3();
	//Cargar slot1
	void loadSlot1();
	//Cargar slot2
	void loadSlot2();
	//Cargar slot3
	void loadSlot3();
	//Resetea los valores del juego para una partida nueva
	//cuando se vuelva al menú principal
	void resetGameManager();
#pragma endregion

#pragma region getters
	//Devuelve true si la misi�n ha sido pasada
	const bool isThatMissionPass(missions mission) { return missionsComplete_[(int)mission]; };
	//Devuelve true si la misi�n est� empezada
	const bool isThatMissionStarted(missions mission) { return missionsStarted_[(int)mission]; };
	//Devuelve si está activo el cooldown de la habilidad
	const bool getSkillCooldown(int skill) { return skillsCooldown_[skill]; };
	//Devuelve si la skill está desbloqueda
	const bool isSkillUnlocked(SkillName skill) { return skillsUnlocked_[(int)skill]; };
	//Devuelve si la skill está equipada
	const bool isSkillAsign(SkillName skill);
	//Devuelve si estamos o no en la isla
	const bool getOnShip() { return onShip_; };

	const int getTileSize() { return tileSize; };

	//Devuelve el oro conseguido
	const int getGold() { return inventoryGold_; };
	//Devuelve el tiempo que hemos puesto a ojo para saber si ha habido pausa :)
	const int getDelayTime() { return DELAYTIME; };
	//Devuelve los puntos de haza�a
	const int getAchievementPoints() { return achievementPoints_; };
	//Devuelve el dinero del inventario
	const int getInventoryGold() { return inventoryGold_; }
	//Devuelve el dinero del alijo
	const int getStashGold() { return stashGold_; }
	//Devuelve el tamaño de fuente según el tamaño de la ventana
	const int getFontSize();
	//Devuelve el total de misiones secundarias
	const int getNumMission() { return (int)missions::Size; };
	//Devuelve el numero de enemigos muertos en cada mision
	const int getCounterEnemiesMission(missions tagMission) { return countEnemiesMission_.at((int)tagMission); };
	//Devuelve el numero de enemigos que hay que matar en cada mision
	const int getEnemiesMission(missions tagMission) { return enemiesMission_.at((int)tagMission); };
	//Devuelve el inventario
	const lista getInventory() { return inventory_; };
	//Devuelve el alijo
	const lista getStash() { return stash_; };
	//Devuelve la tienda
	const lista getShop() { return shop_; };

	//Devuelve el n�mero de islas desbloqueadas
	const Island getUnlockedIslands() { return unlockedIslands_; };
	//Devuelve la isla actual
	const Island getCurrIsland() { return currIsland_; }
	//Devuelve el vector de skills
	const vector<SkillName>& getAllSkillsEquipped() { return skillsEquipped_; }

	//Devuelve el máximo de los puntos de hazaña
	const int getMaxPoints() { return maxPoints_; };
	//Devuelve los puntos gastados en la rama presici�n
	const int getPresicionPoints() { return precisionPoints_; };
	//Devuelve los puntos gastados en la rama melee
	const int getMeleePoints() { return meleePoints_; };
	//Devuelve los puntos gastados en la rama fantasma
	const int getGhostPoints() { return clonPoints_; };
	
	//Devuele la habilidad asignada en la tecla
	const SkillName getEquippedSkill(Key key) { return skillsEquipped_[(int)key]; }
	//Devuelve la tecla en la que está equipada la habilidad
	const Key getEquippedSkillKey(SkillName skill);
	//Devuelve el objeto equipado
	const ObjectName getObjectEquipped(Key key) { return objectsEquipped_[(int)key - (int)Key::One]; };
	
	//Devuelve la posici�n del player
	const Point2D getPlayerPos();
	//Devuelve al jugador
	Player* getPlayer() { return player_; };
	//Devuelve el equipamiento del player
	playerEquipment& getEquip() { return currEquip_; };
	//Devuelve al clon
	GameObject* getClon() { return clon_; };
	//Devuelve el HUD
	HUD* getHUD() { return hud_; };
	//Devuelve la zona en la que nos encontramos actualmente
	Zone getCurrentZone() { return currentZone_; }
	//Devuelve el currentLife del player
	const double getCurrentPlayerLife() { return currPlayerLife_; }
	//Devuelve el currentMana del player
	const double getCurrentPlayerMana() { return currPlayerMana_; }
	
#pragma endregion

#pragma region setters
	//Suma puntos de hazaña
	inline void addArchievementPoints(int value) { achievementPoints_ += value; }
	//Asigna los archievement points
	inline void setArchievementPoints(int value) { achievementPoints_ = value; };
	//Asigna los puntos gastados a la rama precision
	inline void setPrecisionPoints(int value) { precisionPoints_ = value; };
	//Asigna los puntos gastados a la rama melee
	inline void setMeleePoints(int value) { meleePoints_ = value; };
	//Asigna los puntos gastados a la rama Ghost
	inline void setGhostPoints(int value) { clonPoints_ = value; };
	//Añade(+) /Quita(-) dinero del inventario
	inline void addInventoryGold(int money) { inventoryGold_ += money; }
	////Añade(+) /Quita(-) dinero del alijo
	inline void addStashGold(int money) { stashGold_ += money; };
	///Asigna money como cantidad de dinero en el inventario
	inline void setInventoryGold(int money) { inventoryGold_ = money; }
	///Asigna money como cantidad de dinero en el alijo
	inline void setStashGold(int money) { stashGold_ = money; };
	//Indica si estamos o no en el barco
	inline void setOnShip(bool onShip) { onShip_ = onShip; };

	inline void setShop(list<InventoryButton*>* shop) { shop_ = shop; };

	//Reseteo del inventario
	void resetInventory();
	//Asigna el puntero al inventario
	inline void setInventoryPointer(lista inv) { inventory_ = inv; };
	//Asigna el puntero al alijo
	inline void setStashPointer(lista stash) { stash_ = stash; };
	
	//Añade una muerte al contador de muertes de la mision
	inline void addMissionCounter(missions tagMission) { countEnemiesMission_.at((int)tagMission)++; }
	//Reinicia el contador de muertes de la mision
	inline void resetMissionCounter(missions tagMission) { countEnemiesMission_.at((int)tagMission) = 0; }
	//Completa una misi�n secundaria
	inline void setCompleteMission(missions mission, bool complete) {
		missionsComplete_[(int)mission] = complete;
		if (complete) {
			inventoryGold_ += goldReward_.at((int)mission);
			achievementPoints_ += pointsReward_.at((int)mission);
		}
	};
	//Empieza una misi�n secundaria
	inline void setStartedMission(missions mission, bool started) { missionsStarted_[(int)mission] = started; };
	//Asigna a la ultima isla desbloqueada
	inline void setUnlockedIslands(Island island) { unlockedIslands_ = island; };
	//Asigna la nueva isla actual
	inline void setCurrIsland(Island newIsland) { currIsland_ = newIsland; };
	//Marca como desbloqueda la skill que pases como parámetro
	inline void setSkillUnlocked(SkillName skill) { skillsUnlocked_[(int)skill] = true; };
	//Marca como bloqueada la skill que pases como parámetro
	inline void setSkillLocked(SkillName skill) { skillsUnlocked_[(int)skill] = false; };
	//Actualiza el estado del cooldown, no es inline por el HUD
	void setSkillCooldown(bool cooldown, Key key);
	//Actualiza la habilidad equipada en el HUD y en el vector, no es inline por el HUD
	void setSkillEquiped(SkillName newSkill, Key key);
	//Actualiza el objeto equipado en el HUD y en el vector, no es inline por el HUD
	void setObjectEquipped(ObjectName newObject, Key key);
	//
	Application* getApp() { return app_; }
	//Asigna al puntero de player
	inline void setPlayer(Player* player) { player_ = player; };
	//Equipamiento
	//Inicializa el equipamiento base
	playerEquipment& initEquipment();
	void setArmor(Armor* armor) { currEquip_.armor_ = armor; };
	void setGloves(Gloves* armor) { currEquip_.gloves_ = armor; };
	void setBoots(Boots* armor) { currEquip_.boots_ = armor; };
	void setSword(Sword* armor) { currEquip_.sword_ = armor; };
	void setGun(Gun* armor) { currEquip_.gun_ = armor; };
	void setPotion(int slot, usable* newPot) {
		currEquip_.potions_.at(slot) = newPot;
	}
	//Asigna al puntero de clon
	inline void setClon(GameObject* clon) { clon_ = clon; };
	//Asigna el puntero de hud
	inline void setHUD(HUD* hud) { hud_ = hud; hudActive_ = !hudActive_; };

	//borra al clon
	inline void deleteClon() { clon_ = nullptr; };
	//aplicacion
	inline void setApp(Application* app) { app_ = app; };
	//Asigna la nueva zona en la que nos encontramos
	inline void setCurrentZone(Zone newZone) { currentZone_ = newZone; }
	inline void setHudActive(bool active) { hudActive_ = active; }

	//Devuelve el currentLife del player
	inline void setCurrentPlayerLife(double newPlayerLife) { currPlayerLife_ = newPlayerLife; }
	//Devuelve el currentMana del player
	inline void setCurrentPlayerMana(double newPlayerMana) { currPlayerMana_ = newPlayerMana; }
#pragma endregion
	//Para añadir objetos al inventario
	void addToInventory(Item* ob);
	//Para añadir objetos al alijo
	void addToStash(Item* ob);
	void addToShop(Item* ob);

	//tutorial
	void activeTutorial() { tutorial = true; }
	void desactiveTutorial() { tutorial = false; }
	bool onTutorial() { return tutorial; }

	//SettesNPC
	void nextPhaseVenancio() { venancioPhase++; }
	//GettersNPC
	int getVenancioPhase() { return venancioPhase; }
	//<summary>Método que resetea la zona segun en la isla que estés</summary>
	void resetIsland();
};