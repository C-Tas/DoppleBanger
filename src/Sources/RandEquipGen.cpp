#include "RandEquipGen.h"
#include "Application.h"
#include "Resources.h"

RandEquipGen::RandEquipGen(Application* app) : app_(app)
{
	rn_ = SRandBasedGenerator();
}

Equipment* RandEquipGen::genEquip()
{
	equipType type = static_cast<equipType>(rn_.nextInt(0, 5));
	return genEquip(type);
}

Equipment* RandEquipGen::genEquip(equipType type)
{
	Equipment* obj;
	int area = app_->getCurrArea(); //Se usa el nivel actual como variable

	//Aquí visual me hizo declararlo todo a parte o no compilaba
	int ad, health, armor, price, crit, speed;
	double meleeRate, distRate;

	//Hay que revisar mucho las fórmulas
	//Cada variable es un número aleatorio entre dos numeros multiplicados por el nivel actual
	//Nótese que ciertos parámetros del equipamiento son placeholders
	switch (type)
	{
	//Vida y armadura
	case Armor_:
		health = rn_.nextInt(7 * area, 16 * area);
		armor = rn_.nextInt(3 * area, 8 * area);
		price = rn_.nextInt(2 * area, 4 * area);
		obj = new Armor(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pechera", "helloWorld", price, health, armor);
		break;

	//Velocidad y armadura
	case Boots_:
		speed = rn_.nextInt(1 * area, 4 * area);
		armor = rn_.nextInt(2 * area, 6 * area);
		price = rn_.nextInt(1 * area, 2 * area);
		obj = new Boots(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Botas", "helloWorld", price, speed, armor);
		break;

	//Crítico y armadura
	case Gloves_:
		crit = rn_.nextInt(3 * area, 8 * area);
		armor = rn_.nextInt(1 * area, 3 * area);
		price = rn_.nextInt(1 * area, 4 * area);
		obj = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Guantes", "helloWorld", price, crit, armor);
		break;

	//Ad y velocidad de ataque
	//Mas alcance que el sable
	case Sword_:
		ad = rn_.nextInt(5 * area, 16 * area);
		meleeRate = rn_.nextInt(3 * area, 6 * area);
		price = rn_.nextInt(3 * area, 5 * area);
		obj = new Sword(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Espada", "helloWorld", price, ad, meleeRate, type);
		break;

	//Mas daño que la espada
	case Saber_:
		ad = rn_.nextInt(6 * area, 17 * area);
		meleeRate = rn_.nextInt(1 * area, 4 * area);
		price = rn_.nextInt(3 * area, 5 * area);
		obj = new Sword(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Sable", "helloWorld", price, ad, meleeRate, type);
		break;

	//Ap y velocidad de disparo
	//Dispara en linea recta con mas daño y alcance que la escopeta
	case Pistol_:
		ad = rn_.nextInt(5 * area, 16 * area);
		distRate = rn_.nextInt(2 * area, 4 * area);
		price = rn_.nextInt(4 * area, 6 * area);
		obj = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pistola", "helloWorld", price, ad, distRate, type);
		break;

	//Dispara en are recta con menos daño y alcance que la escopeta
	case Shotgun_:
		ad = rn_.nextInt(3 * area, 13 * area);
		distRate = rn_.nextInt(1 * area, 2 * area);
		price = rn_.nextInt(4 * area, 6 * area);
		obj = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Trabuco", "helloWorld", price, ad, distRate, type);
		break;
	default:
		return nullptr;
		break;
	}

	return obj;
}