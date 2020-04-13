#pragma once
#include "GameState.h"
#include "SkillButton.h"
#include <array>

class Skill;
class Player;


class SkillState :
	public GameState
{
private:
	Draw* bg_ = nullptr;
	Draw* emptyBars_ [3] = { nullptr, nullptr, nullptr };	//Los marcos de las barras
	Draw* bars_ [3] = { nullptr, nullptr, nullptr };		//El relleno de las Barras
	Button* goToInventary_ = nullptr;
	Texture* totalPoints_ = nullptr;		//Puntos totales de hazaña
	list <SkillButton*> skillsIcons_;	//Botones que contienen las skills en si mismas
	array <list<SkillButton*>::iterator, 3> skillsTypeIterator;		//array auxiliar para cuando se cambian las texturas 
																	//al desbloquear las habilidades

	//<summary>Textura que contiene la �ltima descripcion de la �ltima skill sobre
	//la que se ha posicionado el cursor</summary>

	SkillName lastPointed = SkillName::Unequipped;

	virtual void update();
	///<summary>Puntero a player (para actualizar las skills que tiene equipadas)</summary>
	Player* player_ = nullptr;
	//<summary>Puntero a la skill seleccionada<summary>
	SkillButton* selected_ = nullptr;
	//<summary>Si hay alg�n objeto seleccionado, se pintar� debajo de este un recuadro para mostrar la seleccion</summary>
	Draw* selectedRectangle = nullptr;
	//<summary>Lugar donde se van a pintar las descripciones</summary>
	SDL_Rect descriptionRect = { 890,350,450,40 };

	///<summary>Vector con los rects de donde se pintaran las texturas de las habilidades cuando sean equipadas en los botones<summary>
	const vector<SDL_Rect> assignButtons = { { 960,728, 68, 39 }, { 1087,728, 68,39} ,{ 1214, 728, 68, 39 }, {1341,728,68, 39} };

protected:
	///<summary>Se inicializa el skill state</summary>
	virtual void initState();

	///<summary>Crea los 4 botones necesarios del skill state</summary>
	void createButtons();

	///<summary>Crea las 3 barras de las ramas</summary>
	void createBars();
	///<summary>Actualiza el relleno de la barra</summary>
	void updateBars();

	///<summary>Crea los iconos de las skills (botones)</summary>
	void createSkillsIcons();
	///<summary>Actualiza los iconos de las skills (los que est�n equipados)</summary>
	void renderSkillsEquipped()const;

	///<summary>Crea la textura con el texto de los puntos totales. Hay que borrar y crear una nueva cada
	///vez que se modifica el valor de los puntos totales</summary>
	void createTexts();

	///<summary>M�todo para seleccionar un boton</summary>
	void setSelectedSkillButton(SkillButton* button);
	///<summary>M�todo auxiliar para el callback de equipar la skill a las teclas
	///0->q, 1->w, 2->e </summary>
	void equipSelectedSkill(Key key);

	///<summary>M�todos auxiliares para el feedback visual</summary>
	void meleePointsActualized();
	void distancePointsActualized();
	void ghostPointsActualized();

	///<summary>M�todo auxiliar que cambia de texturas cuando las habilidades se desbloquean
	///Se llama desde melee/distance/ghostPointsActualized</summary>
	void auxPointsActualized(list<SkillButton*>::iterator aux, Texture* t1,  Texture* t2,  Texture* t3, int points);

	///M�todo que, dado el nombre de la skill, devuelve su icono correspondiente
	///Se usa al pintar las skills que est�n equipadas
	Texture* getTextureFromSkill(SkillName name)const;

	///Redefinici�n del m�todo draw para dibujar las cosas en un orden espec�fico
	virtual void draw()const;

	void changeDescriptionTexture(SkillName name)const;
	void changeDescription(SkillName name);

	///M�todo para cuando se vaya a destruir el estado, se actualice las skills que tiene equipadas el player
	void setPlayerSkills();
	//<summary>M�todo que dado el nombre de una skill crea un objeto Skill* correspondiente
	///FALTA IMPLEMENTAR LOS OBJETOS QUE HEREDEN DE SKILL, PERO LA ESTRUCTURA EST�</summary>
	Skill* createSkill(SkillName name);
public:
	///<summary>Constructora de CreditsState</summary>
	SkillState(Application* app = nullptr, Player* player = nullptr) :GameState(app), player_(player) { initState(); };
	///<summary>Destructora</summary>
	virtual ~SkillState();

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
	///<summary>Asigna como objeto seleccionado el boton sobre el que se hace click</summary>
	static void selectSkill(Application* app, SkillButton* button);
	///<summary>Asigna el elemento seleccionado a la tecla Q</summary>
	static void assingToQKey(Application* app);
	///<summary>Asigna el elemento seleccionado a la tecla W</summary>
	static void assingToWKey(Application* app);
	///<summary>Asigna el elemento seleccionado a la tecla E</summary>
	static void assingToEKey(Application* app);
	///<summary>M�todo para modificar la descripcion que aparece en pantalla</summary>
	static void changeDescription(Application* app, SkillName name);

};

