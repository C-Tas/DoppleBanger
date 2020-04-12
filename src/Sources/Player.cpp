#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBox.h"
#include "GameState.h"
#include "Bullet.h"
#include "GameState.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "Collisions.h"
#include "Skill.h"

void Player::init()
{
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);

	//Equipamiento inicial del jugador
	//Balancear los valores del equipamiento cuando sea necesario
	equip_.armor_ = new Armor(app_->getTextureManager()->getTexture(Resources::TextureId::Wheel), "Pechera", "helloWorld", 10, 10, 10); equip_.armor_->writeStats(); //Prueba
	equip_.gloves_ = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Wheel), "Guantes", "helloWorld", 10, 10, 10); equip_.gloves_->writeStats(); //Prueba
	equip_.boots_ = new Boots(app_->getTextureManager()->getTexture(Resources::TextureId::Wheel), "Botas", "helloWorld", 10, 10, 10); equip_.boots_->writeStats(); //Prueba
	equip_.sword_ = new Sword(app_->getTextureManager()->getTexture(Resources::TextureId::Wheel), "Sable", "helloWorld", 10, 10, 10, Saber_); equip_.sword_->writeStats(); //Prueba
	equip_.gun_ = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Wheel), "Pistola", "helloWorld", 10, 10, 10, Pistol_); equip_.gun_->writeStats(); //Prueba
}

bool Player::update()
{
#pragma region Player Inputs
	//Si se pulsa la Q y se ha acabado el cooldown y se está a rango
	//Hago un if dentro de otro if ya que como el de dentro tiene que hacer cálculos, estos solo se hagan
	//cuando ya se han cumplido previamente las dos condiciones anteriores.
	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q) && ((SDL_GetTicks() - clonTime_) / 1000) > clonCooldown_)
	{
		Vector2D dist = Vector2D(eventHandler_->getRelativeMousePos().getX() - pos_.getX(), eventHandler_->getRelativeMousePos().getY() - pos_.getY());
		if (dist.magnitude() <= CLON_SPAWN_RANGE)
		{
			clon_ = new Clon(app_, getVisPos(eventHandler_->getRelativeMousePos()), scale_, this);
			app_->getGameStateMachine()->getState()->addRenderUpdateLists(clon_);
			clonTime_ = SDL_GetTicks();
		}
	}
	//Si se pulsa la tecla adecuada y el golpe potenciado no está en coodown
	if (empowered_ && eventHandler_->isKeyDown(SDL_SCANCODE_W) && ((SDL_GetTicks() - empoweredTime_) / 1000) > empoweredCooldown_)
	{
#ifdef _DEBUG
		cout << "Ataque potenciado se activa" << endl;
#endif // _DEBUG
		empoweredAct_ = true;
	}
	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_)
		shoot(eventHandler_->getRelativeMousePos());
#pragma endregion

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

	//Si no est� atacando se mueve a la posici�n indicada con un margen de 2 pixels
	int margin = 2; if (attacking_) margin = currStats_.meleeRange_;
	Vector2D visPos = getVisPos(pos_);
	if (visPos.getX() < target_.getX() - margin ||
		visPos.getX() > target_.getX() + margin ||
		visPos.getY() < target_.getY() - margin ||
		visPos.getY() > target_.getY() + margin)
	{
		double delta = app_->getDeltaTime();
		previousPos_ = pos_;
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
		//Al actualizarse aquí la cámara solo modificará la posición de los objetos del estado si existe un jugador
		Camera::instance()->updateCamera(pos_.getX() + scale_.getX() / 2, pos_.getY() + scale_.getY() / 2);
	}

	//Si se ha utilizado el ataque fuerte, ataca con un bonus porcentual de daño
	else if (empoweredAct_ && attacking_ && objective_->getState() != STATE::DYING)
	{
#ifdef _DEBUG
		cout << "Ataque potenciado" << endl;
#endif // _DEBUG
		empoweredAct_ = false;
		objective_->receiveDamage((int)currStats_.meleeDmg_ * empoweredBonus_);
		if (objective_->getState() == STATE::DYING) move(getVisPos(pos_));
		empoweredTime_ = SDL_GetTicks();
		meleeTime_ = empoweredTime_;
	}

	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking_ && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_&& objective_->getState() != STATE::DYING)
	{
		objective_->receiveDamage(currStats_.meleeDmg_);
		if (objective_->getState() == STATE::DYING) move(getVisPos(pos_));
		meleeTime_ = SDL_GetTicks();
	}

	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte
		return true;
	}
#pragma endregion

	
	return false;
}

void Player::initObject() {
	GameManager::instance()->setPlayer(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	CollisionCtrl::instance()->setPlayer(this);
}

void Player::shoot(Vector2D dir)
{
	//Se actualiza el momento del �ltimo disparo
	shotTime_ = SDL_GetTicks();

	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Rock), shootPos, dir, currStats_.distDmg_,
		BULLET_LIFE, BULLET_VEL, Vector2D(W_H_BULLET, W_H_BULLET));
	app_->getCurrState()->addRenderUpdateLists(bullet);
	CollisionCtrl::instance()->addPlayerBullet(bullet);
}

void Player::onCollider()
{
	move(Vector2D(-dir_.getX(), -dir_.getY())); //Rebote
	stop(); //Para
}

void Player::move(Point2D target)
{
	attacking_ = false;
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(target);
	//establecemos la direccion
	Vector2D visPos = getVisPos(pos_);
	dir_.setX(target.getX() - visPos.getX());
	dir_.setY(target.getY() - visPos.getY());
	dir_.normalize();
}

void Player::attack(Enemy* obj)
{
	objective_ = obj;
	move(getVisPos(obj->getPos()));
	attacking_ = true;
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
		currStats_.meleeDmg_ += value;
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