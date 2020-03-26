#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBoxManager.h"

bool Player::update()
{
	updateVisPos();
	if (meleeCooldown <= currStats_.meleeRate_) meleeCooldown = (SDL_GetTicks() - lastAttack) / 1000;

	//Si no está atacando se mueve a la posición indicada con un margen de 2 pixels
	int margin = 2; if (attacking) margin = currStats_.range_;

	if (visPos_.getX() < obj_.getX() - margin ||
		visPos_.getX() > obj_.getX() + margin ||
		visPos_.getY() < obj_.getY() - margin ||
		visPos_.getX() > obj_.getX() + margin)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}
	else if (attacking && meleeCooldown > currStats_.meleeRate_)
	{
		objective->takeDamage(currStats_.ad_);
		meleeCooldown = 0;
		lastAttack = SDL_GetTicks();
	}

	return false;
}

void Player::move(Point2D target)
{
	attacking = false;
	//establecemos el objetivo para poder parar al llegar
	obj_.setVec(target);
	//establecemos la direccion
	dir_.setX(target.getX() - visPos_.getX());
	dir_.setY(target.getY() - visPos_.getY());
	dir_.normalize();
}

void Player::attack(Enemy* obj)
{
	objective = obj;
	move(obj->getVisPos());
	attacking = true;
}