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
