#pragma once
#include "Application.h"
#include "Texture.h"
#include "Vector2D.h"

class TextBox {
protected:
	Application* app_ = nullptr;
	SDL_Rect dest; //Posici�n de la caja de texto, inicializada en init()
	const int lineSpacing = 30;	//Interlineado y m�rgenes del texto

public:
	///<summary>Constructora del textBox de di�logo</summary>
	TextBox(Application* app) : app_(app) {};
	///<summary>Constructora del textBox de descripci�n</summary>
	TextBox(Application* app, Point2D pos) : app_(app) { initDescription(pos); };
	~TextBox() {};

	///<summary>Carga el textBox de di�logo inicial</summary>
	void initDialog();

	///<summary>Carga el textBox de descripci�n inicial, se llama desde la constructora</summary>
	void initDescription(Point2D pos);

#pragma region Di�logos
	///<summary>Frases del viejo cuando se viaja a una isla nueva o se est� en el barco</summary>
	void dialogElderMan(int isle = -1);

	///<summary>Frase del comerciante</summary>
	void dialogMerchant();

	///<summary>Frases del chef, tanto desbloqueado como no</summary>
	void dialogChef(bool unlock);

	///<summary>Frases de Morty, tanto desbloqueado como no</summary>
	void dialogMorty(bool unlock);

	///<summary>Frases del loro, se genera una al azar</summary>
	void dialogParrot();

	///<summary>Frases del esqueleto</summary>
	void dialogSkeleton(bool unlock);

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