#include "Barrel.h"
#include <list>
#include "CollisionCtrl.h"	//Para saber a quienes le afecta la explisión
#include "Cleon.h"			//Para avisar a Cleón de quitar un barril

void Barrel::initObject()
{
	activeBarrel_.initCooldown(BARREL_TIME_ACTIVE);
	initAnims();
}

bool Barrel::update()
{
	if (explote_) { updateFrame(); }
	updateCooldowns();
	if (currState_ == BARREL_STATE::ASSEMBLING && !activeBarrel_.isCooldownActive()) {
		currState_ = BARREL_STATE::READY;
		explote_ = true;
	}
	else if (currState_ == BARREL_STATE::READY /*&& !explosion_.isCooldownActive()*/) {
		currState_ = BARREL_STATE::INIT_EXPLOTION;
	}
	else if (currState_ == BARREL_STATE::INIT_EXPLOTION && currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {  //Cuando acaba la animacion
		initExplotion(); //Este te pone en un estado nuevo currState_ = STATE::EXPLOSION
	}
	else if (currState_ == BARREL_STATE::EXPLODING) { //Hace daño a los que tenga a rango
		if (currAnim_.currFrame_ == EXPLOTION_ACTION && !applyDmg_) {
			applyRangeDmg();
			applyDmg_ = true;
		}
		else if (currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) { //Elimina

			app_->getCurrState()->removeRenderUpdateLists(this);
		}
	}

	return false;
}

void Barrel::onCollider()
{
	initExplotion();
}

void Barrel::initAnims()
{
	//Explosión
	explosionTex_ = app_->getTextureManager()->getTexture(Resources::BarrelExplosion);
	explosionAnim_ = Anim(EXPLOTION_FRAMES, EXPLOTION_W, EXPLOTION_H, EXPLOTION_FRAME_RATE, true);
	//InitExplosion
	mechaExplosionTex_ = app_->getTextureManager()->getTexture(Resources::BarrelInitExpl);
	mechaExplosionAnim_ = Anim(INIT_EXPLOTION_FRAMES, EXPLOTION_W, EXPLOTION_H, INIT_EXPLOTION_FRAME_RATE, true);
	
	initMecha();
}

void Barrel::applyRangeDmg()
{
	currState_ = BARREL_STATE::EXPLODING;
	list<Collider*>affecteds = CollisionCtrl::instance()->getEntitiesInArea(getCenter(), (int)round(EXPL_BARREL_RANGE));
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

void Barrel::initMecha()
{

	currAnim_ = mechaExplosionAnim_;
	texture_ = mechaExplosionTex_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Barrel::initExplotion()
{
	CollisionCtrl::instance()->removeBarrel(this);
	currState_ = BARREL_STATE::EXPLODING;
	currAnim_ = explosionAnim_;
	texture_ = explosionTex_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
