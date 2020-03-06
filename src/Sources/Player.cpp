#include "Player.h"

void Player::update()
{
	if (eventHandler_->getMouseButtonState(0))
		move(eventHandler_->getMousePos());

	pos_ = pos_ + (dir_ * currStats_.moveSpeed_); //Pos_ no cambia
}