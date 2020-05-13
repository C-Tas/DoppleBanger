#pragma once
#include "Application.h"
#include "Texture.h"
#include "Button.h"
#include "Vector2D.h"
#include "GameManager.h"

class TextBox {
protected:
	Application* app_ = nullptr;
	GameManager* gm_ = GameManager::instance();
	SDL_Rect dest; //Posición de la caja de texto, inicializada en init()
	const int lineSpacing = GameManager::instance()->getFontSize() * 1.5;	//Interlineado y márgenes del texto

	Button* shopButton_ = nullptr;
	Button* button_ = nullptr;
	Button* tutorialButton_ = nullptr;
	Button* skipTutorial_ = nullptr;

	static void goShopState(Application* app);
	static void nextConversation(Application* app);
	static void skipTutorial(Application* app);
	static void nextTutorialVenancio(Application* app);


public:
	///<summary>Constructora del textBox de diálogo</summary>
	TextBox(Application* app) : app_(app) { 
		dest.w = app_->getWindowWidth();
		dest.h = app_->getWindowHeight() / 4;
		dest.x = 0;
		dest.y = app_->getWindowHeight() - dest.h;

		shopButton_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::GoToShopButton), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 }, 
			Vector2D{ (double)(app_->getWindowWidth() / 7),  (double)(app_->getWindowHeight() / 20) }, goShopState);

		button_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::RightArrow), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 17),  (double)(app_->getWindowHeight() / 20) }, nextConversation);

		tutorialButton_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::ButtonInitTutorial), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 4),  (double)(app_->getWindowHeight() / 20) }, nextTutorialVenancio);

		skipTutorial_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::ButtonSkipTutorial), Vector2D{ (double)lineSpacing + app->getWindowWidth() / 3, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 5),  (double)(app_->getWindowHeight() / 20) }, skipTutorial);
	};
	///<summary>Constructora del textBox de descripción</summary>
	TextBox(Application* app, Point2D pos) : app_(app) { initDescription(pos); };
	~TextBox() { delete shopButton_; delete button_; delete tutorialButton_; delete skipTutorial_; };

	///<summary>Carga el textBox de diálogo inicial</summary>
	void initDialog();

	///<summary>Carga el textBox de descripción inicial, se llama desde la constructora</summary>
	void initDescription(Point2D pos);

#pragma region Diálogos
	///<summary>Frases del viejo cuando se viaja a una isla nueva o se está en el barco</summary>
	void dialogElderMan(int num);

	///<summary>Frase del comerciante</summary>
	void dialogMerchant();

	///<summary>Frases del chef, tanto desbloqueado como no</summary>
	void dialogChef(bool unlock, int num);

	///<summary>Frases de Morty, tanto desbloqueado como no</summary>
	void dialogMorty(bool unlock, int num);

	///<summary>Frases del loro, se genera una al azar</summary>
	void dialogParrot();

	///<summary>Frases del esqueleto</summary>
	void dialogSkeleton(bool unlock);

	///<summary>Frases de la cartógrafa</summary>
	void dialogCartographer(bool unlock, int num = 0);

	///<summary>Frase del Kraken al empezar/acabar la batalla</summary>
	void dialogKraken(bool defeated);

	///<summary>Frases de Magordito al empezar/acabar la batalla</summary>
	void dialogMagordito(bool defeated);

	///<summary>Frases de Cleon al empezar/acabar la batalla</summary>
	void dialogCleon(bool defeated);
#pragma endregion

#pragma region Descripciones
	///<summary>Descripción de las armaduras caribeñas</summary>
	void armorCaribbean();
	///<summary>Descripción de las armaduras fantasmales</summary>
	void armorSpooky();

	///<summary>Descripción de los guantes caribeños</summary>
	void glovesCaribbean();
	///<summary>Descripción de los guantes fantasmales</summary>
	void glovesSpooky();

	///<summary>Descripción de los calzados caribeños</summary>
	void bootsCaribbean();
	///<summary>Descripción de los calzados fantasmales</summary>
	void bootsSpooky();

	///<summary>Descripción de las espadas caribeñas</summary>
	void swordCaribbean();
	///<summary>Descripción de las espadas fantasmales</summary>
	void swordSpooky();

	///<summary>Descripción de los sables caribeños</summary>
	void saberCaribbean();
	///<summary>Descripción de los sables fantasmales</summary>
	void saberSpooky();

	///<summary>Descripción de las pistolas caribeñas</summary>
	void pistolCaribbean();
	///<summary>Descripción de las pistolas fantasmales</summary>
	void pistolSpooky();

	///<summary>Descripción de los trabucos caribeños</summary>
	void blunderbussCaribbean();
	///<summary>Descripción de los trabucos fantasmales</summary>
	void blunderbussSpooky();

	///<summary>Descripción de la poción de vida</summary>
	void lifePotion();
	///<summary>Descripción de la poción de maná</summary>
	void manaPotion();
	///<summary>Descripción de la poción de velocidad</summary>
	void velocityPotion();
	///<summary>Descripción de la poción de daño</summary>
	void damagePotion();
	///<summary>Descripción de la poción de defensa</summary>
	void defensePotion();
	///<summary>Descripción de la poción de crítico</summary>
	void criticPotion();
#pragma endregion

#pragma region SkillsDescription
	///<summary>Descripción de la habilidad de invocar al clon</summary>
	void Clon();
	///<summary>Descripción de la habilidad LiberacionI del clon</summary>
	void LiberationI();
	///<summary>Descripción de la habilidad LiberacionII del clon</summary>
	void LiberationII();
	///<summary>Descripción de la habilidad Explosion del clon</summary>
	void Explosion();
	///<summary>Descripción de la habilidad Golpe Fuerte de la rama a melee</summary>
	void GolpeFuerte();
	///<summary>Descripción de la habilidad Invencible de la rama a melee</summary>
	void Invencible();
	///<summary>Descripción de la habilidad Torbellino de la rama a melee</summary>
	void Torbellino();
	///<summary>Descripción de la habilidad Raudo del disparo a distancia</summary>
	void Raudo();
	///<summary>Descripción de la habilidad Rebote del disparo a distancia</summary>
	void Rebote();
	///<summary>Descripción de la habilidad Perforador del disparo a distancia</summary>
	void Perforador();
#pragma endregion
};