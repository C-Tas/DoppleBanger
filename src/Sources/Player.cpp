#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBoxManager.h"

void Player::init()
{
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MOVE_SPEED, MELEE_RATE, DIST_RATE);

	//Equipamiento inicial del jugador
	//Balancear los valores del equipamiento cuando sea necesario
	armor_ = new Armor(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pechera", "helloWorld", 10, 10, 10); armor_->writeStats(); //Prueba
	gloves_ = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Guantes", "helloWorld", 10, 10, 10); gloves_->writeStats(); //Prueba
	boots_ = new Boots(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Botas", "helloWorld", 10, 10, 10); boots_->writeStats(); //Prueba
	sword_ = new Sword(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Sable", "helloWorld", 10, 10, 10, Saber_); sword_->writeStats(); //Prueba
	gun_ = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pistola", "helloWorld", 10, 10, 10, Pistol_); gun_->writeStats(); //Prueba
}

bool Player::update()
{
	updateVisPos();
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
		move(eventHandler_->getMousePos());

	//Margen de 2 pixeles
	if (visPos_.getX() < obj_.getX() - 2 ||
		visPos_.getX() > obj_.getX() + 2 ||
		visPos_.getY() < obj_.getY() - 2 ||
		visPos_.getX() > obj_.getX() + 2)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}

	return false;
}

//void Player::equip(Equipment* equip)
//{
//	//Se distingue el tipo del equipamiento, se desequipa el actual y se equipa el nuevo
//	if (dynamic_cast<Armor*>(equip) != nullptr) {
//		armor_->remove(this);
//		delete armor_; //Para que la prueba no deje basura
//		armor_ = static_cast<Armor*>(equip);
//		armor_->equip(this);
//		armor_->writeStats(); //Prueba
//	}
//	else if (dynamic_cast<Gloves*>(equip) != nullptr) {
//		gloves_->remove(this);
//		delete gloves_; //Para que la prueba no deje basura
//		gloves_ = static_cast<Gloves*>(equip);
//		gloves_->equip(this);
//		gloves_->writeStats(); //Prueba
//	}
//	else if (dynamic_cast<Boots*>(equip) != nullptr) {
//		boots_->remove(this);
//		delete boots_; //Para que la prueba no deje basura
//		boots_ = static_cast<Boots*>(equip);
//		boots_->equip(this);
//		boots_->writeStats(); //Prueba
//	}
//	else if (dynamic_cast<Sword*>(equip) != nullptr) {
//		sword_->remove(this);
//		delete sword_; //Para que la prueba no deje basura
//		sword_ = static_cast<Sword*>(equip);
//		sword_->equip(this);
//		sword_->writeStats(); //Prueba
//	}
//	else {
//		gun_->remove(this);
//		delete gun_; //Para que la prueba no deje basura
//		gun_ = static_cast<Gun*>(equip);
//		gun_->equip(this);
//		gun_->writeStats(); //Prueba
//	}
//}

void Player::usePotion(int value, potionType type) {
	switch (type)
	{
	case live_:
		currStats_.health_ += value;
		break;
	case mana_:
		currStats_.mana_ += value;
		break;
	case velocity_:
		currStats_.moveSpeed_ += value;
		break;
	case damage_:
		currStats_.ad_ += value;
		break;
	case defense_:
		currStats_.armor_ += value;
		break;
	case critic_:
		currStats_.crit_ += value;
		break;
	
	}
}
Player::~Player()
{
	delete armor_;
	delete gloves_;
	delete boots_;
	delete sword_;
	delete gun_;
}