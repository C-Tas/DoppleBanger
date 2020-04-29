#include "Player.h"
#include "SDL_macros.h"
#include "CollisionCtrl.h"
#include "Collisions.h"
#include "GameState.h"
#include "Resources.h"
#include "TextBox.h"
#include "PlayerBullet.h"

//Habilidades y pociones
#include "ClonSkill.h"
#include "WhirlwindSkill.h"
#include "ClonSelfDestructSkill.h"
#include "EmpoweredSkill.h"
#include "RicochetSkill.h"
#include "PerforateSkill.h"
#include "usable.h"
#include "Armor.h"
#include "Gloves.h"
#include "Boots.h"
#include "Sword.h"
#include "Gun.h"

void Player::initObject()
{
	texture_ = auxTx_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	gm_ = GameManager::instance();
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DAMAGE, DIST_DAMAGE, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	initAnims();
	GameManager::instance()->setPlayer(this);
	CollisionCtrl::instance()->setPlayer(this);

	//Equipamiento inicial del jugador
	playerEquipment auxEquip = gm_->getEquip();
	armor_ = auxEquip.armor_;
	gloves_ = auxEquip.gloves_;
	boots_ = auxEquip.boots_;
	gun_ = auxEquip.gun_;
	potions_ = auxEquip.potions_;
}

void Player::load()
{
	playerEquipment auxEquip = gm_->getEquip();
	armor_ = auxEquip.armor_;
	gloves_ = auxEquip.gloves_;
	boots_ = auxEquip.boots_;
	gun_ = auxEquip.gun_;
	potions_ = auxEquip.potions_;
}

void Player::initSkills()
{
	vector<SkillName> skillsEquipped_ = gm_->getAllSkillsEquipped();
	int i = 0;
	SkillName skill;
	for (SkillName ob : skillsEquipped_) {
		skill = gm_->getEquippedSkill((Key)i);
		skills_.push_back(createSkill(skill));
		gm_->setSkillEquiped(skill, (Key)i);
		i++;
	}
}

bool Player::update()
{
	updateFrame();
	//Resetea el coolDown en el HUD
	for (int i = 0; i < 4; i++) {
		if (skills_[i] != nullptr && cdSkills[i] && !skills_[i]->isCD()) {
			cdSkills[i] = false;
			GameManager::instance()->setSkillCooldown(false, (Key)i);
		}
	}
	//Cuando se acabe el tiempo de ricochet, se pone a false
	if (ricochet_ && (SDL_GetTicks() - lastTimeRico_) / 1000 > TIME_RICO) {
		ricochet_ = false;
	}

	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q) && skills_[0]!= nullptr) {
		skills_[0]->action();
		GameManager::instance()->setSkillCooldown(true, Key::Q);
		cdSkills[0] = true;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_W) && skills_[1] != nullptr) {
		skills_[1]->action();
		GameManager::instance()->setSkillCooldown(true, Key::W);
		cdSkills[1] = true;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_E) && skills_[2] != nullptr) {
		skills_[2]->action();
		GameManager::instance()->setSkillCooldown(true, Key::E);
		cdSkills[2] = true;
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_R) && skills_[3] != nullptr) {
		skills_[3]->action();
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_SPACE) && !app_->getMute()) shout();

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_) {
		initShoot();
	}

	
	if (eventHandler_->isKeyDown(SDLK_1) && potions_[0] != nullptr && !potions_[0]->isUsed()) {
		usePotion(potions_[0], 0);
		gm_->setObjectEquipped(ObjectName::Unequipped, Key::One);
	}
	if (eventHandler_->isKeyDown(SDLK_2) && potions_[1] != nullptr && !potions_[1]->isUsed()) {
		usePotion(potions_[1], 1);
		gm_->setObjectEquipped(ObjectName::Unequipped, Key::Two);
	}

	Enemy* objective = static_cast<Enemy*>(currEnemy_);
	//Si no est� atacando se mueve a la posici�n indicada con un margen de 2 pixels
	Vector2D target = target_;
	if (attacking_) {
		target = objective->getVisPos();
		updateDir(target);
	}
	Vector2D visPos = getVisPos();
	list<Enemy*> enemiesInRange = CollisionCtrl::instance()->getEnemiesInArea(getCenter(), currStats_.meleeRange_);
	if ((visPos.getX() < target.getX() - 2 || visPos.getX() > target.getX() + 2 || visPos.getY() < target.getY() - 2 || visPos.getY() > target.getY() + 2) &&
		(!attacking_ || objective == nullptr || objective->getState() == STATE::DYING || enemiesInRange.empty()))
	{
		double delta = app_->getDeltaTime();
		previousPos_ = pos_;
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
		//Al actualizarse aquí la cámara solo modificará la posición de los objetos del estado si existe un jugador
		Camera::instance()->updateCamera(pos_.getX() + scale_.getX() / 2, pos_.getY() + scale_.getY() / 2);
	}
	else if (attacking_ && objective != nullptr && objective->getState() != STATE::DYING && !enemiesInRange.empty())
	{
		bool found = false;
		for (auto it = enemiesInRange.begin(); !found && it != enemiesInRange.end(); ++it)
			if ((*it) == objective)
				found = true;

		if (found && empoweredAct_ && !empoweredAnim_)
		{
			cout << "\nAtaque potenciado\n" << endl;
			empoweredAnim_ = true;
			initMelee();
		}
		else if (found && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_)
		{
			cout << "\nAtaque a melee\n" << endl;
			initMelee();
		}
	}
	//En caso de que no esté atacando y ya haya llegado al objetivo (primer if)
	//cambiará de moviéndose a Idle
	else if (currState_ == STATE::FOLLOWING) {
		initIdle();
	}

	//Gestion de estados y animaciones
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

