#include "Player.h"
#include "CollisionCtrl.h"
#include "GameManager.h"
#include "HandleEvents.h"
#include "SDL_macros.h"
#include "Collisions.h"
#include "PlayerBullet.h"
#include "PlayState.h"
#include "PauseState.h"
#include "Inventory.h"
#include "SkillState.h"

//Habilidades y pociones
#include "Clon.h"
#include "ClonSkill.h"
#include "WhirlwindSkill.h"
#include "ClonSelfDestructSkill.h"
#include "EmpoweredSkill.h"
#include "RicochetSkill.h"
#include "PerforateSkill.h"
#include "usable.h"
//Equipamiento
#include "Armor.h"
#include "Gloves.h"
#include "Boots.h"
#include "Sword.h"
#include "Gun.h"
#include "Blunderbuss.h"


//Inicializadores
Player::Player(Application* app, Vector2D pos, Vector2D scale) : Actor(app, pos, scale) { initObject(); };

Player::~Player()
{
	for (Skill* ob : skills_) {
		delete ob; ob = nullptr;
	}

	delete endZoneTextBox_;
}

void Player::load()
{
	playerEquipment auxEquip = gm_->getEquip();
	armor_ = auxEquip.armor_;
	armor_->equip(this);
	gloves_ = auxEquip.gloves_;
	gloves_->equip(this);
	boots_ = auxEquip.boots_;
	boots_->equip(this);
	sword_ = auxEquip.sword_;
	sword_->equip(this);
	gun_ = auxEquip.gun_;
	gun_->equip(this);
	potions_ = auxEquip.potions_;
}

void Player::initObject()
{
	gm_ = GameManager::instance();
	eventHandler_ = HandleEvents::instance();
	collisionCtrl_ = CollisionCtrl::instance();

	initAnims();
	initStats(maxHealth_, maxMana_, MANA_REG, ARMOR, MELEE_DAMAGE, DIST_DAMAGE, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	
	gm_->setPlayer(this);
	collisionCtrl_->setPlayer(this);
	
	endZoneTextBox_ = new TextBox(app_);
	posCollision_ = Vector2D((scale_.getX() / 3), (scale_.getY() / 4));
	scaleCollision_ = { scale_.getX() / 3, scale_.getY() / 2 };
	
	//Equipamiento inicial del jugador
	playerEquipment auxEquip = gm_->initEquipment();
	armor_ = auxEquip.armor_;
	armor_->equip(this);
	gloves_ = auxEquip.gloves_;
	gloves_->equip(this);
	boots_ = auxEquip.boots_;
	boots_->equip(this);
	sword_ = auxEquip.sword_;
	sword_->equip(this);
	gun_ = auxEquip.gun_;
	gun_->equip(this);
	potions_ = auxEquip.potions_;
}

void Player::initSkills()
{
	vector<SkillName> skillsEquipped_ = gm_->getAllSkillsEquipped();
	int i = 0;
	SkillName skill;
	for (SkillName& ob : skillsEquipped_) {
		skill = gm_->getEquippedSkill((Key)i);
		skills_.at(i) = createSkill(skill);
		gm_->setSkillEquiped(skill, (Key)i);
		i++;
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

	//Animacion GolpeFuerte
	//Arriba
	empoweredAnims_.push_back(Anim(EMPOWERED_U_D_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, EMPOWERED_U_D_RATE, false));
	empoweredTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerEmpoweredUp));
	//Derecha
	empoweredAnims_.push_back(Anim(EMPOWERED_R_L_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, EMPOWERED_R_L_RATE, false));
	empoweredTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerEmpoweredRight));
	//Abajo
	empoweredAnims_.push_back(Anim(EMPOWERED_U_D_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, EMPOWERED_U_D_RATE, false));
	empoweredTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerEmpoweredDown));
	//Izquierda
	empoweredAnims_.push_back(Anim(EMPOWERED_R_L_FRAMES, W_H_PLAYER_FRAME, W_H_PLAYER_FRAME, EMPOWERED_R_L_RATE, false));
	empoweredTx_.push_back(app_->getTextureManager()->getTexture(Resources::PlayerEmpoweredLeft));

	//Inicializamos con la animación del idle
	currDir_ = DIR::DOWN;
	initIdle();
}

