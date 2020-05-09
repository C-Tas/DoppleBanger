#include "usable.h"
#include "Player.h"
#include "Application.h"
#include "GameState.h"
#include "TextBox.h"


void usable::initObject()
{
	switch (type_)
	{
	case potionType::Health:
		price_ = HEALTH_PRICE;
		value_ = HEALTH_VALUE;
		time_ = 0;
		break;
	case potionType::Mana:
		price_ = MANA_PRICE;
		value_ = MANA_VALUE;
		time_ = 0;
		break;
	case potionType::Speed:
		price_ = SPEED_PRICE;
		value_ = SPEED_VALUE;
		time_ = SPEED_TIME;
		break;
	case potionType::Damage:
		price_ = DAMAGE_PRICE;
		value_ = DAMAGE_VALUE;
		time_ = DAMAGE_TIME;
		break;
	case potionType::Armor:
		price_ = ARMOR_PRICE;
		value_ = ARMOR_VALUE;
		time_ = ARMOR_TIME;
		break;
	case potionType::Crit:
		price_ = CRIT_PRICE;
		value_ = CRIT_VALUE;
		time_ = CRIT_TIME;
		break;
	}
}

bool usable::update()
{
	if (used_) {
		if (time_ <= 0) {
			app_->getCurrState()->removeUpdateList(this);
			return true;
		}
		else if ((SDL_GetTicks() - useTime_) / 1000 > time_) {

			desactivePotion();
			return true;
		}
	}

	return false;
}

void usable::use()
{
	used_ = true;
	GameManager* gm_ = GameManager::instance();
	switch (type_)
	{
	case potionType::Speed:
		useTime_ = gm_->getPlayer()->getTimerPotion(0);
		break;
	case potionType::Armor:
		useTime_ = gm_->getPlayer()->getTimerPotion(1);
		break;
	case potionType::Damage:
		useTime_ = gm_->getPlayer()->getTimerPotion(2);
		break;
	case potionType::Crit:
		useTime_ = gm_->getPlayer()->getTimerPotion(3);
		break;
	default:
		useTime_ = 0;
		break;
	}
	
}

void usable::desactivePotion()
{
	GameManager* gm_ = GameManager::instance();
	switch (type_)
	{
	case potionType::Speed:
		gm_->getPlayer()->desactiveBuffPotion(this, 0);
		break;
	case potionType::Damage:
		gm_->getPlayer()->desactiveBuffPotion(this, 1);
		break;
	case potionType::Armor:
		gm_->getPlayer()->desactiveBuffPotion(this, 2);
		break;
	case potionType::Crit:
		gm_->getPlayer()->desactiveBuffPotion(this, 3);
		break;
	}
	app_->getCurrState()->removeUpdateList(this);
}

void usable::getDescription(TextBox* tex)
{
	switch (type_) {
	case potionType::Armor:
		tex->defensePotion();
		break;
	case potionType::Crit:
		tex->criticPotion();
		break;
	case potionType::Damage :
		tex->damagePotion();
		break;
	case potionType::Health :
		tex->lifePotion();
		break;
	case potionType::Mana:
		tex->manaPotion();
		break;
	case potionType::Speed:
		tex->velocityPotion();
		break;
	}
}
