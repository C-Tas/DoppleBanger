#include "Player.h"
#include "SDL_macros.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "Collisions.h"
#include "GameState.h"
#include "Resources.h"
#include "TextBox.h"
#include "PlayerBullet.h"

//Habilidades
#include "ClonSkill.h"
#include "WhirlwindSkill.h"
#include "ClonSelfDestructSkill.h"
#include "EmpoweredSkill.h"
#include "RicochetSkill.h"
#include "PerforateSkill.h"

void Player::initObject()
{
	gm_ = GameManager::instance();
	gm_->setPlayer(this);
	CollisionCtrl::instance()->setPlayer(this);
	eventHandler_ = HandleEvents::instance();
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);

	//Inicialización de skills
	skills_.push_back(new WhirlwindSkill(this));
	skills_.push_back(new EmpoweredSkill(this));
	skills_.push_back(new ClonSelfDestructSkill(this));
	skills_.push_back(new ClonSkill(this));

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
	//Resetea el coolDown en el HUD
	for (int i = 0; i < 4; i++) {
		if (skills_[i] != nullptr && cdSkills[i] && !skills_[i]->isCD()) {
			cdSkills[i] = false;
			GameManager::instance()->setSkillCooldown(false, (SkillKey)i);
		}
	}
	//Cuando se acabe el tiempo de ricochet, se pone a false
	if (ricochet_ && (SDL_GetTicks() - lastTimeRico_) / 1000 > TIME_RICO) {
		cout << "Fin rebote" << endl;
		ricochet_ = false;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q)) {
		skills_[0]->action();
		GameManager::instance()->setSkillCooldown(true, SkillKey::Q);
		cdSkills[0] = true;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_W)) {
		skills_[1]->action();
		GameManager::instance()->setSkillCooldown(true, SkillKey::W);
		cdSkills[1] = true;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_E)) {
		skills_[2]->action();
		GameManager::instance()->setSkillCooldown(true, SkillKey::E);
		cdSkills[2] = true;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_R)) {
		skills_[3]->action();
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_SPACE) && !app_->getMute()) shout();

	//Para testeo
	if (eventHandler_->isKeyDown(SDL_SCANCODE_8)) {
		if (skills_[0] != nullptr) delete skills_[0];
		skills_[0] = new RicochetSkill(this);
		cdSkills[0] = false;
		gm_->setSkillEquiped(SkillName::Rebote, SkillKey::Q);
		GameManager::instance()->setSkillCooldown(false, SkillKey::Q);
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_9)) {
		if (skills_[1] != nullptr) delete skills_[1];
		skills_[1] = new PerforateSkill(this);
		cdSkills[1] = false;
		gm_->setSkillEquiped(SkillName::DisparoPerforante, SkillKey::W);
		GameManager::instance()->setSkillCooldown(false, SkillKey::W);
	}

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_)
		shoot(eventHandler_->getRelativeMousePos());

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
		cout << "\nAtaque potenciado\n" << endl;
#endif // _DEBUG
		empoweredAct_ = false;
		objective_->receiveDamage((int)currStats_.meleeDmg_ * empoweredBonus_);
		if (objective_->getState() == STATE::DYING) move(getVisPos(pos_));
		empoweredTime_ = SDL_GetTicks();
		meleeTime_ = empoweredTime_;
	}

	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking_ && objective_ != nullptr && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_&& objective_->getState() != STATE::DYING)
	{
#ifdef _DEBUG
		cout << "\nAtaque a melee\n" << endl;
#endif // _DEBUG
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

void Player::shoot(Vector2D dir)
{
	//Se actualiza el momento del �ltimo disparo
	shotTime_ = SDL_GetTicks();

	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	PlayerBullet* bullet = new PlayerBullet(app_, app_->getTextureManager()->getTexture(Resources::Rock),
		shootPos, dir, currStats_.distDmg_);
	//Activa perforación en la bala
	if (perforate_) {
		bullet->setPerforate(perforate_);
		perforate_ = false;
	}
	//Activa el rebote en la bala
	if (ricochet_)
		bullet->setRicochet(ricochet_);

	//Se añade a los bucles del juegos
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

void Player::decreaseMana(double mana) {
	currStats_.mana_ -= mana;
	if (currStats_.mana_ <= 0) currStats_.mana_ = 0;
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

void Player::setElementsHUD()
{
	gm_->setSkillEquiped(SkillName::Torbellino, SkillKey::Q);
	gm_->setSkillEquiped(SkillName::GolpeFuerte, SkillKey::W);
	gm_->setSkillEquiped(SkillName::Explosion, SkillKey::E);
}

void Player::createClon()
{
	Vector2D pos;
	pos.setX(eventHandler_->getRelativeMousePos().getX() - (scale_.getX() / 2));
	pos.setY(eventHandler_->getRelativeMousePos().getY() - (scale_.getY() * 0.8));
	clon_ = new Clon(app_, pos, scale_, this);
	app_->getGameStateMachine()->getState()->addRenderUpdateLists(clon_);
}

Player::~Player()
{
	//Temporal para no dejar basura
	for (int i = 0; i < skills_.size(); i++) {
		delete skills_[i];
	}

	delete equip_.armor_;
	delete equip_.gloves_;
	delete equip_.boots_;
	delete equip_.sword_;
	delete equip_.gun_;
	delete equip_.potion1_;
	delete equip_.potion2_;
}

void Player::shout()
{
	app_->getAudioManager()->playChannel(Resources::Shout, 0, 1);
}