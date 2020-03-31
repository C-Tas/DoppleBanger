#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDL.h"
#include <iostream>



class Draw : public GameObject
{
protected:
	Texture* texture_;
	SDL_Rect destiny_;
	SDL_Rect frame_;
	Vector2D visPos_;
	int numberFrames_=0;

	Draw() : texture_(nullptr), frame_({ 0,0,0,0 }), destiny_({0,0,0,0}) {}; //Constructora vacia de Draw

	Draw(Application* app, Texture* texture, Point2D pos, Vector2D scale, SDL_Rect frame = { 0,0,0,0},int numberFrames=0) : //Constructora con argumentos de Draw
		GameObject(app, pos, scale), texture_(texture),frame_(frame),numberFrames_(numberFrames) {
		destiny_.x = (int)pos.getX();
		destiny_.y = (int)pos.getY();
		destiny_.w = (int)scale.getX();
		destiny_.h = (int)scale.getY();
	};

	//Draw(Application* app, Texture* texture, SDL_Rect frame, Point2D pos, Vector2D scale) : //Constructora por Frame y argumentos de Draw 
	//	GameObject(app, pos, scale), texture_(texture) {
	//	destiny_.x = (int)pos.getX();
	//	destiny_.y = (int)pos.getY();
	//	destiny_.w = (int)scale.getX();
	//	destiny_.h = (int)scale.getY();
	//	frame_ = frame;
	//};

	Draw(const Draw& other) : GameObject(other.app_, other.pos_, other.scale_), 
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {}; //Constructora por copia de Draw

	Draw(const Draw&& other)noexcept : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {}; //Constructora por movimiento de Draw

public:
	virtual ~Draw() {}; //Destructora de Draw

public:
	//Para construir un background
	Draw(Application* app, Texture* texture) : GameObject(app, Vector2D(0, 0),
		Vector2D(app->getWindowWidth(), app->getWindowHeight()))
		, texture_(texture) {
		frame_ = SDL_Rect({ 0, 0, (int)scale_.getX(), (int)scale_.getY() });
		destiny_ = SDL_Rect({ 0,0,0,0 });
	};
	//Para construir un texto
	Draw(Application* app, Texture* texture, SDL_Rect dest)
		:GameObject(app, Vector2D({ (double)dest.x, (double)dest.y }), 
			Vector2D({ (double)dest.w,(double)dest.h })), texture_(texture) {
		destiny_ = SDL_Rect({ 0,0,0,0 });
		frame_ = SDL_Rect({ 0, 0, (int)scale_.getX(), (int)scale_.getY() });
	};

	//<metodo comun para renderizar tanto imagenes con un solo frame como con varios"
	const virtual void draw() {
		if (numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE); else {
			texture_->render(getDestiny(), frame_); }};
	//<summary>cambia el frame </summary>
	virtual bool update() { return false; };
	virtual void updateFrame() { frame_.x = (frame_.x + frame_.w) % (numberFrames_*frame_.w); };
	//Devuelve la posicion "visual" del objeto
	//Cuando se mueva un objeto no se mira su posicion superior izquierda, sino sus pies.
	void updateVisPos() { visPos_.setVec(Vector2D(pos_.getX() + (scale_.getX() / 2), pos_.getY() + (scale_.getY() * 0.8))); }; //Actualiza la posicion visual del objeto

#pragma region getters
	//Dada una posición le resta el offset del objeto que invoca el método
	//de tal forma que si este se mueve a la dicha posición queda centrado en ella
	Vector2D getCenter(Vector2D pos)
	{
		Vector2D center;
		center.setX(pos.getX() - (scale_.getX() / 2));
		center.setY(pos.getY() - (scale_.getY() / 2));
		return center;
	}
	//Dada una posición le resta el offset del objeto que invoca el método
	//de tal forma que si este se mueve a la dicha posición queda con "los pies" colocados en ella
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
	Point2D getVisPos() { return visPos_; };
#pragma endregion


#pragma region setters
	void setFrame(SDL_Rect frame) { frame_ = frame; }; //Asigna el frame
	void setDestiny(SDL_Rect destiny) { destiny_ = destiny; }; //Asigna el rectangulo de destino
	void setTexture(Texture* texture) { texture_ = texture; }; //Asigna la textura
#pragma endregion
};
