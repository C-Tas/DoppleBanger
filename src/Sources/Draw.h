﻿#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDL.h"


class Draw : public GameObject
{
protected:
	Texture* texture_;
	SDL_Rect destiny_;
	SDL_Rect frame_;

	Draw() : texture_(nullptr), frame_({ 0,0,0,0 }), destiny_({0,0,0,0}) {}; //Constructora vacia de Draw

	Draw(Application* app, Texture* texture, Point2D pos, Vector2D scale) : //Constructora con argumentos de Draw
		GameObject(app, pos, scale), texture_(texture) {
		destiny_.x = (int)pos.getX();
		destiny_.y = (int)pos.getY();
		destiny_.w = (int)scale.getX();
		destiny_.h = (int)scale.getY();
		frame_ = { 0,0,0,0 };
	};

	Draw(Application* app, Texture* texture, SDL_Rect frame, Point2D pos, Vector2D scale) : //Constructora por Frame y argumentos de Draw 
		GameObject(app, pos, scale), texture_(texture) {
		destiny_.x = (int)pos.getX();
		destiny_.y = (int)pos.getY();
		destiny_.w = (int)scale.getX();
		destiny_.h = (int)scale.getY();
		frame_ = frame;
	};

	Draw(const Draw& other) : GameObject(other.app_, other.pos_, other.scale_), 
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {}; //Constructora por copia de Draw

	Draw(const Draw&& other)noexcept : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {}; //Constructora por movimiento de Draw

	virtual ~Draw() {}; //Destructora de Draw

public:
	const virtual void draw() { texture_->render(getDestiny(), SDL_FLIP_NONE); };

#pragma region getters
	//Devuelve una posición con el offset del sprite aplicado
	//Sirve para encontrar en centro en relación a un objeto
	Vector2D getCenter(Vector2D pos)
	{
		Vector2D center;
		center.setX(pos.getX() - (scale_.getX() / 2));
		center.setY(pos.getY() - (scale_.getY() / 2));
		return center;
	}
	//Devuelve "la posición visual" del sprite
	//Vease: cuando se mueve el jugador este mueve "sus pies" a esa posición
	Vector2D getVisPos(Vector2D pos)
	{
		Vector2D vis;
		vis.setX(pos.getX() - (scale_.getX() / 2));
		vis.setY(pos.getY() - (scale_.getY() * 0.8));
		return vis;
	}
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
