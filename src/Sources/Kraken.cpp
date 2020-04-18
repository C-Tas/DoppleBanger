#include "Kraken.h"
#include "CollisionCtrl.h"

bool Kraken::update() {

	//Si ha muerto
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte?
		//Cuando acabe la animación, lo mata
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}

	updateAnim();
	return false;
}

//Inicializa todas las animaciones
void Kraken::initAnims()
{
	slamAnim_ = Anim(NUM_FRAMES_SLAM, W_FRAME_SLAM, H_FRAME_SLAM, FRAME_RATE_SLAM, NAME_SLAM);
	sweepAnim_ = Anim(NUM_FRAMES_SWEEP, W_FRAME_SWEEP, H_FRAME_SWEEP, FRAME_RATE_SWEEP, NAME_SWEEP);
	inkAnim_ = Anim(NUM_FRAMES_INK, W_FRAME_INK, H_FRAME_INK, FRAME_RATE_INK, NAME_INK);
	diveAnim_ = Anim(NUM_FRAMES_DIVE, W_FRAME_DIVE, H_FRAME_DIVE, FRAME_RATE_DIVE, NAME_DIVE);
	exitAnim_ = Anim(NUM_FRAMES_EXIT, W_FRAME_EXIT, H_FRAME_EXIT, FRAME_RATE_EXIT, NAME_EXIT);
}

//Inicializa el kraken
void Kraken::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Kraken));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	boxCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)boxCollision_.getX(),(int)boxCollision_.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	initAnim();
}