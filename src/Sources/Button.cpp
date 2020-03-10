#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Application* app,Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack)
	: Draw(texture, &SDL_Rect({ 0,0,0,0 }), pos, scale), ButtonCallBack(callBack),appReference_(app)  {
	call = 0;
};

Button::Button(GameState* state,Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickMenu* callBackMenu)
	: Draw(texture, &SDL_Rect({ 0,0,0,0 }), pos, scale), ButtonCallBackMenu(callBackMenu),currentState_(state) {
	call = 1;
};

void Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny())&& input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) 
	{
		if (call == 0) ButtonCallBack(appReference_);
		else if (call == 1) ButtonCallBackMenu(currentState_);
	}
}

void Button::Render() {
	texture_->render(pos_.getX(),pos_.getY());//provisional
}