//Updates
bool Player::update()
{
	updateFrame();		//Actualiza animacion
	if (currState_ == STATE::DYING) {
		dieAnim();
		return dead_;
	}
	else {
		//Actualizadores
		manageTint();		//Actualiza el tint
		updateCooldowns();	//Actualiza cooldowns
		updateBuffPotion();	//Actualiza estado de pociones
		updateDebuffs();	//Efectos de estado
		manaReg();			//Regeneramos mana
		
		//Gestion de animaciones con accion
		animator();

		#ifdef _DEBUG
		//Checkea el input para chetar al player
		checkInputCheat();
		#endif // _DEBUG

		//Eventos de teclado
		checkInputState();
		if (!bussy_) checkInput();

		//Gestion de movimiento
		if(!changeZone_) movementManager();
	}
	return changeZone_;
}

void Player::updateCooldowns()
{
	//Resetea el coolDown en el HUD
	for (int i = 0; i < skills_.size(); i++) {

		if (skills_.at(i) != nullptr) {
			skills_.at(i)->update();
			gm_->setSkillCooldown(skills_.at(i)->isCD(), (Key)i);
		}
	}
	//COOLDOWN
	if (shootCD_.isCooldownActive()) { shootCD_.updateCooldown(); }
	if (meleeCD_.isCooldownActive()) { meleeCD_.updateCooldown(); }
	if (empoweredCD_.isCooldownActive()) { empoweredCD_.updateCooldown(); }
	if (ricochetCD_.isCooldownActive()) { ricochetCD_.updateCooldown(); }
	if (slowTimeCD_.isCooldownActive()) slowTimeCD_.updateCooldown();
}

void Player::updateBuffPotion(){
	//Como se ha hecho previamente, se ha guardado el momento en el que se usó la poción
	//de esa manera, si se vuelve a usar una poción del mismo tipo, se resetea timerPotion_[timerPos]
	//por lo que unicamente quitara el debufo cuando se cumpla ese tiempo
	for (int i = 0; i < potionUsing_.size(); i++) {
		if (potionUsing_.at(i)) {
			double currTick_ = SDL_GetTicks();

			//Si se abre el inventario, los skills o la pausa no reducimos la duración (el valor suele estar entre 0 y 10, así que 200 que son 0,2 segundos es más que suficiente para determinar pausa)
			if (currTick_ - lastTicksPotion_.at(i) <= gm_->getDelayTime()) {
				timerPotion_.at(i) -= currTick_ - lastTicksPotion_.at(i);
			}

			lastTicksPotion_.at(i) = currTick_;
			//Condicion para que se desactive la pocion
			if (timerPotion_.at(i) <= 0) {
				switch (i + 2)
				{
				case (int)potionType::Speed:
					currStats_.moveSpeed_ -= valuePotion_.at(i);
					potionUsing_[0] = false;
					break;
				case (int)potionType::Armor:
					currStats_.armor_ -= valuePotion_.at(i);
					potionUsing_[1] = false;
					break;
				case (int)potionType::Damage:
					currStats_.meleeDmg_ = currStats_.meleeDmg_ / (1 + valuePotion_.at(i) / 100);
					currStats_.distDmg_ = currStats_.distDmg_ / (1 + valuePotion_.at(i) / 100);
					potionUsing_[2] = false;
					break;
				case (int)potionType::Crit:
					currStats_.crit_ -= valuePotion_.at(i);
					potionUsing_[3] = false;
					break;
				default:
					break;
				}
			}
		}
	}
}

void Player::updateDebuffs()
{
	//Slowed
	if (slowed_ && !slowTimeCD_.isCooldownActive())
	{
		currStats_.moveSpeed_ = currStats_.moveSpeed_ / (1 - slowEffect_);
		slowed_ = false;
	}
}

