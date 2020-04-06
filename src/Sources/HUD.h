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
	//Actualiza el estado del cooldown
	void setSkillCooldown(bool cooldown, int key);

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
	Texture* cdBg_ = nullptr;		//Background del cooldown
	vector<bool> cdKeys;			//Vector del estado del cooldown de las habilidades
	#pragma endregion

	#pragma region Vida y mana
	Texture* life_ = nullptr;		//Textura de la vida
	SDL_Rect clipLife_;				//Contenido de vida
	Sint16 xMana_ = 0;				//Coordenada x del centro de la circunferencia
	Sint16 yMana_ = 0;				//Coordenada y del centro de la circunferencia
	Sint16 endMana_ = 270;			//Punto donde termina de pintar la circunferencia
	double propLife_ = 1.0;			//Proporción de vida
	double propMana_ = 1.0;			//Proporción del maná
	double currentLife_ = 0.0;		//Vida actual
	double currentMana_ = 0.0;		//Maná actual
	double maxLife_ = 0.0;			//Vida máxima
	double maxMana_ = 0.0;			//Maná máximo
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

	//Vida
	const uint W_H_LIFE = app_->getWindowHeight() / 7;
	const Sint16 START_MANA = 90;			//Punto donde empieza a pintar la circunferencia
	const Sint16 MAX_DEGREES_MANA = 180;	//Grados máximos del arco de maná
	#pragma endregion

	//Inicializa el objeto
	virtual void initObject();
	//Crea el fondo del HUD
	void createBg(Texture* tx, const SDL_Rect& destRect);
	//Crea las texturas para las habilidades
	Texture* createSkillIcon(int key);
	//Crea las texturas para los objetos
	Texture* createObjectIcon(int key);
};