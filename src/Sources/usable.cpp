#include "usable.h"
#include "Player.h"

void usable::initObject()
{
	switch (type_)
	{
	case potionType::Health:
		price_ = HEALTH_PRICE;
		value_ = HEALTH_VALUE;
		break;
	case potionType::Mana:
		price_ = MANA_PRICE;
		value_ = MANA_VALUE;
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
		if (time_ <= -1) {
			GameManager::instance()->getPlayer()->desactivePotion(this);
			return true;
		}
		else if (SDL_GetTicks() - useTime_ > time_) {
			GameManager::instance()->getPlayer()->desactivePotion(this);
			return true;
		}
	}

	return false;
}

void usable::use()
{
	used_ = true;
	useTime_ = SDL_GetTicks();
}