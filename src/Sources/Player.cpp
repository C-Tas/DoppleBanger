#include "Player.h"

void Player::update()
{
	if (eventHandler_->getMouseButtonState(0))
		move(eventHandler_->getMousePos());

	if (pos_.getX() < obj_.getX() - 2 ||
		pos_.getX() > obj_.getX() + 2 ||		pos_.getY() < obj_.getY() - 2 ||
		pos_.getX() > obj_.getX() + 2)
	{
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_) / 500));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_) / 500));
	}
}