#include "Draw.h"

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
