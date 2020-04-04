#pragma once
#include "GameState.h"
#include "SkillButton.h"

enum class Keys :int { Q, W, E };

class SkillState :
	public GameState
{
private:
	Draw* bg_ = nullptr;
	Draw* emptyBars_ [3] = { nullptr, nullptr, nullptr };	//Los marcos de las barras
	Draw* bars_ [3] = { nullptr, nullptr, nullptr };		//El relleno de las Barras
	Draw* totalPoints_ = nullptr;		//Puntos totales de hazaña
	SkillButton* skillsIcons_[3][3] = { { nullptr, nullptr, nullptr } ,{ nullptr, nullptr, nullptr } ,{ nullptr, nullptr, nullptr } };
	//He puesto todo iniciado a nullptr porque lo he visto así en otros sitios, aunque no lo veo necesario

	virtual void update();
	Player* player_ = nullptr;
	SkillButton* selected_ = nullptr;

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
	///<summary>Método para seleccionar un boton</summary>
	void setSelectedSkillButton(SkillButton* button);
	///<summary>Método auxiliar para el callback de equipar la skill a las teclas</summary>
	///0->q, 1->w, 2->e
	void equipSelectedSkill(Keys key);

public:
	///<summary>Constructora de CreditsState</summary>
	SkillState(Application* app = nullptr) :GameState(app) { initSkillState(); };
	///<summary>Destructora</summary>
	virtual ~SkillState() {};

	///<summary>Metodo para pasar a los botones de este estado, vuelve al anterior</summary>
	static void backToPreviousState(Application* app);
	///<summary>Metodo para pasar InventoryState</summary>
	static void goToInventaryState(Application* app);
	///<summary>Invierte un punto de hazaña en la rama Precision</summary>
	static void increasePrecisionBranch(Application* app);
	///<summary>Invierte un punto de hazaña en la rama Melee</summary>
	static void increaseMeleeBranch(Application* app);
	///<summary>Invierte un punto de hazaña en la rama Ghost</summary>
	static void increaseGhostBranch(Application* app);
	///<summary>Asigna como objeto seleccionado el boton sobre el que se hace click</summary>
	static void selectSkill(Application* app, SkillButton* button);
};

