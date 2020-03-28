#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBoxManager.h"

bool Player::update()
{
	updateVisPos();
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
		move(eventHandler_->getMousePos());

	//Margen de 2 pixeles
	if (visPos_.getX() < target_.getX() - 2 ||
		visPos_.getX() > target_.getX() + 2 ||
		visPos_.getY() < target_.getY() - 2 ||
		visPos_.getX() > target_.getX() + 2)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}

	return false;
}

void Player::initObject() {
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}