void Player::manaReg() {
	//Inicializa el cooldown sólo cuando el mana sea menor que el MAXMANA
	if (currStats_.mana_ < maxMana_ && initManaReg_) {
		manaCD_.initCooldown(MANA_REG_DELAY);
		initManaReg_ = false;
	}
	//Actualiza el cooldown
	if (manaCD_.isCooldownActive()) manaCD_.updateCooldown();
	else if(!initManaReg_){
		currStats_.mana_ += maxMana_ * (currStats_.manaReg_ / 100);
		if (currStats_.mana_ >= maxMana_) {
			currStats_.mana_ = maxMana_;
		}
		initManaReg_ = true;
	}
}

void Player::updateDir(Vector2D target)
{
	Vector2D visPos = getVisPos();
	dir_.setX(target.getX() - visPos.getX());
	dir_.setY(target.getY() - visPos.getY());
	dir_.normalize();
}

//Animaciones
void Player::animator()
{
	if (currState_ == STATE::SHOOTING) {
		shootAnim();
	}
	else if (currState_ == STATE::ATTACKING) {
		meleeAnim();
	}
	else if (currState_ == STATE::CHARGING_EMPOWERED) {
		empoweredAnim();
	}
}
	//Inits
void Player::initIdle()
{
	//Resteo los booleanos bussy
	bussy_ = false;
	meleeBussy_ = false;

	//Apaño para que deje de sonar al caminar
	if(currState_ == STATE::FOLLOWING)
		app_->getAudioManager()->playChannel(Resources::WalkAudio, 0, Resources::PlayerChannel1);
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initMove()
{
	if (SDL_GetTicks() - WALK_TIME > lastWalkSound_) {
		lastWalkSound_ = SDL_GetTicks();
		app_->getAudioManager()->playChannel(Resources::WalkAudio, -1, Resources::PlayerChannel1);
		app_->getAudioManager()->setChannelVolume(Resources::PlayerChannel1, 50);
	}
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];
	if (currState_ != STATE::FOLLOWING) {
		currState_ = STATE::FOLLOWING;
		frame_.x = 0; frame_.y = 0;
	}

	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initShoot()
{
	auto choice = app_->getRandom()->nextInt(Resources::Attack1, Resources::Attack6);
	app_->getAudioManager()->playChannel(choice, 0, Resources::PlayerChannel1);
	stop();
	currState_ = STATE::SHOOTING;	//Cambio de estado
	shooted_ = false;	//Aún no se ha creado la bala
	updateDirVisMouse();	//Hacia dónde mira
	texture_ = shootTx_[(int)currDir_];
	currAnim_ = shootAnims_[(int)currDir_];
	//Asigna el frame donde ocurrirá la acción
	switch (currDir_)
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

	shootCD_.initCooldown(currStats_.distRate_);

	if (clon_ != nullptr)clon_->initShoot(mousePos_);
}

void Player::initMelee()
{
	//Sonidos
	auto choice = app_->getRandom()->nextInt(Resources::Attack1, Resources::Attack6);
	app_->getAudioManager()->playChannel(choice, 0, Resources::PlayerChannel1);
	auto melee = app_->getRandom()->nextInt(Resources::SwordSound1, Resources::SwordSound6);
	app_->getAudioManager()->playChannel(melee, 0, Resources::PlayerChannel2);

	currState_ = STATE::ATTACKING;			//Cambio de estado
	attacked_ = false;						//Aún no se ha atacado
	meleeBussy_ = true;						//Para no inicializar otra vez el melee si se dan mas clicks
	updateDirVisObjective(currEnemy_);		//Hacia dónde está el enemigo
	texture_ = meleeTx_[(int)currDir_];		//Cambio de textura
	currAnim_ = meleeAnims_[(int)currDir_];	//Cambio de animacion

	//Frame exacto del ataque
	switch (currDir_)
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

	//Inicia cooldown
	meleeCD_.initCooldown(currStats_.meleeRate_);
}

void Player::initEmpowered()
{
	stop();
	bussy_ = true;
	//Apaño para que deje de sonar al caminar
	if (currState_ == STATE::FOLLOWING)
		app_->getAudioManager()->playChannel(Resources::WalkAudio, 0, Resources::PlayerChannel1);
	empoweredAct_ = true;
	currState_ = STATE::CHARGING_EMPOWERED;
	texture_ = empoweredTx_[(int)currDir_];
	currAnim_ = empoweredAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Player::initDie() {
	Actor::initDie();
	//Cargamos música de fondo
	app_->resetMusicChannels();
	app_->resetSoundsChannels();
	app_->getAudioManager()->playChannel(Resources::AudioId::FuneralTheme, -1, Resources::MainMusicChannel);
}

	//Managers
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
		if (currEnemy_ == nullptr) {
			attacking_ = false;
			dir_ = Vector2D(0, 0);
		}
		else {
			double totalDmg = currStats_.meleeDmg_;
			if (empoweredAct_) { //Golpe fuerte
				empoweredCD_.initCooldown(EMPOWERED_DELAY);
				empoweredAct_ = false;
				totalDmg = currStats_.meleeDmg_ * EMPOWERED_BONUS;
				static_cast<Enemy*>(currEnemy_)->receiveDamage((int)round(totalDmg));
			}
			else {
				if (applyCritic()) totalDmg *= 1.5;
				static_cast<Enemy*>(currEnemy_)->receiveDamage((int)round(totalDmg));
			}
		}

		//if (static_cast<Actor*>(currEnemy_)->getState() == STATE::DYING) attacking_ = false;
		attacked_ = true;
		empoweredInit_ = false;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();	//Activa el idle
	}
}

