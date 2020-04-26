#include "RandEquipGen.h"
#include "Application.h"
#include "Resources.h"
#include "GameManager.h"


RandEquipGen::RandEquipGen(Application* app) : app_(app)
{
	rn_ = app_->getRandom();
	gameManager_ = GameManager::instance(); 
}

Equipment* RandEquipGen::genEquip()
{
	equipType type = static_cast<equipType>(rn_->nextInt(0, 5));
	return genEquip(type);
}

Equipment* RandEquipGen::genEquip(equipType type)
{
	//Aqu� visual me hizo declararlo todo a parte o no compilaba
	int ad, health, armor, price, crit, speed;
	double meleeRate, distRate;
	
	Equipment* obj;
	int area = (int)gameManager_->getUnlockedIslands();
	switch (type)
	{
	//Vida y armadura
	case equipType::ArmorI:
		health = rn_->nextInt(7 * area, 16 * area);
		armor = rn_->nextInt(3 * area, 8 * area);
		price = rn_->nextInt(2 * area, 4 * area);
		obj = new Armor(price, health, armor, type);
		break;

	//Velocidad y armadura
	case equipType::BootsI:
		speed = rn_->nextInt(1 * area, 4 * area);
		armor = rn_->nextInt(2 * area, 6 * area);
		price = rn_->nextInt(1 * area, 2 * area);
		obj = new Boots(price, speed, armor, type);
		break;

	//Cr�tico y armadura
	case equipType::GlovesI:
		crit = rn_->nextInt(3 * area, 8 * area);
		armor = rn_->nextInt(1 * area, 3 * area);
		price = rn_->nextInt(1 * area, 4 * area);
		obj = new Gloves(price, crit, armor, type);
		break;

	//Ad y velocidad de ataque
	//Mas alcance que el sable
	case equipType::SwordI:
		ad = rn_->nextInt(5 * area, 16 * area);
		meleeRate = rn_->nextInt(3 * area, 6 * area);
		price = rn_->nextInt(3 * area, 5 * area);
		obj = new Sword(price, ad, meleeRate, type);
		break;

	//Mas da�o que la espada
	case equipType::SaberI:
		ad = rn_->nextInt(6 * area, 17 * area);
		meleeRate = rn_->nextInt(1 * area, 4 * area);
		price = rn_->nextInt(3 * area, 5 * area);
		obj = new Sword(price, ad, meleeRate, type);
		break;

	//Ap y velocidad de disparo
	//Dispara en linea recta con mas da�o y alcance que la escopeta
	case equipType::PistolI:
		ad = rn_->nextInt(5 * area, 16 * area);
		distRate = rn_->nextInt(2 * area, 4 * area);
		price = rn_->nextInt(4 * area, 6 * area);
		obj = new Gun(price, ad, distRate, type);
		break;

	//Dispara en are recta con menos da�o y alcance que la escopeta
	case equipType::ShotgunI:
		ad = rn_->nextInt(3 * area, 13 * area);
		distRate = rn_->nextInt(1 * area, 2 * area);
		price = rn_->nextInt(4 * area, 6 * area);
		obj = new Gun(price, ad, distRate, type);
		break;
	default:
		return nullptr;
		break;
	}

	return obj;
}