void Player::initIdle()
{
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)lookAt];
	currAnim_ = idleAnims_[(int)lookAt];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initMove()
{
	mousePos_ = eventHandler_->getRelativeMousePos();
	texture_ = moveTx_[(int)lookAt];
	currAnim_ = moveAnims_[(int)lookAt];
	if (currState_ != STATE::FOLLOWING) {
		currState_ = STATE::FOLLOWING;
		frame_.x = 0; frame_.y = 0;
	}

	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initShoot()
{
	stop();
	currState_ = STATE::SHOOTING;	//Cambio de estado
	mousePos_ = eventHandler_->getRelativeMousePos();
	shooted_ = false;	//Aún no se ha creado la bala
	updateDirVisMouse();	//Hacia dónde mira
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

	//Inicio de lso frames
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initMelee()
{
	currState_ = STATE::ATTACKING;	//Cambio de estado
	attacked_ = false;	//Aún no se ha atacado
	updateDirVisEnemy();	//Hacia dónde está el enemigo
	texture_ = meleeTx_[(int)lookAt];
	currAnim_ = meleeAnims_[(int)lookAt];
	//Frame exacto del ataque
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

	//Se inicia el frame
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
	meleeTime_ = SDL_GetTicks();
}

void Player::updateDirVisMouse()
{
	mousePos_ = eventHandler_->getRelativeMousePos();
	Vector2D center = getCenter();		//Punto de referencia
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
	if (currEnemy_ != nullptr) {
		Vector2D center = getCenter();		//Punto de referencia
		Vector2D enemyCenter = currEnemy_->getCenter();
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
		initIdle();	//Activa el idle
	}
}

void Player::meleeAnim()
{
 	if (!attacked_ && currAnim_.currFrame_ == frameAction_) {
		double totalDmg = currStats_.meleeDmg_;	//Daño total por si hace el Golpe Fuerte
		if (empoweredAct_) { //Golpe fuerte
			empoweredAct_ = false;
			totalDmg = currStats_.meleeDmg_ * empoweredBonus_;
			empoweredTime_ = SDL_GetTicks();
			meleeTime_ = empoweredTime_;
		}

		static_cast<Enemy*>(currEnemy_)->receiveDamage(totalDmg);
		if (static_cast<Enemy*>(currEnemy_)->getState() == STATE::DYING) attacking_ = false;
		attacked_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		empoweredAnim_ = false;
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

	//Animación de movimiento
	//Arriba
	moveAnims_.push_back(Anim(MOVE_U_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MOVE_U_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMoveUpAnim));
	//Derecha														
	moveAnims_.push_back(Anim(MOVE_R_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MOVE_R_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMoveRightAnim));
	//Abajo
	moveAnims_.push_back(Anim(MOVE_D_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MOVE_D_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMoveDownAnim));
	//Izquierda
	moveAnims_.push_back(Anim(MOVE_L_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, MOVE_L_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerMoveLeftAnim));

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

	if (clon_ != nullptr)
		clon_->shoot(dir);
}

void Player::onCollider()
{
	stop(); //Para
}

void Player::updateDir(Vector2D target)
{
	Vector2D visPos = getVisPos();
	dir_.setX(target.getX() - visPos.getX());
	dir_.setY(target.getY() - visPos.getY());
	dir_.normalize();
}

void Player::move(Point2D target)
{
	attacking_ = false;
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(target);
	//establecemos la direccion
	Vector2D visPos = getVisPos();
	dir_.setX(target.getX() - visPos.getX());
	dir_.setY(target.getY() - visPos.getY());
	dir_.normalize();
 	initMove();
}

void Player::attack(Enemy* obj)
{
	currEnemy_ = obj;
	move(obj->getVisPos());
	attacking_ = true;
}

void Player::activeInvincible()
{
	currStats_.crit_ += CRIT_INV;
	currStats_.meleeDmg_ += DMG_INV;
	currStats_.distDmg_ += DMG_INV;
}

void Player::decreaseMana(double mana) {
	currStats_.mana_ -= mana;
	if (currStats_.mana_ <= 0) currStats_.mana_ = 0;
}

void Player::usePotion(usable* potion, int key) {
	double auxValue = potion->getValue();
	switch (potion->getType())
	{
	case potionType::Health:
		currStats_.health_ = maxHealth_ * (1 + (auxValue / 100));
		if (currStats_.health_ > maxHealth_) currStats_.health_ = maxHealth_;
		break;
	case potionType::Mana:
		currStats_.mana_ = maxMana_ * (1 + auxValue / 100);
		if (currStats_.mana_ > MANA) currStats_.mana_ = MANA;
		break;
	case potionType::Speed:
		if (!potionUsing_[0]) {
			cout << "Suma velocidad" << endl;
			currStats_.moveSpeed_ += auxValue;
			potionUsing_[0] = true;
		}
		timerPotion_[0] = SDL_GetTicks();	//Se resetea el tiempo de duración
		break;
	case potionType::Armor:
		if (!potionUsing_[1]) {
			currStats_.armor_ += auxValue;
			potionUsing_[1] = true;
		}
		timerPotion_[1] = SDL_GetTicks();	//Se resetea el tiempo de duración
		break;
	case potionType::Damage:
		if (!potionUsing_[2]) {
			currStats_.meleeDmg_ = currStats_.meleeDmg_ * (1 + auxValue / 100);
			currStats_.distDmg_ = currStats_.distDmg_ * (1 + auxValue / 100);
			potionUsing_[2] = true;
		}
		timerPotion_[2] = SDL_GetTicks();	//Se resetea el tiempo de duración
		break;
	case potionType::Crit:
		if (!potionUsing_[3]) {
			currStats_.crit_ += auxValue;
			potionUsing_[3] = true;
		}
		timerPotion_[3] = SDL_GetTicks();	//Se resetea el tiempo de duración
		break;
	}

	app_->getCurrState()->addUpdateList(potion);
	potions_[key] = nullptr;
	gm_->setPotion(key, nullptr);
	potion->use();
}

void Player::desactiveBuffPotion(usable* potion, int timerPos){
	//Como se ha hecho previamente, se ha guardado el momento en el que se usó la poción
	//de esa manera, si se vuelve a usar una poción del mismo tipo, se resetea timerPotion_[timerPos]
	//por lo que unicamente quitara el debufo cuando se cumpla ese tiempo
	if ((SDL_GetTicks() - timerPotion_[timerPos]) / 1000 > potion->getTime()) {
		double auxValue = potion->getValue();
		switch (potion->getType())
		{
		case potionType::Speed:
			currStats_.moveSpeed_ -= auxValue;
			timerPotion_[0] = false;
			break;
		case potionType::Armor:
			currStats_.armor_ -= auxValue;
			timerPotion_[1] = false;
			break;
		case potionType::Damage:
			currStats_.meleeDmg_ = currStats_.meleeDmg_ / (1 + auxValue / 100);
			currStats_.distDmg_ = currStats_.distDmg_ / (1 + auxValue / 100);
			timerPotion_[2] = false;
			break;
		case potionType::Crit:
			currStats_.crit_ -= auxValue;
			timerPotion_[3] = false;
			break;
		default:
			break;
		}
	}
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
}

void Player::shout()
{
	app_->getAudioManager()->playChannel(Resources::Shout, 0, 1);
}

Skill* Player::createSkill(SkillName name)
{
	Skill* skill;
	switch (name)
	{
	case SkillName::Unequipped:
		skill = nullptr;
		break;
	case SkillName::GolpeFuerte:
		skill = new EmpoweredSkill(this);
		break;
	case SkillName::Invencible:
		skill = nullptr;
		break;
	case SkillName::Torbellino:
		skill = new WhirlwindSkill(this);
		break;
	case SkillName::DisparoPerforante:
		skill = new PerforateSkill(this);
		break;
	case SkillName::Raudo:
		skill = nullptr;
		break;
	case SkillName::Rebote:
		skill = new RicochetSkill(this);
		break;
	case SkillName::Clon:
		skill = new ClonSkill(this);
		break;
	case SkillName::LiberacionI:
		skill = nullptr;
		break;
	case SkillName::Explosion:
		skill = new ClonSelfDestructSkill(this);
		break;
	case SkillName::LiberacionII:
		skill = nullptr;
		break;
	default:
		skill = nullptr;
		break;
	}
	return skill;
}