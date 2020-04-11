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
	Button(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* cbClick);
	Button(Application* app, GameState* state,Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickMenu* callBackMenu);
	virtual ~Button() {};
	virtual bool update(); //Lleva la logica del boton
	void setCurrentState(GameState* state) { currentState_ = state; }
	const virtual void draw() {
		if (currAnim_.numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE);
		else texture_->render(getDestiny(), frame_);
	};

protected:
	
	CallBackOnClick* cbClick_ = nullptr;
	CallBackOnClickMenu* ButtonCallBackMenu = nullptr;
	int call;
	Application* appReference_ = nullptr;
	GameState* currentState_ = nullptr;
	virtual void initObject() {};
	virtual void initAnims() {};
};