#include "tutorialObject.h"

bool tutorialObject::update() {
	//Solo entra con el dummy
	if (currState_ == STATE::DYING) {
		
		switch (id_)
		{
		case 1:

			break;
		case 2:
			app_->getAudioManager()->playChannel(Resources::AudioId::DummyDie, 0, (int)EFFECT::TUTORIAL);
			break;
		default:
			break;
		}
		onCollider();	//Para dar la misión como terminada
		applyRewards();
		CollisionCtrl::instance()->removeDummy();
		return true;
	}
	return false;
}

void tutorialObject::initialStats() {
	rangeVision_ = 0;
	HEALTH = 400;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 0;
	MELEE_DMG = 0;
	DIST_DMG = 0;
	CRIT = 0;
	MELEE_RANGE = 0;
	DIST_RANGE = 0;
	MOVE_SPEED = 0;
	MELEE_RATE = 0;
	DIST_RATE = 0;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
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
	}
}

void tutorialObject::initObject() {
	Enemy::initObject();
	initRewards();
}