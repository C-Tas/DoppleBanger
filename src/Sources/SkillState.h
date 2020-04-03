#pragma once
#include "GameState.h"

class SkillState :
	public GameState
{
private:
	Draw* bg_ = nullptr;
	Draw* emptyBars_ [3] = { nullptr, nullptr, nullptr };	//Los marcos de las barras
	Draw* bars_ [3] = { nullptr, nullptr, nullptr };		//El relleno de las Barras
	Draw* totalPoints_ = nullptr;		//Puntos totales de haza�a
	Draw* skillsIcons_[3][3] = { { nullptr, nullptr, nullptr } ,{ nullptr, nullptr, nullptr } ,{ nullptr, nullptr, nullptr } };
	//He puesto todo iniciado a nullptr porque lo he visto as� en otros sitios, aunque no lo veo necesario

	virtual void update();

protected:
	///<summary>Se inicializa el skill state</summary>
	void initSkillState();

	///<summary>Crea los 4 botones necesarios del skill state</summary>
	void createButtons();

	///<summary>Crea las 3 barras de las ramas</summary>
	void createBars();
	///<summary>Actualiza el relleno de la barra</summary>
	void updateBars();

	///<summary>Crea los iconos de las skills</summary>
	void createSkillsIcons();
	///<summary>Actualiza los iconos de las skills</summary>
	void updateSkillsIcons();

	///<summary>Crea el texto de los puntos totales</summary>
	void createTexts();
	///<summary>Actualiza los textossummary>
	void updateTexts();

public:
	///<summary>Constructora de CreditsState</summary>
	SkillState(Application* app = nullptr) :GameState(app) { initSkillState(); };
	///<summary>Destructora</summary>
	virtual ~SkillState() {};

	///<summary>Metodo para pasar a los botones de este estado, vuelve al anterior</summary>
	static void backToPreviousState(Application* app);
	///<summary>Metodo para pasar InventoryState</summary>
	static void goToInventaryState(Application* app);
	///<summary>Invierte un punto de haza�a en la rama Precision</summary>
	static void increasePrecisionBranch(Application* app);
	///<summary>Invierte un punto de haza�a en la rama Melee</summary>
	static void increaseMeleeBranch(Application* app);
	///<summary>Invierte un punto de haza�a en la rama Ghost</summary>
	static void increaseGhostBranch(Application* app);
};

