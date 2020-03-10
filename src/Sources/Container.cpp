#include "Container.h"

const void Container::draw()
{	
	SDL_Rect rect;
	rect.x = destiny_.x;
	rect.y = destiny_.y;
	rect.h = destiny_.h;
	rect.w = rect.h * texture_->getW() / texture_->getH();

	if(background_ != nullptr)
		background_->render(destiny_, SDL_FLIP_NONE); //Muestra el fondo del contenedor

	texture_->render(rect, SDL_FLIP_NONE); //Muestra el item en la parte izquierda del contenedor
}

Container::Container(Texture* texture, Texture* background, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, Item* item) : Button(texture, pos, scale, nullptr)
{
	background_ = background;
	item_ = item;
}
