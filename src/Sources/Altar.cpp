#include "Altar.h"
#include "CollisionCtrl.h"
#include "PlayState.h"
#include "Magordito.h"
#include "AltarSkeleton.h"


void Altar::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::ShipDoor);
}

bool Altar::update() {
	
	return false;
}

void Altar::createMobs(PlayState* playState)
{
	for (int i = 0; i < numMobs_; i++) {

		int xPos = app_->getRandom()->nextInt(getPosX() - ALTAR_RANGE, getPosX() + ALTAR_RANGE);
		int yPos = app_->getRandom()->nextInt(getPosY() - ALTAR_RANGE, getPosY() + ALTAR_RANGE);
		AltarSkeleton* skeleton = new AltarSkeleton(app_, { (double)xPos,(double)yPos }, { SKELETON_W,SKELETON_H }, this);
		playState->addEnemy(skeleton);
		mobs.push_back(skeleton);
	}
	magordito_ = playState->getEnemyByTag("Magordito");
	static_cast<Magordito*>(magordito_)->setAltar(this);
	playState->swapRenders(magordito_, this);
	//playState->addRenderList(new Draw(app_, app_->getTextureManager()->getTexture(Resources::Rojo),
		//SDL_Rect({ (int)(getPosX() - ALTAR_RANGE),(int)(getPosY() - ALTAR_RANGE),(int)(getScaleX() + ALTAR_RANGE * 2),(int)(getScaleY() + ALTAR_RANGE * 2) })));
}

bool Altar::outRange(SDL_Rect skeletonRect)
{
	SDL_Rect altarRect = { (int)getPosX(),(int)getPosY(),(int)getScaleX() + ALTAR_RANGE,(int)getScaleY() + ALTAR_RANGE };
	if (SDL_HasIntersection(&skeletonRect, &altarRect)) {
		return false;
	}
	return true;
}

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
