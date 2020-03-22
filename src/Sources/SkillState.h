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
	///<summary>Constructora de CreditsState</summary>
	SkillState(Application* app = nullptr) :GameState(app) { initSkillState(); };
	///<summary>Destructora</summary>
	virtual ~SkillState() {};

	///<summary>Metodo para pasar a los botones de este estado, vuelve al anterior</summary>
	static void backToPreviousState(Application* app);
	///<summary>Invierte un punto de hazaña en la rama Precision</summary>
	static void increasePrecisionBranch(Application* app);
	///<summary>Invierte un punto de hazaña en la rama Melee</summary>
	static void increaseMeleeBranch(Application* app);
	///<summary>Invierte un punto de hazaña en la rama Ghost</summary>
	static void increaseGhostBranch(Application* app);
};