void Player::empoweredAnim()
{
	if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();
	}
}

void Player::dieAnim()
{
	if (currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {

		dead_ = true;
	}
}

//Input y sus dependencias
void Player::checkInputCheat(){
	if (eventHandler_->isKeyDown(SDL_SCANCODE_L) && !gm_->getOnShip() && !gm_->onTutorial()) {
		cheatPlayer();
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_K) && !gm_->getOnShip() && !gm_->onTutorial()) {
		list<Enemy*> enemies_ = dynamic_cast<PlayState*>(app_->getCurrState())->getListEnemies();
		for (auto it = enemies_.begin(); it != enemies_.end(); ++it) {
			app_->getCurrState()->removeRenderUpdateLists((*it));
		}
		dynamic_cast<PlayState*>(app_->getCurrState())->getListEnemies().clear();
	}
}

void Player::checkInput()
{
	//Skills
	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q) && skills_[0] != nullptr) {
		skills_[0]->action();
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_W) && skills_[1] != nullptr) {
		skills_[1]->action();
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_E) && skills_[2] != nullptr) {
		skills_[2]->action();
	}
	if (eventHandler_->isKeyDown(SDL_SCANCODE_R) && skills_[3] != nullptr) {
		skills_[3]->action();
	}

	//Pociones
	if ((!gm_->getOnShip() || gm_->onTutorial()) && eventHandler_->isKeyDown(SDLK_1) && potions_[0] != nullptr) {
		usePotion(potions_[0], 0);
		gm_->setObjectEquipped(ObjectName::Unequipped, Key::One);
	}
	if ((!gm_->getOnShip() || gm_->onTutorial()) && eventHandler_->isKeyDown(SDLK_2) && potions_[1] != nullptr) {
		usePotion(potions_[1], 1);
		gm_->setObjectEquipped(ObjectName::Unequipped, Key::Two);
	}

	//Grito
	if (eventHandler_->isKeyDown(SDL_SCANCODE_SPACE)) shout();

	//Disparo
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && !shootCD_.isCooldownActive()) {
		shootCD_.initCooldown(currStats_.distRate_);
		initShoot();
	}

	//Ataque/movimiento
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
	{
		Enemy* obj; obj = checkAttack();
		updateDirVisMouse();
		if (obj != nullptr) {
			if(!meleeBussy_) attack(obj);
		}
		else if (!getOnCollision()) {
			move(eventHandler_->getRelativeMousePos());
		}
		else setOnCollision(false);

		if (collisionCtrl_->isNextZoneTextBoxActive()) {
			getEndZoneTextBox()->updateButtons();
			changeZone_ = true;
		}
	}
}

void Player::checkInputState() {
	if (eventHandler_->isKeyDown(SDL_SCANCODE_P)) {
		app_->getGameStateMachine()->pushState(new PauseState(app_));
		stop();
	}
	else if (eventHandler_->isKeyDown(SDL_SCANCODE_C)) {
		app_->getGameStateMachine()->pushState(new Inventory(app_));
		stop();
	}
	else if (eventHandler_->isKeyDown(SDL_SCANCODE_V)) {
		app_->getGameStateMachine()->pushState(new SkillState(app_, this));
		stop();
	}
}

