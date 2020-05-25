#pragma once
#include "Application.h"
#include "Texture.h"
#include "Button.h"
#include "Vector2D.h"
#include "GameManager.h"
#include "GameState.h"

class TextBox {
protected:
	Application* app_ = nullptr;
	GameManager* gm_ = GameManager::instance();
	SDL_Rect dest; //Posici�n de la caja de texto, inicializada en init()
	const int lineSpacing = (int)round(GameManager::instance()->getFontSize() * 1.5);	//Interlineado y m�rgenes del texto

	Button* shopButton_ = nullptr;
	Button* button_ = nullptr;
	Button* tutorialButton_ = nullptr;
	Button* skipTutorial_ = nullptr;	
	Button* goToShipButton_ = nullptr;
	Button* goToNextZoneButton_ = nullptr;
	Button* unlockReward_ = nullptr;

	static void goShopState(Application* app);
	static void nextConversation(Application* app);
	static void skipTutorial(Application* app);
	static void nextTutorialVenancio(Application* app);
	static void goToShipState(Application* app);
	static void changeZone(Application* app);
	static void unlockCookerReward(Application* app);
	static void unlockMortyReward(Application* app);
	static void unlockNamiReward(Application* app);



public:
	///<summary>Constructora del textBox de di�logo</summary>
	TextBox(Application* app) : app_(app) { 
		dest.w = app_->getWindowWidth();
		dest.h = app_->getWindowHeight() / 4;
		dest.x = 0;
		dest.y = app_->getWindowHeight() - dest.h;

		shopButton_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::GoToShopButton), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 }, 
			Vector2D{ (double)(app_->getWindowWidth() / 7),  (double)(app_->getWindowHeight() / 20) }, goShopState);

		button_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::GoToNextZoneButton), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 7),  (double)(app_->getWindowHeight() / 20) }, nextConversation);

		tutorialButton_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::ButtonInitTutorial), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 4),  (double)(app_->getWindowHeight() / 20) }, nextTutorialVenancio);

		skipTutorial_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::ButtonSkipTutorial), Vector2D{ (double)lineSpacing + app->getWindowWidth() / 3, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 5),  (double)(app_->getWindowHeight() / 20) }, skipTutorial);
		
		goToShipButton_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::GoToShipButton), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 7),  (double)(app_->getWindowHeight() / 20) }, goToShipState);

		goToNextZoneButton_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::GoToNextZoneButton), Vector2D{ (double)6*(app_->getWindowWidth() / 7)-lineSpacing, dest.y + (double)lineSpacing * 5 },
			Vector2D{ (double)(app_->getWindowWidth() / 7),  (double)(app_->getWindowHeight() / 20) }, changeZone);

		unlockReward_ = new Button(app_, app_->getTextureManager()->getTexture(Resources::GoToNextZoneButton), Vector2D{ (double)lineSpacing, dest.y + (double)lineSpacing * 5 }, 
			Vector2D{ (double)(app_->getWindowWidth() / 7),  (double)(app_->getWindowHeight() / 20) },unlockCookerReward);
	};
	///<summary>Constructora del textBox de descripci�n</summary>
	TextBox(Application* app, Point2D pos) : app_(app) { initDescription(pos); };
	~TextBox() { delete shopButton_; delete button_; delete tutorialButton_; delete skipTutorial_; delete goToShipButton_; delete goToNextZoneButton_; delete unlockReward_; };

	///<summary>Carga el textBox de di�logo inicial</summary>
	void initDialog();
	bool updateButtons() { return goToShipButton_->update() || goToNextZoneButton_->update(); }

	///<summary>Carga el textBox de descripci�n inicial, se llama desde la constructora</summary>
	void initDescription(Point2D pos);
	///<summary>Crea el textBox para pasar de zona</summary>
	void passZoneDialog();


