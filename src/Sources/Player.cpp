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
	equip_.armor_ = new Armor(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pechera", "helloWorld", 10, 10, 10); equip_.armor_->writeStats(); //Prueba
	equip_.gloves_ = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Guantes", "helloWorld", 10, 10, 10); equip_.gloves_->writeStats(); //Prueba
	equip_.boots_ = new Boots(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Botas", "helloWorld", 10, 10, 10); equip_.boots_->writeStats(); //Prueba
	equip_.sword_ = new Sword(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Sable", "helloWorld", 10, 10, 10, Saber_); equip_.sword_->writeStats(); //Prueba
	equip_.gun_ = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pistola", "helloWorld", 10, 10, 10, Pistol_); equip_.gun_->writeStats(); //Prueba
}

bool Player::update()
{
	updateVisPos();
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
		move(eventHandler_->getMousePos());

	//para utilizar las pociones
	if (eventHandler_->isKeyDown(SDLK_1)) {
		if (equip_.potion1_ != nullptr) {
			PotionTime1 = SDL_GetTicks();
			equip_.potion1_->use(this);
		}
	}
	if (eventHandler_->isKeyDown(SDLK_2)) {
		if (equip_.potion2_ != nullptr) {
			PotionTime2 = SDL_GetTicks();
			equip_.potion2_->use(this);
		}
	}
	//comprobamos si hay que desactivar las pociones
	desactivePotion();

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
void Player::desactivePotion(){
	//Pocion1
	//Si la pocion uno esta usada
	if (equip_.potion1_ != nullptr && equip_.potion1_->isUsed()  ) {
		//si es de efecto permanente la borramos
		if (equip_.potion1_->getDuration() <= -1) {
			delete equip_.potion1_;
			equip_.potion1_ = nullptr;
		}
		//Si no, miramos si ha pasado el tiempo de duracion
		else if ((SDL_GetTicks() - PotionTime1) >= equip_.potion1_->getDuration()) {
			usePotion(-(equip_.potion1_->getValue()), equip_.potion1_->getType());//quitamos el valor de la pocion
			delete equip_.potion1_;// eliminamos la pocion
			equip_.potion1_ = nullptr;
		}
	}
	//Pocion2
	//Si la pocion uno esta usada
	if (equip_.potion2_ != nullptr && equip_.potion2_->isUsed()) {
		//si es de efecto permanente la borramos
		if (equip_.potion2_->getDuration() <= -1) {
			delete equip_.potion2_;
			equip_.potion2_ = nullptr;
		}
		//Si no, miramos si ha pasado el tiempo de duracion
		else if ((SDL_GetTicks() - PotionTime2) >= equip_.potion2_->getDuration()) {
			usePotion(-(equip_.potion1_->getValue()), equip_.potion2_->getType());//quitamos el valor de la pocion
			delete equip_.potion2_;// eliminamos la pocion
			equip_.potion2_ = nullptr;
		}
	}
}
Player::~Player()
{
	delete equip_.armor_;
	delete equip_.gloves_;
	delete equip_.boots_;
	delete equip_.sword_;
	delete equip_.gun_;
	delete equip_.potion1_;
	delete equip_.potion2_;
}