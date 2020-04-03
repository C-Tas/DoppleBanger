#pragma once
#include "Draw.h"
#include <list>

class HUD : public Draw
{
public:
	HUD(Application* app) : Draw(app, { 0,0 }, { 0,0 }) { initObject(); };
	~HUD();

	const virtual void draw();
	virtual bool update() { return false; };

private:
	list<Draw*> elementsHUD_; //Lista de los elementos del HUD
	Draw* wheel_ = nullptr; //Timon
	Draw* rope_ = nullptr; //Cuerda
	Draw* skills_ = nullptr; //Skills y objetos

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

	//Inicializa el objeto
	virtual void initObject();
};

