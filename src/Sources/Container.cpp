#include "Container.h"

void Container::render()
{
	SDL_Rect rect;
	rect.x = pos_.getX();
	rect.y = pos_.getY();
	rect.w = scale_.getX();
	rect.h = scale_.getY();

	background_->render(rect);
	rect.w = rect.h;

	texture_->render(rect);
}

Container::Container(Texture* texture, Texture* background, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, Item* item) : Button(texture, pos, scale, nullptr)
{
	background_ = background;
	item_ = item;
}
