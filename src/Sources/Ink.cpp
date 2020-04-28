#include "Ink.h"
#include "CollisionCtrl.h"

bool Ink::update()
{
	if ((SDL_GetTicks() - spawnTime_) / 1000 > INK_DURATION)
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
	spawnTime_ = SDL_GetTicks();
}

void Ink::onCollider()
{
	Player* player = static_cast<Player*>(GameManager::instance()->getPlayer());
	player->applySlow(SLOW_EFFECT, SLOW_DURATION);
}