Enemy* Player::checkAttack() {
	bool found = false;
	Enemy* obj = nullptr;
	Vector2D mousePos = eventHandler_->getRelativeMousePos();
	SDL_Point mouse = { 0, 0 }; mouse.x =(int)round( mousePos.getX()); mouse.y =(int)round( mousePos.getY());
	list<Enemy*> enemies_ = dynamic_cast<PlayState*>(app_->getCurrState())->getListEnemies();
	for (auto it = enemies_.begin(); !found && it != enemies_.end(); ++it) {
		if (SDL_PointInRect(&mouse, &(*it)->getCollider())) {
			obj = (*it);
			found = true;
		}
	}
	return obj;
}

void Player::movementManager()
{
	Enemy* objective = static_cast<Enemy*>(currEnemy_);
	//Si no est� atacando se mueve a la posici�n indicada con un margen de 2 pixels
	Vector2D target = target_;
	if (attacking_ && objective != nullptr) {
		target = objective->getVisPos();
		updateDir(target);
	}
	else
		attacking_ = false;

	//Pies del player
	Vector2D visPos = getVisPos();
	//Para 
	list<Enemy*> enemiesInRange = collisionCtrl_->getEnemiesInArea(getCenter(), (int)round(currStats_.meleeRange_));
	//Movimiento hasta llegar al target 
	if ((visPos.getX() < target.getX() - 2		//Comprueba si se ha llegado
		|| visPos.getX() > target.getX() + 2
		|| visPos.getY() < target.getY() - 2
		|| visPos.getY() > target.getY() + 2)
		&&
		(!attacking_ || objective == nullptr || objective->getState() == STATE::DYING || enemiesInRange.empty()) && !bussy_)
	{
		double delta = app_->getDeltaTime();
		previousPos_ = pos_;
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
		//Al actualizarse aquí la cámara solo modificará la posición de los objetos del estado si existe un jugador
		if (!gm_->getOnShip() && !gm_->onTutorial()) Camera::instance()->updateCamera((int)round(pos_.getX() + scale_.getX() / 2),(int)round( pos_.getY() + scale_.getY() / 2));
	}
	//Cuando se llegue al target
	else {
		//Si se viene desde following se inicia el idle
		if (currState_ == STATE::FOLLOWING) initIdle();
		//Si se ha llegado al target y es un enemigo, estoy atacando
		if (attacking_ && objective != nullptr && objective->getState() != STATE::DYING && !enemiesInRange.empty() && !bussy_)
		{
			//Para cuando se llegue al target y cambiar de animacion
			if (currState_ == STATE::FOLLOWING) initIdle();
			bool found = false;
			for (auto it = enemiesInRange.begin(); !found && it != enemiesInRange.end(); ++it)
				if ((*it) == objective)
					found = true;

			if (found && empoweredAct_ && !empoweredInit_)
			{
				empoweredInit_ = true;
				app_->getAudioManager()->playChannel(Resources::EmpoweredSkillAudio, 0, Resources::PlayerChannel4);
				initMelee();
			}
			else if (found && !meleeCD_.isCooldownActive())
			{
				initMelee();
			}
		}
	}
}

