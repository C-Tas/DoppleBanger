#include "RandEquipGen.h"
#include "Application.h"
#include "GameManager.h"
#include "usable.h"
#include "Armor.h"
#include "Boots.h"
#include "Gloves.h"
#include "Gun.h"
#include "Sword.h"

RandEquipGen::RandEquipGen(Application* app) : app_(app)
{
	rn_ = app_->getRandom();
	gameManager_ = GameManager::instance();
}

Item* RandEquipGen::genEquip()
{
	equipType type = (equipType)(rn_->nextInt(0, (int)equipType::Size+(int)potionType::Size));
	return genEquip((int)type);
}

Item* RandEquipGen::genEquip(int type)
{
	//Aqu� visual me hizo declararlo todo a parte o no compilaba
	int ad, health, armor, price, crit, speed;
	double meleeRate, distRate/*, distRange*/;

	Item* obj;
	int area = (int)gameManager_->getUnlockedIslands() + 1;
	//comprobamos si se trata de equipamiento o pociones
	if (type <= (int)equipType::Size) {
		switch ((equipType)type)
		{
			//Vida y armadura
		case equipType::ArmorI:
			health = rn_->nextInt(200 * area, 300 * area);
			armor = rn_->nextInt(3 * area, 8 * area);
			price = rn_->nextInt(50 * area, 150 * area);
			obj = new Armor(app_, price, health, armor, (equipType)type);
			break;

		case equipType::ArmorII:
			health = rn_->nextInt(100 * area, 200 * area);
			armor = rn_->nextInt(5 * area, 10 * area);
			price = rn_->nextInt(50 * area, 150 * area);
			obj = new Armor(app_, price, health, armor, (equipType)type);
			break;
			//Velocidad y armadura
		case equipType::BootsI:
			speed = rn_->nextInt(8 * area, 14 * area);
			armor = rn_->nextInt(2 * area, 3 * area);
			price = rn_->nextInt(20 * area, 80 * area);
			obj = new Boots(app_, price, speed, armor, (equipType)type);
			break;
		case equipType::BootsII:
			speed = rn_->nextInt(5 * area, 9 * area);
			armor = rn_->nextInt(5 * area, 9 * area);
			price = rn_->nextInt(20 * area, 80 * area);
			obj = new Boots(app_, price, speed, armor, (equipType)type);
			break;

			//Cr�tico y armadura
		case equipType::GlovesI:
			crit = rn_->nextInt(15 * area, 50* area);
			armor = rn_->nextInt(0 * area, 4 * area);
			price = rn_->nextInt(35 * area, 100 * area);
			obj = new Gloves(app_, price, crit, armor, (equipType)type);
			break;
		case equipType::GlovesII:
			crit = rn_->nextInt(10 * area, 20 * area);
			armor = rn_->nextInt(10 * area, 20 * area);
			price = rn_->nextInt(35 * area, 100 * area);
			obj = new Gloves(app_, price, crit, armor, (equipType)type);
			break;

			//Ad y velocidad de ataque
			//Mas alcance que el sable
		case equipType::SwordI:
			ad = rn_->nextInt(50 * area, 100 * area);
			meleeRate = rn_->nextInt(70 * area, 100 * area);
			price = rn_->nextInt(50 * area, 100 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;
		case equipType::SwordII:
			ad = rn_->nextInt(40 * area, 150 * area);
			meleeRate = rn_->nextInt(50 * area, 130 * area);
			price = rn_->nextInt(50 * area, 100 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;

			//Mas da�o que la espada
		case equipType::SaberI:
			ad = rn_->nextInt(130 * area, 180 * area);
			meleeRate = rn_->nextInt(20 * area, 60 * area);
			price = rn_->nextInt(60 * area, 90 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;
		case equipType::SaberII:
			ad = rn_->nextInt(115 * area, 200 * area);
			meleeRate = rn_->nextInt(8 * area, 35 * area);
			price = rn_->nextInt(60 * area, 90 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;

			//Ap y velocidad de disparo
			//Dispara en linea recta con mas da�o
		case equipType::PistolI:
			ad = rn_->nextInt(80 * area, 120 * area);
			distRate = rn_->nextInt(100 * area, 150 * area);
			price = rn_->nextInt(75 * area, 165 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;
		case equipType::PistolII:
			ad = rn_->nextInt(50 * area, 180 * area);
			distRate = rn_->nextInt(60 * area, 170 * area);
			price = rn_->nextInt(75 * area, 165 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;

			//Dispara en are recta con menos da�o
		case equipType::ShotgunI:
			ad = rn_->nextInt(40 * area, 70 * area);
			distRate = rn_->nextInt(30 * area, 80 * area);
			price = rn_->nextInt(80 * area, 175 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;
		case equipType::ShotgunII:
			ad = rn_->nextInt(30 * area, 100 * area);
			distRate = rn_->nextInt(20 * area, 90 * area);
			price = rn_->nextInt(80 * area, 175 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;
		case equipType::Size:
			obj = genEquip();
			break;
		default:
			return nullptr;
			break;
		}
	}
	else {
	//no estamos en el rango de los equipamientos por lo que estamos en el de las pociones 
	type -= ((int)equipType::Size+1);

	switch ((potionType)type)
	{
	case potionType::Health:
		obj = new usable(app_,(potionType)type);
		break;
	case potionType::Mana:
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Speed:
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Armor:
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Damage:
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Crit:
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Size:
		obj = genEquip();
		break;
	default:
		return nullptr;
		break;
	}
}
	return obj;
}