#pragma region Dialogos
	///<summary>Frases del viejo cuando se viaja a una isla nueva o se est� en el barco</summary>
	void dialogElderMan(int num);

	///<summary>Frase del comerciante</summary>
	void dialogMerchant(int dialog);

	///<summary>Frases del chef, tanto desbloqueado como no</summary>
	void dialogChef(bool unlock, int num);

	///<summary>Frases de Morty, tanto desbloqueado como no</summary>
	void dialogMorty(bool unlock, int num);

	///<summary>Frases del loro, se genera una al azar</summary>
	void dialogParrot();

	///<summary>Frases del esqueleto</summary>
	void dialogSkeleton(bool unlock);

	///<summary>Frases de la cart�grafa</summary>
	void dialogCartographer(bool unlock, int num = 0);

	///<summary>Frase del Kraken al empezar/acabar la batalla</summary>
	void dialogKraken(bool defeated);

	///<summary>Frases de Magordito al empezar/acabar la batalla</summary>
	void dialogMagordito(bool defeated);

	///<summary>Frases de Cleon al empezar/acabar la batalla</summary>
	void dialogCleon(bool defeated);
#pragma endregion

#pragma region Descripciones
	///<summary>Descripci�n de las armaduras caribe�as</summary>
	void armorCaribbean();
	///<summary>Descripci�n de las armaduras fantasmales</summary>
	void armorSpooky();

	///<summary>Descripci�n de los guantes caribe�os</summary>
	void glovesCaribbean();
	///<summary>Descripci�n de los guantes fantasmales</summary>
	void glovesSpooky();

	///<summary>Descripci�n de los calzados caribe�os</summary>
	void bootsCaribbean();
	///<summary>Descripci�n de los calzados fantasmales</summary>
	void bootsSpooky();

	///<summary>Descripci�n de las espadas caribe�as</summary>
	void swordCaribbean();
	///<summary>Descripci�n de las espadas fantasmales</summary>
	void swordSpooky();

	///<summary>Descripci�n de los sables caribe�os</summary>
	void saberCaribbean();
	///<summary>Descripci�n de los sables fantasmales</summary>
	void saberSpooky();

	///<summary>Descripci�n de las pistolas caribe�as</summary>
	void pistolCaribbean();
	///<summary>Descripci�n de las pistolas fantasmales</summary>
	void pistolSpooky();

	///<summary>Descripci�n de los trabucos caribe�os</summary>
	void blunderbussCaribbean();
	///<summary>Descripci�n de los trabucos fantasmales</summary>
	void blunderbussSpooky();

	///<summary>Descripci�n de la poci�n de vida</summary>
	void lifePotion();
	///<summary>Descripci�n de la poci�n de man�</summary>
	void manaPotion();
	///<summary>Descripci�n de la poci�n de velocidad</summary>
	void velocityPotion();
	///<summary>Descripci�n de la poci�n de da�o</summary>
	void damagePotion();
	///<summary>Descripci�n de la poci�n de defensa</summary>
	void defensePotion();
	///<summary>Descripci�n de la poci�n de cr�tico</summary>
	void criticPotion();
#pragma endregion

#pragma region SkillsDescription
	///<summary>Descripci�n de la habilidad de invocar al clon</summary>
	void Clon();
	///<summary>Descripci�n de la habilidad LiberacionI del clon</summary>
	void LiberationI();
	///<summary>Descripci�n de la habilidad LiberacionII del clon</summary>
	void LiberationII();
	///<summary>Descripci�n de la habilidad Explosion del clon</summary>
	void Explosion();
	///<summary>Descripci�n de la habilidad Golpe Fuerte de la rama a melee</summary>
	void GolpeFuerte();
	///<summary>Descripci�n de la habilidad Invencible de la rama a melee</summary>
	void Invencible();
	///<summary>Descripci�n de la habilidad Torbellino de la rama a melee</summary>
	void Torbellino();
	///<summary>Descripci�n de la habilidad Raudo del disparo a distancia</summary>
	void Raudo();
	///<summary>Descripci�n de la habilidad Rebote del disparo a distancia</summary>
	void Rebote();
	///<summary>Descripci�n de la habilidad Perforador del disparo a distancia</summary>
	void Perforador();
#pragma endregion
};