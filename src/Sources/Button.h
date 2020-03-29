#pragma once
#include "Draw.h"
#include "Application.h"


//using CallBackOnClick = void(Application* App); 
using CallBackOnClick = void (Application* app);
using CallBackOnClickMenu = void(GameState* state);
//declaracion de CallBacks

class Button : public Draw
{ 
public:
	Button(Application* app,Texture* texture,Vector2D pos, Vector2D scale, CallBackOnClick* callBack, int id = 0);
	Button(Application* app, GameState* state,Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickMenu* callBackMenu, int id = 0);
	virtual bool update();
	const virtual void draw();
	virtual ~Button() {};
	int getId() { return id_; };

protected:
	
	CallBackOnClick* ButtonCallBack = nullptr;
	CallBackOnClickMenu* ButtonCallBackMenu = nullptr;
	int call;
	Application* appReference_ = nullptr;
	GameState* currentState_ = nullptr;
	int id_;
};

