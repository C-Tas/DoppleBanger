#include "Chest.h"
#include "HandleEvents.h"

void Chest::pick() {
	rN.genEquip();
	initAnim();
}

bool Chest::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos(); //Guardas la posicion del raton
	SDL_Point mouse = { aux.getX(), aux.getY() };

	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		pick();
		return true;
	}
	else return false;
}

void Chest::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Wheel)); //Cambiar por Chest
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });

	//addTrigger?addObstacle??

}

void Chest::onCollider() {

}