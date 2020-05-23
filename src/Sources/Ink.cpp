#include "Ink.h"
#include "CollisionCtrl.h"
#include "Kraken.h"

bool Ink::update()
{
	updateCooldowns();
	//Este if en principio estaba planteado para hacerse en funcion del tiempo
	//Sin embargo, cuando se metan las animaciones habra que cambiarlo para que
	//se haga en funcion de las animaciones.

	if(falling)
	{
		updateFrame();
	}

	if (state_ == STATE::FOLLOWING && !fallingCD_.isCooldownActive())
	{
		state_ = STATE::ATTACKING;
		//setTexture(app_->getTextureManager()->getTexture(Resources::RedBar));
		initInk();
		app_->getAudioManager()->playChannel(Resources::KrakenSplash, 0, Resources::KrakenChannel2);
	}
	if ( currAnim_.currFrame_ == currAnim_.numberFrames_ - 2) {
		falling = false;
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

void Ink::initAnims()
{
	inkanim_= Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, false);
	inkTx_ = app_->getTextureManager()->getTexture(Resources::InkAnim);
}

void Ink::initInk()
{
	
	//Empieza animación (cambiar el valor de swimTime)
	texture_ = inkTx_;
	currAnim_ = inkanim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Ink::initObject()
{
	//setTexture(app_->getTextureManager()->getTexture(Resources::BlueBar));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addCollider(this);
	lifeCD_.initCooldown(INK_DURATION);
	fallingCD_.initCooldown(FALL_DURATION);
	state_ = STATE::FOLLOWING;
	initAnims();
	texture_ = inkTx_;
	currAnim_ = inkanim_;
}

void Ink::onCollider()
{
	Player* player = GameManager::instance()->getPlayer();
	if (state_ == STATE::ATTACKING)
	{
		//Critico
		double realDamage = kraken_->getDistDmg();
		if (kraken_->applyCritic()) realDamage *= 1.5;

		player->receiveDamage(realDamage);
		state_ = STATE::IDLE;
	}

	player->applySlow(SLOW_EFFECT, SLOW_DURATION);
}