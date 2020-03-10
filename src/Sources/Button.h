#pragma once
#include "Draw.h"
#include "Application.h"


using CallBackOnClick = void(Application* App); 
//declaracion de CallBacks

class Button : public Draw
{ 
public:
	Button(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack);
	virtual bool update();
	const virtual void draw();
	virtual ~Button() {};

protected:
	CallBackOnClick* ButtonCallBack;

};

