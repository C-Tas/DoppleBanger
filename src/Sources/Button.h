#pragma once
#include "Draw.h"
#include "Application.h"


//using CallBackOnClick = void(Application* App); 
using CallBackOnClick = void ();
//declaracion de CallBacks

class Button : public Draw
{ 
public:
	Button(Texture* texture,Vector2D pos, Vector2D scale, CallBackOnClick* callBack);
	virtual void update();
	virtual void Render();
	virtual ~Button() {};

protected:
	
	CallBackOnClick* ButtonCallBack;

};

