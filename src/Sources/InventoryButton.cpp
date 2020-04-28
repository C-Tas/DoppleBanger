#include "InventoryButton.h"
#include "HandleEvents.h"
#include "Equipment.h"
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
		texture_ = auxTx->getTexture(Resources::Sword1);
		break;
	case equipType::SwordII:
		texture_ = auxTx->getTexture(Resources::Sword2);
		break;
	case equipType::SaberI:
		texture_ = auxTx->getTexture(Resources::Saber1);
		break;
	case equipType::SaberII:
		texture_ = auxTx->getTexture(Resources::Saber2);
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
	SDL_Point mouse = { aux.getX(), aux.getY() };
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