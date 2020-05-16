#pragma once
#include "GameObject.h"
#include <iostream>
#include "Camera.h"

class Draw : public GameObject
{
protected:
	struct Anim
	{
		int numberFrames_;		// Número de frames totales
		int widthFrame_;		// Ancho del frame
		int heightFrame_;		// Alto del frame
		int frameRate_;			// Velocidad a la que se cambia de frames
		int currFrame_ = 0;		// Frame actual
		bool loop_;	// Para saber si se repite
		Anim(int numberFrames, int widthFrame, int heightFrame, int frameRate, bool loop) :
		numberFrames_(numberFrames), widthFrame_(widthFrame), heightFrame_(heightFrame), frameRate_(frameRate), loop_(loop) {}
		~Anim() {};
	};
	Anim currAnim_{ 0,0,0,0,false };
	//Textura del objeto
	Texture* texture_ = nullptr;
	//Rect del render
	SDL_Rect destiny_ = { 0,0,0,0 };
	//El clip que se va a renderizar de la textura
	SDL_Rect frame_ = { 0,0,0,0 };
	//Último frame de animación
	Uint32 lastFrame_ = 0;
	//Numero de frames que tiene la animación
	//Constructora vacia de Draw
	Draw() {};
	//Constructora con argumentos de Draw
	Draw(Application* app, Point2D pos, Vector2D scale) :
		GameObject(app, pos, scale) {
		initObject();
	};
	//Constructora por copia de Draw
	Draw(const Draw& other) : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};
	//Constructora por movimiento de Draw
	Draw(const Draw&& other)noexcept : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};

	//Inicializa destiny
	virtual void initObject() {
		destiny_.x = (int)pos_.getX();
		destiny_.y = (int)pos_.getY();
		destiny_.w = (int)scale_.getX();
		destiny_.h = (int)scale_.getY();
	};
	virtual void initAnims() {};
public:
	//Para construir un background
	Draw(Application* app, Texture* texture) :
		GameObject(app, Vector2D(0, 0), Vector2D(app->getWindowWidth(), app->getWindowHeight())),
		texture_(texture) {
		initObject();
	}

	//Para construir un texto y elementos del HUD
	Draw(Application* app, Texture* texture, SDL_Rect dest) :
		GameObject(app, Vector2D((double)dest.x, (double)dest.y), Vector2D((double)dest.w, (double)dest.h)), texture_(texture), destiny_(dest) {};

	//Destructora de Draw
	virtual ~Draw() { texture_ = nullptr; };

	//<metodo comun para renderizar tanto imagenes con un solo frame como con varios"
	const virtual void draw();
	
	//<summary>cambia el frame </summary>
	virtual bool update() { return false; };
	//Cambia de animación
	void changeAnim(const Anim& newAnim);
	//Cambia al siguiente frame
	virtual void updateFrame();


#pragma region getters
//Devuelve el rectangulo destino
	const virtual SDL_Rect& getDestiny() {
		destiny_.x = (int)pos_.getX();
		destiny_.y = (int)pos_.getY();
		destiny_.w = (int)scale_.getX();
		destiny_.h = (int)scale_.getY();
		return destiny_;
	};
	//Dada una posición le resta el offset del objeto que invoca el método
	//de tal forma que si este se mueve a la dicha posición queda con "los pies" colocados en ella
	Vector2D getVisPos()
	{
		Vector2D vis;
		vis.setX(pos_.getX() + (scale_.getX() / 2));
		vis.setY(pos_.getY() + (scale_.getY() * 0.8));
		return vis;
	}
#pragma endregion

#pragma region setters
	void setFrame(const SDL_Rect& frame) { frame_ = frame; }; //Asigna el frame
	//Asigna el rectangulo de destino (modificado porque tiene que cambiar el tamaño del gameObject)
	void setDestiny(SDL_Rect destiny) {  
		pos_.setVec({ (double)destiny.x, (double)destiny.y });
		scale_.setVec({ (double)destiny.w, (double)destiny.h }); 
		destiny_ = destiny;
	};
	void setTexture(Texture* texture) { texture_ = texture; }; //Asigna la textura
#pragma endregion
};