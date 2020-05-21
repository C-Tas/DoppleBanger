#include "Ink.h"
#include "CollisionCtrl.h"
#include "Kraken.h"

bool Ink::update()
{
	updateCooldowns();
	//Este if en principio estaba planteado para hacerse en funcion del tiempo
	//Sin embargo, cuando se metan las animaciones habra que cambiarlo para que
	//se haga en funcion de las animaciones.
	if (state_ == STATE::FOLLOWING && !fallingCD_.isCooldownActive())
	{
		state_ = STATE::ATTACKING;
		setTexture(app_->getTextureManager()->getTexture(Resources::RedBar));
		app_->getAudioManager()->playChannel(Resources::KrakenSplash, 0, Resources::KrakenChannel2);
	}

	else if (state_ == STATE::ATTACKING)
		state_ = STATE::IDLE;
	
	if (!lifeCD_.isCooldownActive())
	{
		app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
		CollisionCtrl::instance()->removeCollider(this);
		return true;
	}
	return false;
}

void Ink::initObject()
{
	setTexture(app_->getTextureManager()->getTexture(Resources::BlueBar));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addCollider(this);
	lifeCD_.initCooldown(INK_DURATION);
	fallingCD_.initCooldown(FALL_DURATION);
	state_ = STATE::FOLLOWING;
}

void Ink::onCollider()
{
	Player* player = GameManager::instance()->getPlayer();
	if (state_ == STATE::ATTACKING)
	{
		player->receiveDamage(kraken_->getDistDmg());
		state_ = STATE::IDLE;
	}

	player->applySlow(SLOW_EFFECT, SLOW_DURATION);
}