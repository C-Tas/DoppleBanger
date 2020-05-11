#include "tutorialObject.h"

bool tutorialObject::update()
{
	return false;
}

void tutorialObject::initialStats() {
	rangeVision_ = 0;
	HEALTH = 1000;
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

void tutorialObject::initObject() {

}
