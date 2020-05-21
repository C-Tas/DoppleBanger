#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, int id)
	: Draw(app, pos, scale), cbClick_(callBack) {
	setTexture(texture);
	id_ = id;
};

Button::Button(NoParCallBack* callBack, Application* app, Texture* texture, Vector2D pos, Vector2D scale)
	: Draw(app, pos, scale), cb_(callBack) {
	setTexture(texture);
};

//Button::Button(Application* app, GameState* state,Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickMenu* callBackMenu, int id)
//	: Draw(app,texture, SDL_Rect({(int)pos.getX(),(int)pos.getY(),(int)scale.getX(),(int)scale.getY()})), ButtonCallBackMenu(callBackMenu),currentState_(state) {
//	call = 1;
//};

bool Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getRealMousePos(); //Guardas la posicion del raton
	SDL_Point mouse = { aux.getX(), aux.getY() };

	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		if (cbClick_ != nullptr) {
			cbClick_(app_);
			//app_->getAudioManager()->playChannel(Resources::Time, 0, Resources::AuxMusicChannel2);
		}
		else if (cb_ != nullptr) cb_();
		return true;
	}
	else return false;
}