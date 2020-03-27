#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBox.h"
#include "GameState.h"
#include "Bullet.h"
#include "GameState.h"

bool Player::update()
{
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		Vector2D dir = eventHandler_->getMousePos();
		move(getVisPos(dir));
	}

	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q) && ((SDL_GetTicks() - clonTime_) / 1000) > clonCooldown_)
	{
		clon_ = new Clon(app_, eventHandler_->getMousePos(), currStats_.ad_, currStats_.meleeRate_, liberation_, explotion_, scale_);
		app_->getGameStateMachine()->getState()->addRenderUpdateLists(clon_);
		clonTime_ = SDL_GetTicks();
	}

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && (SDL_GetTicks() - lastShot) / 1000 > currStats_.distRate_)
		shoot(eventHandler_->getMousePos());

	//Margen de 2 pixeles
	if (pos_.getX() < obj_.getX() - 2 ||
		pos_.getX() > obj_.getX() + 2 ||
		pos_.getY() < obj_.getY() - 2 ||
		pos_.getX() > obj_.getX() + 2)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}

	return false;
}

void Player::shoot(Vector2D dir)
{
	//Se actualiza el momento del �ltimo disparo
	lastShot = SDL_GetTicks();

	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), shootPos, dir, currStats_.ad_);
	app_->getCurrState()->addRenderUpdateLists(bullet);
}