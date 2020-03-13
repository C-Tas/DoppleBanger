#pragma once
#include "Application.h"
#include "Texture.h"

class TextBoxManager {
protected:
	Application* app_ = nullptr;
	SDL_Rect dest; //Posición de la caja de texto, inicializada en init()
	const int lineSpacing = 30;	//Interlineado y márgenes del texto

public:
	TextBoxManager(Application* app) : app_(app) { init(); };
	~TextBoxManager() {};

	///<summary>Carga el textBox inicial, se llama desde la constructora</summary>
	void init();

	///<summary>Frases del viejo cuando se viaja a una isla nueva o se está en el barco</summary>
	void dialogElderMan(int isle = -1);

	///<summary>Frase del comerciante</summary>
	void dialogMerchant();

	///<summary>Frases del chef, tanto desbloqueado como no</summary>
	void dialogChef(bool unlock);

	///<summary>Frases de Morty, tanto desbloqueado como no</summary>
	void dialogMorty(bool unlock);

	///<summary>Frases del loro, se genera una al azar</summary>
	void dialogParrot();

	///<summary>Frase del Kraken al empezar/acabar la batalla</summary>
	void dialogKraken(bool defeated);

	///<summary>Frases de Magordito al empezar/acabar la batalla</summary>
	void dialogMagordito(bool defeated);

	///<summary>Frases de Cleon al empezar/acabar la batalla</summary>
	void dialogCleon(bool defeated);
};