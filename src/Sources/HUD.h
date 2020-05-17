#pragma once
#include <list>
#include "VisualElement.h"

class Player;

struct potionHUD
{
	bool active_ = false;
	double duration_;
	double lastTick_;
	double currentTick_;
	VisualElement* potionBackground_;
	VisualElement* potionHUD_;
	Texture* potionTimeHUD_;
};

class HUD : public Draw
{
public:
	HUD(Application* app) : Draw(app, { 0,0 }, { 0,0 }) { initObject(); };
	~HUD();

	const virtual void draw();
	virtual bool update();
	//Estos dos m�todos tienen que ser llamados s�lo una vez, por lo que se llaman
	//desde GameManager al configurar las teclas en el inventario o en el skillState
	//Actualiza la textura asignada a la tecla
	void updateKey(int key);
	//Actualiza el estado del cooldown
	void setSkillCooldown(bool cooldown, int key);
	//Crea el HUD de los objetos consumidos
	void showPotionHUD(int index, double duration, double time);
	//Método para settear al player
	void setPlayerInHUD(Player* player) { player_ = player; };
private:
	list<VisualElement*> elementsHUD_;	//Lista de los elementos del HUD
	vector<potionHUD> potionsHUD_;		//Lista de las pociones del HUD | 0 vel, 1 def, 2 da�, 3 crit
	GameManager* gm_ = nullptr; //GameManager
	Player* player_ = nullptr;
	#pragma region Iconos
	//Contiene todos los iconos
	vector<Texture*> icons;

	Texture* cdBg_ = nullptr;		//Background del cooldown
	vector<bool> cdKeys;			//Vector del estado del cooldown de las habilidades
	SDL_Rect cdRect_;				//Rect del cooldown
	#pragma endregion

	#pragma region Vida y mana
	Texture* life_ = nullptr;		//Textura de la vida
	int Mana = 0;
	SDL_Rect clipLife_;				//Contenido de vida
	Sint16 xMana_ = 0;				//Coordenada x del centro de la circunferencia
	Sint16 yMana_ = 0;				//Coordenada y del centro de la circunferencia
	Sint16 endMana_ = 270;			//Punto donde termina de pintar la circunferencia
	double propLife_ = 1.0;			//Proporci�n de vida
	double propMana_ = 1.0;			//Proporci�n del man�
	double currentLife_ = 0.0;		//Vida actual
	double currentMana_ = 0.0;		//Man� actual
	double maxLife_ = 0.0;			//Vida m�xima
	double maxMana_ = 0.0;			//Man� m�ximo
	#pragma endregion
	
	#pragma region Constantes
	const int ICON_AMOUNT = 6;
	const int POTIONS_AMOUNT = 4;
	//Tama�o de los iconos
	const int W_H_ICON = app_->getWindowHeight() / 16;
	//Separaci�n entre cada icono
	const int DISTANCE_BTW_ICON = app_->getWindowWidth() / 17.15;

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
	const uint W_H_LIFE = app_->getWindowHeight() * 2 / 15;
	const Sint16 START_MANA = 90;			//Punto donde empieza a pintar la circunferencia
	const Sint16 MAX_DEGREES_MANA = 180;	//Grados m�ximos del arco de man�
	#pragma endregion

	//Inicializa el objeto
	virtual void initObject();
	//Crea el fondo del HUD
	void createBg(Texture* tx, const SDL_Rect& destRect);
	//Crea las texturas para las habilidades
	Texture* createSkillIcon(int key);
	//Crea las texturas para las el HUD de las pociones
	potionHUD createPotionHUD(int key);
	//Crea las texturas para los objetos
	Texture* createObjectIcon(int key);
};