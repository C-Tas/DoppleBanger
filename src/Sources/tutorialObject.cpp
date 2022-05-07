#include "tutorialObject.h"

bool tutorialObject::update() {
	Enemy::manageTint();
	//Solo entra con el dummy
	if (currState_ == STATE::DYING) {
		if (id_ >= 2) app_->getAudioManager()->playChannel(Resources::AudioId::DummyDie, 0, (int)EFFECT::TUTORIAL);
		//switch (id_)
		//{
		//case 1:

		//	break;
		//case 2:
		//	app_->getAudioManager()->playChannel(Resources::AudioId::DummyDie, 0, (int)EFFECT::TUTORIAL);
		//	break;
		//default:
		//	break;
		//}
		onCollider();	//Para dar la misión como terminada
		applyRewards();
		CollisionCtrl::instance()->removeDummy();
		return true;
	}
	return false;
}

void tutorialObject::initialStats() {
	rangeVision_ = 0;
	initHealth_ = 800;
	initMana_ = 0;
	initManaReg_ = 0;
	initArmor_ = 0;
	initMeleeDmg = 0;
	initDistDmg = 0;
	initCrit_ = 0;
	initMeleeRange = 0;
	initDistRange_ = 0;
	initMoveSpeed = 0;
	initMeleeRate_ = 0;
	initDistRate_ = 0;
	initStats(initHealth_, initMana_, initManaReg_, initArmor_, initMeleeDmg, initDistDmg, initCrit_, initMeleeRange, initDistRange_, initMoveSpeed, initMeleeRate_, initDistRate_);
}

void tutorialObject::onCollider() {
	dynamic_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
	app_->getCurrState()->removeRenderUpdateLists(this);
	auto state = dynamic_cast<tutorialState*>(app_->getCurrState());

	if (state) {
		state->currTaskSucess();
	}
}

void tutorialObject::receiveDamage(int damage) {
	if (app_->getGameManager()->getVenancioPhase() == 2) currStats_.health_ -= damage;
	else if (app_->getGameManager()->getVenancioPhase() == 3 && app_->getGameManager()->getPlayer()->isDummyAttack()) currStats_.health_ = 0;
	if (currStats_.health_ <= 0) {
		this->die();
		currState_ = STATE::DYING;
	}
}

void tutorialObject::initObject() {
	Enemy::initObject();
	initRewards();
}