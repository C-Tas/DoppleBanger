#pragma once
#include "Draw.h"
#include "Application.h"


using CallBackOnClick = void(Application * App);
//declaracion de CallBacks

class Button : public Draw
{
public:
	Button(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* cbClick)
		: Draw(app, pos, scale), cbClick_(cbClick) {
		setTexture(texture);
	};
	virtual ~Button() {};

	virtual bool update(); //Lleva la logica del boton
	const virtual void draw();

protected:
	CallBackOnClick* cbClick_;
	virtual void initObject() {};
};