#include "Kirin.h"
#include "GameState.h"
#include "Player.h"
#include "Collisions.h"

Kirin::Kirin(Application* app, Vector2D pos, Vector2D scale, double dmg) : 
	Draw(app, pos, scale),
	damage_(dmg){
	initObject();
}

bool Kirin::update()
{
	updateFrame();
	if (currAnim_.currFrame_ == FRAME_ACTION) {
		attacked_ = true;
		Player* player = GameManager::instance()->getPlayer();
		Vector2D playerCenter = player->getCenter();
		Vector2D playerCollider = player->getColliderScale();
		Vector2D centerCollision = Vector2D(pos_.getX() + scale_.getX() / 2, pos_.getY() + scale_.getY() * 7 / 8);

		//Si el rayo impacta hace daño al player
		if (RectRect((float)playerCenter.getX(), (float)playerCenter.getY(), (float)playerCollider.getX(), (float)playerCollider.getY(),
			(float)centerCollision.getX(), (float)centerCollision.getY(), (float)(scale_.getX() / 2), (float)(scale_.getY() / 4))) {
			player->receiveDamage(damage_);

			return true;
		}
	}
	else if (currAnim_.currFrame_ >= NUM_FRAMES) {
		app_->getCurrState()->removeRenderUpdateLists(this);
	}
	return false;
}

void Kirin::initObject()
{
	currAnim_ = Anim(NUM_FRAMES, W_H_FRAME, W_H_FRAME, FRAME_RATE, false);
 	texture_ = app_->getTextureManager()->getTexture(Resources::Kirin);

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	app_->getCurrState()->addRenderUpdateListsAsFirst(this);
}