void Player::shoot(Vector2D dir)
{
	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	equipType auxGunType = gun_->getEquipType();
	//Critico
	double realDamage = currStats_.distDmg_;
	if (applyCritic()) realDamage *= 1.25;
	if (auxGunType == equipType::PistolI || auxGunType == equipType::PistolII) {
		app_->getAudioManager()->playChannel(Resources::Pistol, 0, Resources::SoundChannels::PlayerChannel2);
		PlayerBullet* bullet = new PlayerBullet(app_, app_->getTextureManager()->getTexture(Resources::Bullet), shootPos, dir,
			realDamage, currStats_.distRange_, gun_->getBulletSpeed());

		//Activa perforación en la bala
		if (perforate_) {
			bullet->setPerforate(perforate_);
			perforate_ = false;
		}
		//Activa el rebote en la bala
		bullet->setRicochet(ricochetCD_.isCooldownActive());

		//Se añade a los bucles del juegos
		app_->getCurrState()->addRenderUpdateListsAsFirst(bullet);
		collisionCtrl_->addPlayerBullet(bullet);
	}
	else if (auxGunType == equipType::ShotgunI || auxGunType == equipType::ShotgunII) {
		app_->getAudioManager()->playChannel(Resources::Trabuco, 0, Resources::SoundChannels::PlayerChannel2);
		Blunderbuss* blunderbuss = new Blunderbuss(app_, app_->getTextureManager()->getTexture(Resources::Bullet), shootPos, dir,
			(int)round(realDamage), currStats_.distRange_, gun_->getBulletSpeed());
		if (perforate_) {
			blunderbuss->activatePerforate();
			perforate_ = false;
		}
		if (ricochetCD_.isCooldownActive()) {
			blunderbuss->activateRicochet();
		}
		app_->getCurrState()->addUpdateListAsFirst(blunderbuss);
	}

	if (clon_ != nullptr)
		clon_->shoot();
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

//Habilidades y pociones
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
	app_->getAudioManager()->playChannel(Resources::Drink, 0, Resources::PlayerChannel2);
	double auxValue = potion->getValue();
	switch (potion->getType())
	{
	case potionType::Health:
		currStats_.health_ += maxHealth_ * auxValue / 100;
		if (currStats_.health_ > maxHealth_) currStats_.health_ = maxHealth_;
		break;
	case potionType::Mana:
		currStats_.mana_ += maxMana_ * auxValue / 100;
		if (currStats_.mana_ > maxMana_) currStats_.mana_ = maxMana_;
		break;
	case potionType::Speed:
		if (!potionUsing_[0]) {
			if (slowed_) currStats_.moveSpeed_ += (auxValue * slowEffect_);
			else currStats_.moveSpeed_ += auxValue;
			potionUsing_[0] = true;
			valuePotion_[0] = auxValue;
		}
		lastTicksPotion_[0] = SDL_GetTicks();
		timerPotion_[0] = potion->getTime();	//Se resetea el tiempo de duración
		//Muestra la cuenta atras del tiempo de la pocion en el HUD, tambien le reestablece el tiempo si la poción vuelve a activarse
		gm_->getHUD()->showPotionHUD(0, potion->getTime(), timerPotion_[0]);
		break;
	case potionType::Armor:
		if (!potionUsing_[1]) {
			currStats_.armor_ += auxValue;
			potionUsing_[1] = true;
			valuePotion_[1] = auxValue;
		}
		lastTicksPotion_[1] = SDL_GetTicks();
		timerPotion_[1] = potion->getTime();	//Se resetea el tiempo de duración
		//Muestra la cuenta atras del tiempo de la pocion en el HUD, tambien le reestablece el tiempo si la poción vuelve a activarse
		gm_->getHUD()->showPotionHUD(1, potion->getTime(), timerPotion_[1]);
		break;
	case potionType::Damage:
		if (!potionUsing_[2]) {
			currStats_.meleeDmg_ = currStats_.meleeDmg_ * (1 + auxValue / 100);
			currStats_.distDmg_ = currStats_.distDmg_ * (1 + auxValue / 100);
			potionUsing_[2] = true;
			valuePotion_[2] = auxValue;
		}
		lastTicksPotion_[2] = SDL_GetTicks();
		timerPotion_[2] = potion->getTime();	//Se resetea el tiempo de duración
		//Muestra la cuenta atras del tiempo de la pocion en el HUD, tambien le reestablece el tiempo si la poción vuelve a activarse
		gm_->getHUD()->showPotionHUD(2, potion->getTime(), timerPotion_[2]);
		break;
	case potionType::Crit:
		if (!potionUsing_[3]) {
			currStats_.crit_ += auxValue;
			potionUsing_[3] = true;
			valuePotion_[3] = auxValue;
		}
		lastTicksPotion_[3] = SDL_GetTicks();
		timerPotion_[3] = potion->getTime();	//Se resetea el tiempo de duración
		//Muestra la cuenta atras del tiempo de la pocion en el HUD, tambien le reestablece el tiempo si la poción vuelve a activarse
		gm_->getHUD()->showPotionHUD(3, potion->getTime(), timerPotion_[3]);
		break;
	}
	delete potion;
	//app_->getCurrState()->addUpdateList(potion);
	potions_[key] = nullptr;
	gm_->setPotion(key, nullptr);
}

