#pragma once
#include "Draw.h"
#include "Application.h"


//using CallBackOnClick = void(Application* App); 
using CallBackOnClick = void (Application* app);
using CallBackOnClickMenu = void(GameState * state);
//declaracion de CallBacks

class Button : public Draw
{ 
public:
	Button(Texture* texture,Vector2D pos, Vector2D scale, CallBackOnClick* callBack);
	Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickMenu* callBackMenu);
	virtual void update();
	virtual void Render();
	virtual ~Button() {};

protected:
	
	CallBackOnClick* ButtonCallBack;
	CallBackOnClickMenu* ButtonCallBackMenu;
	int call;

};

