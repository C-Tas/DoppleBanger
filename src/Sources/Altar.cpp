#include "Altar.h"
#include "CollisionCtrl.h"
#include "PlayState.h"
#include "Magordito.h"
#include "AltarSkeleton.h"
#include "Collisions.h"
#include "Skeleton.h"

void Altar::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::Altar);
	currAnim_ = Anim(NUM_FRAMES, W_H_FRAME, W_H_FRAME, FRAME_RATE, true);

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Altar::elimina()
{
	actualS--;
}


Altar::~Altar()
{
	mobs.clear();
};

bool Altar::update() {
	updateFrame();
	return false;
}

void Altar::createMobs(PlayState* playState)
{
	if (actualS < MAX_SKELETON) {


		for (int i = 0; i < numMobs_; i++) {
			double xPos = app_->getRandom()->nextInt((int)round(getPosX() - ALTAR_RANGE), (int)round(getPosX() + ALTAR_RANGE));
			double yPos = app_->getRandom()->nextInt((int)round(getPosY() - ALTAR_RANGE), (int)round(getPosY() + ALTAR_RANGE));
			AltarSkeleton* skeleton = new AltarSkeleton(app_, { xPos, yPos }, { SKELETON_W,SKELETON_H },this);
			playState->addEnemy(skeleton);
			CollisionCtrl::instance()->addEnemy(skeleton);
			mobs.push_back(skeleton);
			actualS++;
		}
		magordito_ = playState->getEnemyByTag("Magordito");
		static_cast<Magordito*>(magordito_)->setAltar(this);
		playState->swapRenders(magordito_, this);
	}
}

//bool Altar::outRange(AltarSkeleton* skeleton)
//{
//	Vector2D center = getCenter();
//	Vector2D skeletonCenter = skeleton->getCenter();
//	Vector2D scaleSkeleton = skeleton->getColliderScale();
//	if (RectBall((float)skeletonCenter.getX(), (float)skeletonCenter.getY(), (float)scaleSkeleton.getX(), (float)scaleSkeleton.getY(),
//		(float)center.getX(), (float)center.getY(), (float)scale_.getX())) {
//		return false;
//	}
//	return true;
//}

void Altar::setEnemyToMobs(Clon* enemy)
{
	for (int i = 0; i < mobs.size(); i++) {
		enemy->addEnemy(mobs.at(i));
		mobs.at(i)->setEnemy(enemy);
	}
}

bool Altar::mobsAlive()
{
	int aux = 0;
	for (int i = 0; i < mobs.size(); i++) {
		if (mobs[i] != nullptr) {
			aux++;
		}
	}
	return aux > 0 ? true : false;
}
