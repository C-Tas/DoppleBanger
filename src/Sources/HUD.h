#pragma once
#include "Draw.h"
#include <list>

class HUD : public Draw
{
public:
	HUD(Application* app) : Draw(app, { 0,0 }, { 0,0 }) { initObject(); };
	~HUD();

	const virtual void draw();
	virtual bool update();
	//Estos dos métodos tienen que ser llamados sólo una vez, por lo que se llaman
	//desde GameManager al configurar las teclas en el inventario o en el skillState
	//Actualiza la textura asignada a la tecla
	void updateSkillKey(int key);
	//Actualiza la textura asignada a la tecla
	void updateObjectKey(int key);

private:
	list<Draw*> elementsHUD_;	//Lista de los elementos del HUD
	GameManager* gm_ = nullptr; //GameManager
	#pragma region Iconos
	const int ICON_AMOUNT = 6;
	//Contiene todos los iconos
	vector<Texture*> icons;
	//Tamaño de los iconos
	const int W_H_ICON = app_->getWindowHeight() / 16;
	//Separación entre cada icono
	const int DISTANCE_BTW_ICON = app_->getWindowWidth() / 17.15;
	Texture* q_ = nullptr;			//Tecla asignada a la habilidad
	Texture* w_ = nullptr;			//Tecla asignada a la habilidad
	Texture* e_ = nullptr;			//Tecla asignada a la habilidad
	Texture* r_ = nullptr;			//Tecla asignada a la habilidad
	Texture* one_ = nullptr;		//Tecla asignada al objeto
	Texture* two_ = nullptr;		//Tecla asignada al objeto
	#pragma endregion
	#pragma region Constantes
	//Timon
	const uint W_WHEEL = app_->getWindowWidth() * 3 / 19;
	const uint H_WHEEL = W_WHEEL;

	//Cuerda
	const uint W_ROPE = app_->getWindowWidth() * 7 / 8;
	const uint H_ROPE = app_->getWindowHeight() * 2 / 9;

	//Skills
	const uint W_SKILLS = app_->getWindowWidth() * 5 / 13;
	const uint H_SKILLS = app_->getWindowHeight() / 10;
	#pragma endregion

	int endLife = 270;
	//Inicializa el objeto
	virtual void initObject();
	//Crea el fondo del HUD
	void createBg(Texture* tx, const SDL_Rect& destRect);
	//Crea las texturas para las habilidades
	Texture* createSkillIcon(int key);
	//Crea las texturas para los objetos
	Texture* createObjectIcon(int key);
};

