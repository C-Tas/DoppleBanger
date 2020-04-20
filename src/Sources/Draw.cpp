#include "Draw.h"
#include "GameManager.h"

const void Draw::draw() {
	if (app_->getGameManager()->getOnShip()) {
		if (currAnim_.numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE);
		else texture_->render(getDestiny(), frame_);
	}
	else {
		SDL_Rect dest = getDestiny(); dest.x = dest.x - Camera::instance()->getCamera().getX(); dest.y = dest.y - Camera::instance()->getCamera().getY();
		if (currAnim_.numberFrames_ <= 0) texture_->render(dest, SDL_FLIP_NONE);
		else texture_->render(dest, frame_);
	}
};

void Draw::changeAnim(const Anim& newAnim)
{
	currAnim_ = newAnim;
}

void Draw::updateFrame()
{
	if (currAnim_.numberFrames_ > 0 && currAnim_.frameRate_ <= SDL_GetTicks() - lastFrame_) {
		lastFrame_ = SDL_GetTicks();
		frame_.x = (frame_.x + currAnim_.widthFrame_) % (currAnim_.numberFrames_ * currAnim_.widthFrame_);
		//Esta variable hace falta para identificar el frame en el que se está
		//Por ejemplo, para el disparo se necesita saber el frame exacto del disparo
		currAnim_.currFrame_++;
		if (currAnim_.loop_ && currAnim_.currFrame_ >= currAnim_.numberFrames_)
			currAnim_.currFrame_ = 0;
	}
}
