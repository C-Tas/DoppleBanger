#include "RandEquipGen.h"
#include "Application.h"
#include "GameManager.h"

RandEquipGen::RandEquipGen(Application* app) : app_(app)
{
	rn_ = SRandBasedGenerator();
	gameManager_ = GameManager::instance(); 
}

Equipment* RandEquipGen::genEquip()
{
	equipType type = static_cast<equipType>(rn_.nextInt(0, 5));
	return genEquip(type);
}

Equipment* RandEquipGen::genEquip(equipType type)
{
	Equipment* obj = new Equipment(type);
	
	int area = (int)gameManager_->getUnlockedIslands();
	switch (type)
	{
	//Vida y armadura
	case Armor:
		obj->setHealth(rn_.nextInt(7 * area, 16 * area));
		obj->setArmor(rn_.nextInt(3 * area, 8 * area));
		break;

	//Velocidad y armadura
	case Boots:
		obj->setSpeed(rn_.nextInt(1 * area, 4 * area));
		obj->setArmor(rn_.nextInt(2 * area, 6 * area));
		break;

	//Crítico y armadura
	case Gloves:
		obj->setCrit(rn_.nextInt(3 * area, 8 * area));
		obj->setArmor(rn_.nextInt(1 * area, 3 * area));
		break;

	//Ad y velocidad de ataque
	case Sword:
		obj->setAd(rn_.nextInt(5 * area, 16 * area));
		obj->setMeleeRate(rn_.nextInt(1 * area, 4 * area)); //Revisar fórmula
		break;

	//Ap y velocidad de disparo
	case Gun:
		obj->setAd(rn_.nextInt(5 * area, 16 * area));
		obj->setDistRate(rn_.nextInt(1 * area, 4 * area)); //Revisar fórmula
		break;
	}

	return obj;
}