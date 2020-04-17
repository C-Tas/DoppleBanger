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
	updateFrame();
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

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_) {
		initShoot();
	}
	else if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		Vector2D dir = eventHandler_->getRelativeMousePos();
		move(getVisPos(dir));
	}

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
	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking_ && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_ && objective_->getState() != STATE::DYING)
	{
		initMelee();
	}

	if (currState_ == STATE::SHOOTING) {
		shootAnim();
	}
	else if (currState_ == STATE::ATTACKING) {
		meleeAnim();
	}
	else if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte
		return true;
	}
	return false;
}

void Player::initObject() {
	texture_ = auxTx_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	initAnims();
	GameManager::instance()->setPlayer(this);
	CollisionCtrl::instance()->setPlayer(this);
}

void Player::initIdle()
{
	currState_ = STATE::IDLE;
	mousePos_ = eventHandler_->getRelativeMousePos();
	texture_ = idleTx_[(int)lookAt];
	currAnim_ = idleAnims_[(int)lookAt];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initShoot()
{
	stop();
	currState_ = STATE::SHOOTING;
	mousePos_ = eventHandler_->getRelativeMousePos();
	shooted_ = false;
	updateDirVisMouse();
	texture_ = shootTx_[(int)lookAt];
	currAnim_ = shootAnims_[(int)lookAt];
	//Asigna el frame donde ocurrirá la acción
	switch (lookAt)
	{
	case DIR::UP:
		frameAction_ = 3;
		break;
	case DIR::RIGHT:
		frameAction_ = 1;
		break;
	case DIR::DOWN:
		frameAction_ = 3;
		break;
	case DIR::LEFT:
		frameAction_ = 1;
	}
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initMelee()
{
	currState_ = STATE::ATTACKING;
	mousePos_ = eventHandler_->getRelativeMousePos();
	attacking_ = false;
	attacked_ = false;
	updateDirVisEnemy();
	texture_ = meleeTx_[(int)lookAt];
	currAnim_ = meleeAnims_[(int)lookAt];
	switch (lookAt)
	{
	case DIR::UP:
		frameAction_ = 1;
		break;
	case DIR::RIGHT:
		frameAction_ = 2;
		break;
	case DIR::DOWN:
		frameAction_ = 2;
		break;
	case DIR::LEFT:
		frameAction_ = 2;
		break;
	}

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::updateDirVisMouse()
{
	mousePos_ = eventHandler_->getRelativeMousePos();
	Vector2D center = getCenter(pos_);		//Punto de referencia
	Vector2D dir = mousePos_ - center;	//Vector dirección
	dir.normalize();
	double angle = atan2(dir.getY(), dir.getX()) * 180 / M_PI;
	if (angle >= 0) {
		if (angle <= 45.0) lookAt = DIR::RIGHT;
		else if (angle < 135.0) lookAt = DIR::DOWN;
		else lookAt = DIR::LEFT;
	}
	else {
		if (angle >= -45.0) lookAt = DIR::RIGHT;
		else if (angle >= -135.0) lookAt = DIR::UP;
		else lookAt = DIR::LEFT;
	}
}

void Player::updateDirVisEnemy() {
	if (objective_ != nullptr) {
		Vector2D center = getCenter(pos_);		//Punto de referencia
		Vector2D enemyCenter = getCenter(objective_->getPos());
		Vector2D dir = enemyCenter - center;		//Vector dirección
		dir.normalize();
		double angle = atan2(dir.getY(), dir.getX()) * 180 / M_PI;
		if (angle >= 0) {
			if (angle <= 45.0) lookAt = DIR::RIGHT;
			else if (angle < 135.0) lookAt = DIR::DOWN;
			else lookAt = DIR::LEFT;
		}
		else {
			if (angle >= -45.0) lookAt = DIR::RIGHT;
			else if (angle >= -135.0) lookAt = DIR::UP;
			else lookAt = DIR::LEFT;
		}
	}
}

void Player::shootAnim()
{
	if (!shooted_ && currAnim_.currFrame_ == frameAction_) {
		shoot(mousePos_);
		shooted_ = true; 
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		currState_ = STATE::IDLE;	//Reseteo de la animación
		initIdle();	//Activa el idle
	}
}

void Player::meleeAnim()
{
	if (!attacked_ && currAnim_.currFrame_ == frameAction_) {
		objective_->receiveDamage(currStats_.meleeDmg_);
		if (objective_->getState() == STATE::DYING) move(getVisPos(pos_));
		meleeTime_ = SDL_GetTicks();
		attacked_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		currState_ = STATE::IDLE;	//Reseteo de la animación
		initIdle();	//Activa el idle
	}
}

void Player::initAnims()
{
	//Animación de idle
	//Arriba
	idleAnims_.push_back(Anim(IDLE_U_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, IDLE_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerIdleUpAnim));			
	//Derecha																						
	idleAnims_.push_back(Anim(IDLE_R_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, IDLE_R_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerIdleRightAnim));		
	//Abajo																							
	idleAnims_.push_back(Anim(IDLE_D_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, IDLE_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerIdleDownAnim));		
	//Izquierda																						
	idleAnims_.push_back(Anim(IDLE_L_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, IDLE_L_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerIdleLeftAnim));

	//Animación de disparo
	//Arriba
	shootAnims_.push_back(Anim(SHOOT_U_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, SHOOT_U_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerShootUpAnim));
	//Derecha
	shootAnims_.push_back(Anim(SHOOT_R_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, SHOOT_R_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerShootRightAnim));
	//Abajo
	shootAnims_.push_back(Anim(SHOOT_D_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, SHOOT_D_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerShootDownAnim));
	//Izquierda
	shootAnims_.push_back(Anim(SHOOT_L_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, SHOOT_L_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerShootLeftAnim));

	//Animación de melee
	//Arriba
	meleeAnims_.push_back(Anim(MELEE_U_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MELEE_U_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMeleeUpAnim));
	//Derecha
	meleeAnims_.push_back(Anim(MELEE_R_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MELEE_R_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMeleeRightAnim));
	//Abajo
	meleeAnims_.push_back(Anim(MELEE_D_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MELEE_D_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMeleeDownAnim));
	//Izquierda
	meleeAnims_.push_back(Anim(MELEE_L_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MELEE_L_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMeleeLeftAnim));

	//Inicializamos con la animación del idle
	lookAt = DIR::DOWN;
	initIdle();
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