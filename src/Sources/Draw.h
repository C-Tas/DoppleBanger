﻿#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDL.h"
#include <iostream>



class Draw : public GameObject
{
protected:
	//Textura del objeto
	Texture* texture_ = nullptr;
	//Rect del render
	SDL_Rect destiny_ = { 0,0,0,0 };
	//El clip que se va a renderizar de la textura
	SDL_Rect frame_ = { 0,0,0,0 };
	//Pies de un objeto
	Vector2D visPos_{ 0,0 };
	//Numero de frames que tiene la animación
	int numberFrames_=0;
	//Constructora vacia de Draw
	Draw() {};
	//Constructora con argumentos de Draw
	Draw(Application* app, Point2D pos, Vector2D scale) : 
		GameObject(app, pos,scale) {
		initObject();
	};
	//Constructora por copia de Draw
	Draw(const Draw& other) : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};
	//Constructora por movimiento de Draw
	Draw(const Draw&& other)noexcept : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};
	//Destructora de Draw
	virtual ~Draw() {}; 
	
	//Inicializa destiny
	virtual void initObject() {
		destiny_.x = (int)pos_.getX();
		destiny_.y = (int)pos_.getY();
		destiny_.w = (int)scale_.getX();
		destiny_.h = (int)scale_.getY();
	};

public:
	//Para construir un background
	Draw(Application* app, Texture* texture) : 
		GameObject(app, Vector2D(0, 0), Vector2D(app->getWindowWidth(), app->getWindowHeight())),
		texture_(texture) {
		initObject();
	}
		
	//Para construir un texto
	Draw(Application* app, Texture* texture, SDL_Rect dest)
		:GameObject(app, Vector2D((double)dest.x, (double)dest.y), Vector2D((double)dest.w, (double)dest.h))
		, texture_(texture), destiny_(dest) {};

	//<metodo comun para renderizar tanto imagenes con un solo frame como con varios"
	const virtual void draw() {
		if (numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE);
		else  texture_->render(getDestiny(), frame_);
	};

	//<summary>cambia el frame </summary>
	virtual bool update() { return false; };
	//Cambia al siguiente frame
	virtual void updateFrame() { frame_.x = (frame_.x + frame_.w) % (numberFrames_*frame_.w); };
	//Devuelve la posicion "visual" del objeto
	//Cuando se mueva un objeto no se mira su posicion superior izquierda, sino sus pies.
	void updateVisPos() { visPos_.setVec(Vector2D(pos_.getX() + (scale_.getX() / 2), pos_.getY() + (scale_.getY() * 0.8))); }; //Actualiza la posicion visual del objeto

#pragma region getters
//Devuelve el rectangulo destino
	const virtual SDL_Rect getDestiny() {
		destiny_.x = (int)pos_.getX();
		destiny_.y = (int)pos_.getY();
		destiny_.w = (int)scale_.getX();
		destiny_.h = (int)scale_.getY();
		return destiny_;
	};
#pragma endregion

#pragma region setters
	void setFrame(SDL_Rect frame) { frame_ = frame; }; //Asigna el frame
	void setDestiny(SDL_Rect destiny) { destiny_ = destiny; }; //Asigna el rectangulo de destino
	void setTexture(Texture* texture) { texture_ = texture; }; //Asigna la textura
#pragma endregion
};
