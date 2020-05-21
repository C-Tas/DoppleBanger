#include "Barrel.h"
#include <list>
#include "CollisionCtrl.h"	//Para saber a quienes le afecta la explisión
#include "Cleon.h"			//Para avisar a Cleón de quitar un barril

void Barrel::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	activeBarrel_.initCooldown(BARREL_TIME_ACTIVE);
}

bool Barrel::update()
{
	updateCooldowns();
	if (currState_ == BARREL_STATE::ASSEMBLING && !activeBarrel_.isCooldownActive()) {
		currState_ = BARREL_STATE::READY;
		explosion_.initCooldown(BARREL_TIME_LIFE);
	}
	else if (currState_ == BARREL_STATE::READY && !explosion_.isCooldownActive()) {
		applyRangeDmg();
	}
	return false;
}

void Barrel::onCollider()
{
	applyRangeDmg();
}

void Barrel::initAnims()
{

}

void Barrel::applyRangeDmg()
{
	currState_ = BARREL_STATE::EXPLODING;
	list<Collider*>affecteds = CollisionCtrl::instance()->getEntitiesInArea(getCenter(), EXPL_BARREL_RANGE);
	for (auto afected : affecteds) {
		dynamic_cast<Actor*>(afected)->receiveDamage(BARREL_DMG);
	}
	affecteds.clear();
	CollisionCtrl::instance()->removeBarrel(this);
	app_->getCurrState()->removeRenderUpdateLists(this);
	cleon_->quitBarrel();
}

void Barrel::updateCooldowns()
{
	if (explosion_.isCooldownActive()) { explosion_.updateCooldown(); }
	if (activeBarrel_.isCooldownActive()) { activeBarrel_.updateCooldown(); }
}
