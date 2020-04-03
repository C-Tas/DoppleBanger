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

Player::~Player()
{
	delete armor_;
	delete gloves_;
	delete boots_;
	delete sword_;
	delete gun_;
}