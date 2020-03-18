#pragma once
#include "GameState.h"

class SkillState :
	public GameState
{
protected:
	///<summary>Se inicializa el skill state</summary>
	void initSkillState();
	///<summary>crea los 4 botones necesarios del skill state</summary>
	void createButtons();

public:
	int rama1 = 0;
	int rama2 = 0;
	int rama3 = 0;
	int puntos = 500;

	///<summary>Constructora de CreditsState</summary>
	SkillState(Application* app = nullptr) :GameState(app) { initSkillState(); };
	///<summary>Destructora</summary>
	virtual ~SkillState() {};

	///<summary>Metodo para pasar a los botones de este estado, vuelve al anterior</summary>
	static void backToPreviousState(Application* app);
	///<summary>Aumenta los punto invertidos en la rama 1</summary>
	static void increaseBranch1(Application* app);
	///<summary>Aumenta los punto invertidos en la rama 2</summary>
	static void increaseBranch2(Application* app);
	///<summary>Aumenta los punto invertidos en la rama 3</summary>
	static void increaseBranch3(Application* app);
};