void Player::createClon()
{
	auto choice = app_->getRandom()->nextInt(Resources::Laugh1, Resources::Laugh7);
	app_->getAudioManager()->playChannel(choice, 0, Resources::PlayerChannel2);
	Vector2D pos;
	pos.setX(eventHandler_->getRelativeMousePos().getX() - (scale_.getX() / 2));
	pos.setY(eventHandler_->getRelativeMousePos().getY() - (scale_.getY() * 0.8));
	clon_ = new Clon(app_, pos, scale_, this);
	app_->getGameStateMachine()->getState()->addRenderUpdateLists(clon_);
}

bool Player::killClon()
{
	if (clon_ != nullptr) {
		clon_->die();
		clon_ = nullptr;
		return true;
	}
	else return false;
}

//Otros
void Player::cheatPlayer()
{
	if (!cheat_) {
		cheat_ = true;
		cout << "CHEAT ACTIVE" << endl;
		maxHealth_ += healthCheat_;
		currStats_.health_ = maxHealth_;
		currStats_.manaReg_ += manaRegCheat_;	
		currStats_.armor_ += armorCheat_;			
		currStats_.meleeDmg_ += meleeDamageCheat_;	
		currStats_.distDmg_ += distDmgCheat_;		
		currStats_.crit_ += critCheat_;			
		currStats_.distRange_ += distRangeCheat_;		
		currStats_.moveSpeed_ += moveSpeedCheat_;
		collisionCtrl_->setPlayer(nullptr);
	}
	else {
		cheat_ = false;
		cout << "CHEAT DESACTIVE" << endl;
		maxHealth_ -= healthCheat_;
		currStats_.health_ = maxHealth_;
		currStats_.manaReg_ -= manaRegCheat_;
		currStats_.armor_ -= armorCheat_;
		currStats_.meleeDmg_ -= meleeDamageCheat_;
		currStats_.distDmg_ -= distDmgCheat_;
		currStats_.crit_ -= critCheat_;
		currStats_.distRange_ -= distRangeCheat_;
		currStats_.moveSpeed_ -= moveSpeedCheat_;
		collisionCtrl_->setPlayer(this);
	}
}

void Player::shout()
{
	auto choice = app_->getRandom()->nextInt(Resources::jarl1, Resources::jarl11 + 1);
	app_->getAudioManager()->playChannel(choice, 0, Resources::JarlChannel);
}

void Player::feedBackHurtSounds()
{
	auto choice = app_->getRandom()->nextInt(Resources::Hurt1, Resources::Hurt4 + 1);
	app_->getAudioManager()->playChannel(choice, 0, Resources::SoundChannels::PlayerChannel3);
}

void Player::displace(Vector2D dir, int dist)
{
	pos_.setX(pos_.getX() + (dir.getX() * dist));
	pos_.setY(pos_.getY() + (dir.getY() * dist));
	stop();
}

void Player::applySlow(double effect, double duration)
{
	if (!slowed_)
	{
		currStats_.moveSpeed_ -= currStats_.moveSpeed_ * effect;
		slowEffect_ = effect;
	}
	else if (slowed_ && effect > slowEffect_)
	{
		currStats_.moveSpeed_ = currStats_.moveSpeed_ / (1 - slowEffect_);
		currStats_.moveSpeed_ -= currStats_.moveSpeed_ * effect;
		slowEffect_ = effect;
	}

	slowed_ = true;
	slowTimeCD_.initCooldown(duration);
}

void Player::isEnemyDead(Actor* obj)
{
	if (obj == currEnemy_) {
		attacking_ = false;
		currEnemy_ = nullptr;
	}
}
void Player:: setSkillAt(int key, Skill* skill) {
	if (skills_[key] != nullptr)delete skills_[key];
	skills_[key] = skill;
}