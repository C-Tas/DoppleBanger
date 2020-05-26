#include "InventoryButton.h"
#include "HandleEvents.h"
#include "Equipment.h"
#include "Armor.h"
#include "Gloves.h"
#include "Boots.h"
#include "Sword.h"
#include "Gun.h"
#include "usable.h"

void InventoryButton::initObject()
{
	//Pregunta qué tipo de objeto es para coger la textura
	if (object_ != nullptr) {
		switch (object_->getObjectType())
		{
		case ObjectType::Equipment:
			initTextureEquipment();
			break;
		case ObjectType::Usable:
			initTextureUsable();
			break;
		}
	}
}

void InventoryButton::initTextureEquipment()
{
	TextureManager* auxTx = app_->getTextureManager();
	switch (dynamic_cast<Equipment*>(object_)->getEquipType())
	{
	case equipType::ArmorI:
		texture_ = auxTx->getTexture(Resources::Armor1);
		break;
	case equipType::ArmorII:
 		texture_ = auxTx->getTexture(Resources::Armor2);
		break;
	case equipType::GlovesI:
		texture_ = auxTx->getTexture(Resources::Gloves1);
		break;
	case equipType::GlovesII:
		texture_ = auxTx->getTexture(Resources::Gloves2);
		break;
	case equipType::BootsI:
		texture_ = auxTx->getTexture(Resources::Boots1);
		break;
	case equipType::BootsII:
		texture_ = auxTx->getTexture(Resources::Boots2);
		break;
	case equipType::SwordI:
		texture_ = auxTx->getTexture(Resources::Sword1H);
		break;
	case equipType::SwordII:
		texture_ = auxTx->getTexture(Resources::Sword2H);
		break;
	case equipType::SaberI:
		texture_ = auxTx->getTexture(Resources::Saber1H);
		break;
	case equipType::SaberII:
		texture_ = auxTx->getTexture(Resources::Saber2H);
		break;
	case equipType::PistolI:
		texture_ = auxTx->getTexture(Resources::Gun1);
		break;
	case equipType::PistolII:
		texture_ = auxTx->getTexture(Resources::Gun2);
		break;
	case equipType::ShotgunI:
		texture_ = auxTx->getTexture(Resources::ShotGun1);
		break;
	case equipType::ShotgunII:
		texture_ = auxTx->getTexture(Resources::ShotGun2);
		break;
	}
}

void InventoryButton::initTextureUsable()
{
	TextureManager* auxTx = app_->getTextureManager();
	switch (dynamic_cast<usable*>(object_)->getType())
	{
	case potionType::Health:
		texture_ = auxTx->getTexture(Resources::HealthPot);
		break;
	case potionType::Mana:
		texture_ = auxTx->getTexture(Resources::ManaPot);
		break;
	case potionType::Speed:
		texture_ = auxTx->getTexture(Resources::SpeedPot);
		break;
	case potionType::Damage:
		texture_ = auxTx->getTexture(Resources::DmgPot);
		break;
	case potionType::Armor:
		texture_ = auxTx->getTexture(Resources::ArmorPot);
		break;
	case potionType::Crit:
		texture_ = auxTx->getTexture(Resources::CritPot);
		break;
	default:
		break;
	}
}

bool InventoryButton::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getRealMousePos();
	SDL_Point mouse = { (int)round(aux.getX()), (int)round(aux.getY()) };
	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		callBackInventory_(app_, this);
		return true;
	}
	else return false;
}

void InventoryButton::setObject(Equipment* ob){
	object_ = ob;
	initObject();
}

void InventoryButton::saveButton(jute::jValue& container)
{
	switch (object_->getObjectType())
	{
	case ObjectType::Equipment:
		saveEquipButton(container);
		break;
	case ObjectType::Usable:
		savePotButton(container);
		break;
	}
}

void InventoryButton::saveEquipButton(jute::jValue& container)
{
	jute::jValue jObj_(jute::jType::JOBJECT);
	jute::jValue aux(jute::jType::JNUMBER);
	Equipment* auxEquip_ = dynamic_cast<Equipment*>(object_);
	//Nombre
	aux.set_string(to_string((int)object_->getObjectType()));
	jObj_.add_property("type", aux);
	equipType auxType = auxEquip_->getEquipType();
	aux.set_string(to_string((int)auxType));
	jObj_.add_property("name", aux);
	//Precio
	string strAux = to_string(auxEquip_->getPrice());
	replace(strAux.begin(), strAux.end(), ',', '.');
	aux.set_string(strAux);
	jObj_.add_property("price", aux);
	//seleccion de objeto (Pechera, Guantes, Botas, Espada, Pistola)
	if (auxType == equipType::ArmorI || auxType == equipType::ArmorII) {
		Armor* auxArmor = dynamic_cast<Armor*>(auxEquip_);
		//Armadura
		strAux = to_string(auxEquip_->getArmor());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("armor", aux);
		//Vida
		strAux = to_string(auxEquip_->getHealth());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("health", aux);
	}
	else if (auxType == equipType::GlovesI || auxType == equipType::GlovesII) {
		Gloves* auxGloves = dynamic_cast<Gloves*>(auxEquip_);
		//Armadura
		strAux = to_string(auxEquip_->getArmor());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("armor", aux);
		//Critico
		strAux = to_string(auxEquip_->getCrit());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("critic", aux);
	}
	else if (auxType == equipType::BootsI || auxType == equipType::BootsII) {
		Boots* auxBoots = dynamic_cast<Boots*>(auxEquip_);
		//Armadura
		strAux = to_string(auxEquip_->getArmor());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("armor", aux);
		//Velocidad de movimiento
		strAux = to_string(auxEquip_->getSpeed());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("speed", aux);
	}
	else if (auxType == equipType::SwordI || auxType == equipType::SwordII
		|| auxType == equipType::SaberI || auxType == equipType::SaberII) {
		Sword* auxSword = dynamic_cast<Sword*>(auxEquip_);
		//Velocidad de ataque melee
		strAux = to_string(auxEquip_->getMeleeRate());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("rate", aux);
		//Daño melee
		strAux = to_string(auxEquip_->getMeleeDmg());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("damage", aux);
	}
	else if (auxType == equipType::PistolI || auxType == equipType::PistolII
		|| auxType == equipType::ShotgunI || auxType == equipType::ShotgunII) {
		Gun* auxGun = dynamic_cast<Gun*>(auxEquip_);
		//Cadencia disparo
		strAux = to_string(auxEquip_->getDistRate());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("rate", aux);
		//Daño distancia
		strAux = to_string(auxEquip_->getDistDmg());
		replace(strAux.begin(), strAux.end(), ',', '.');
		aux.set_string(strAux);
		jObj_.add_property("damage", aux);
	}

	container.add_element(jObj_);
}

void InventoryButton::savePotButton(jute::jValue& container)
{
	jute::jValue jObj_(jute::jType::JOBJECT);
	jute::jValue aux(jute::jType::JNUMBER);
	usable* auxUsable_ = dynamic_cast<usable*>(object_);
	//Nombre
	aux.set_string(to_string((int)object_->getObjectType()));
	jObj_.add_property("type", aux);
	aux.set_string(to_string((int)auxUsable_->getType()));
	jObj_.add_property("name", aux);

	container.add_element(jObj_);
}
 InventoryButton::~InventoryButton() {
	if (!equipped)
		delete object_;
};