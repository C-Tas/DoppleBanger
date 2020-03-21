#pragma once
#include "Draw.h"
#include "Application.h"


using CallBackOnClick = void(Application* App); 
//declaracion de CallBacks

class Button : public Draw
{ 
public:
	Button(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack);
	virtual bool update(); //Lleva la logica del boton
	const virtual void draw();
	virtual ~Button() {};
	void setTexture(Texture* tx) { texture_ = tx; } //Cambia la textura del actual botón por tx
protected:
	CallBackOnClick* ButtonCallBack;

};

