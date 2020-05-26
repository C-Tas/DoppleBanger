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
#ifdef _DEBUG
		cout << type << endl;
#endif // _DEBUG
		switch ((equipType)type)
		{
			//Vida y armadura
		case equipType::ArmorI:
			health = rn_->nextInt(7 * area, 16 * area);
			armor = rn_->nextInt(3 * area, 8 * area);
			price = rn_->nextInt(2 * area, 4 * area);
			obj = new Armor(app_, price, health, armor, (equipType)type);
			break;

		case equipType::ArmorII:
			health = rn_->nextInt(7 * area, 16 * area);
			armor = rn_->nextInt(3 * area, 8 * area);
			price = rn_->nextInt(2 * area, 4 * area);
			obj = new Armor(app_, price, health, armor, (equipType)type);
			break;
			//Velocidad y armadura
		case equipType::BootsI:
			speed = rn_->nextInt(1 * area, 4 * area);
			armor = rn_->nextInt(2 * area, 6 * area);
			price = rn_->nextInt(1 * area, 2 * area);
			obj = new Boots(app_, price, speed, armor, (equipType)type);
			break;
		case equipType::BootsII:
			speed = rn_->nextInt(1 * area, 4 * area);
			armor = rn_->nextInt(2 * area, 6 * area);
			price = rn_->nextInt(1 * area, 2 * area);
			obj = new Boots(app_, price, speed, armor, (equipType)type);
			break;

			//Cr�tico y armadura
		case equipType::GlovesI:
			crit = rn_->nextInt(3 * area, 8 * area);
			armor = rn_->nextInt(1 * area, 3 * area);
			price = rn_->nextInt(1 * area, 4 * area);
			obj = new Gloves(app_, price, crit, armor, (equipType)type);
			break;
		case equipType::GlovesII:
			crit = rn_->nextInt(3 * area, 8 * area);
			armor = rn_->nextInt(1 * area, 3 * area);
			price = rn_->nextInt(1 * area, 4 * area);
			obj = new Gloves(app_, price, crit, armor, (equipType)type);
			break;

			//Ad y velocidad de ataque
			//Mas alcance que el sable
		case equipType::SwordI:
			ad = rn_->nextInt(5 * area, 16 * area);
			meleeRate = rn_->nextInt(3 * area, 6 * area);
			price = rn_->nextInt(3 * area, 5 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;
		case equipType::SwordII:
			ad = rn_->nextInt(5 * area, 16 * area);
			meleeRate = rn_->nextInt(3 * area, 6 * area);
			price = rn_->nextInt(3 * area, 5 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;

			//Mas da�o que la espada
		case equipType::SaberI:
			ad = rn_->nextInt(6 * area, 17 * area);
			meleeRate = rn_->nextInt(1 * area, 4 * area);
			price = rn_->nextInt(3 * area, 5 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;
		case equipType::SaberII:
			ad = rn_->nextInt(6 * area, 17 * area);
			meleeRate = rn_->nextInt(1 * area, 4 * area);
			price = rn_->nextInt(3 * area, 5 * area);
			obj = new Sword(app_, price, ad, meleeRate, (equipType)type);
			break;

			//Ap y velocidad de disparo
			//Dispara en linea recta con mas da�o y alcance que la escopeta
		case equipType::PistolI:
			ad = rn_->nextInt(5 * area, 16 * area);
			distRate = rn_->nextInt(2 * area, 4 * area);
			price = rn_->nextInt(4 * area, 6 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;
		case equipType::PistolII:
			ad = rn_->nextInt(5 * area, 16 * area);
			distRate = rn_->nextInt(2 * area, 4 * area);
			price = rn_->nextInt(4 * area, 6 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;

			//Dispara en are recta con menos da�o y alcance que la escopeta
		case equipType::ShotgunI:
			ad = rn_->nextInt(3 * area, 13 * area);
			distRate = rn_->nextInt(1 * area, 2 * area);
			price = rn_->nextInt(4 * area, 6 * area);
			obj = new Gun(app_, price, ad, distRate, (equipType)type);
			break;
		case equipType::ShotgunII:
			ad = rn_->nextInt(3 * area, 13 * area);
			distRate = rn_->nextInt(1 * area, 2 * area);
			price = rn_->nextInt(4 * area, 6 * area);
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
#ifdef _DEBUG
	cout << "  x  " << type << endl;
#endif // _DEBUG
	//no estamos en el rango de los equipamientos por lo que estamos en el de las pociones 
	type -= ((int)equipType::Size+1);
#ifdef _DEBUG
	cout <<"  x2  "<< type << endl;
#endif // _DEBUG

	switch ((potionType)type)
	{
	case potionType::Health:
#ifdef _DEBUG
		cout << "h" << endl;
#endif // _DEBUG

		obj = new usable(app_,(potionType)type);
		break;
	case potionType::Mana:
#ifdef _DEBUG
		cout << "m" << endl;
#endif // _DEBUG
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Speed:
#ifdef _DEBUG
		cout << "s" << endl;
#endif // _DEBUG
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Armor:
#ifdef _DEBUG
		cout << "a" << endl;
#endif // _DEBUG
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Damage:
#ifdef _DEBUG
		cout << "d" << endl;
#endif // _DEBUG
		obj = new usable(app_, (potionType)type);
		break;
	case potionType::Crit:
#ifdef _DEBUG
		cout << "h" << endl;
#endif // _DEBUG
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