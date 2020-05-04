#include "BeerButton.h"
#include "HandleEvents.h"
#include "MainMenuState.h"
#include "PauseState.h"

BeerButton::BeerButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale,CallBackOnClick* cb) :
	Button(app, nullptr, pos, scale, cb){
	buttonTx_ = texture;
	initAnims();
}

bool BeerButton::update(){
	//Solo entrara cuando no se haya pulsado ningun otro boton o se haya pulsado este
	if (!currentState_->getButtonClick() || clicked_) {
		HandleEvents* input = HandleEvents::instance();
		Vector2D aux = input->getRealMousePos(); //Guardas la posicion del raton
		SDL_Point mouse = { aux.getX(), aux.getY() };

		if (clicked_ && currAnim_.currFrame_ >= currAnim_.numberFrames_) {
			resetButton();
			cbClick_(app_);
			return true;
		}
		//Si esta el raton encima del boton y no ha sido clickado
		if (!clicked_ && SDL_PointInRect(&mouse, &getDestiny())) {
			select_ = true;
			if (input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
				currentState_->setButtonClick(true);
				clicked_ = true;
			}
		}
		//Si no esta el raton encima del boton y no ha sido clickado
		else if (!clicked_) {
			select_ = false;
		}
	}

	return false;
}

const void BeerButton::draw(){
	//Boton principal
	buttonTx_->render(getDestiny(), SDL_FLIP_NONE);
	if (select_) {
		if(clicked_) updateFrame();
		//Animacion de las cervezas
		texture_->render(beerRect, frame_);
	}
}

void BeerButton::initAnims(){
	beerAnim = Anim(NUM_FRAMES, W_FRAME, H_FRAME, FRAME_RATE, false);

	texture_ = app_->getTextureManager()->getTexture(Resources::BeerAnim);
	currAnim_ = beerAnim;

	beerRect.w = scale_.getX() * 1.5;
	beerRect.h = scale_.getY() * 1.7;
	beerRect.x = pos_.getX() + scale_.getX() / 2 - beerRect.w / 2;
	beerRect.y = pos_.getY() + scale_.getY() / 2 - beerRect.h / 2;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void BeerButton::resetButton(){
	select_ = false;
	clicked_ = false;
	currentState_->setButtonClick(false);
	currAnim_.currFrame_ = 0;
}

