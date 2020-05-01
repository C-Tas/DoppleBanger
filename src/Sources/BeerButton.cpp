#include "BeerButton.h"
#include "HandleEvents.h"

BeerButton::BeerButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* cb) :
	Button(app, nullptr, pos, scale, cb){
	buttonTx_ = texture;
	initAnims();
}

bool BeerButton::update(){
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getRealMousePos(); //Guardas la posicion del raton
	SDL_Point mouse = { aux.getX(), aux.getY() };

	if (clicked_ && currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		resetButton();
		cbClick_(app_);
		return true;
	}
	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		clicked_ = true;
	}
	else return false;
	//Cuando se haya dado click y la animacion se haya acabado
}

const void BeerButton::draw(){
	//Boton principal
	buttonTx_->render(getDestiny(), SDL_FLIP_NONE);
	if (clicked_) {
		updateFrame();
		//Animacion de las cervezas
		if (currAnim_.numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE);
		else texture_->render(getDestiny(), frame_);
	}
}

void BeerButton::initAnims(){
	beerAnim = Anim(NUM_FRAMES, W_FRAME, H_FRAME, FRAME_RATE, false);

	texture_ = app_->getTextureManager()->getTexture(Resources::BeerAnim);
	currAnim_ = beerAnim;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void BeerButton::resetButton(){
	clicked_ = false;
	currAnim_.currFrame_ = 0;
}

