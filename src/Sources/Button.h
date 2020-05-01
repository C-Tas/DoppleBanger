#pragma once
#include "Draw.h"
#include "Application.h"

using CallBackOnClick = void (Application* app);

class Button : public Draw
{
public:
	Button(Application* app,Texture* texture,Vector2D pos, Vector2D scale, CallBackOnClick* callBack, int id = 0);
	virtual ~Button() {};
	virtual bool update(); //Lleva la logica del boton
	const virtual void draw() {
		if (currAnim_.numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE);
		else texture_->render(getDestiny(), frame_);
	};
	void setCurrentState(GameState* state) { currentState_ = state; }
	int getId() { return id_; };

protected:
	
	CallBackOnClick* cbClick_ = nullptr;
	Application* appReference_ = nullptr;
	GameState* currentState_ = nullptr;
	virtual void initObject() {};
	virtual void initAnims() {};
	int id_;
};