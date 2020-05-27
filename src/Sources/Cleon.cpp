#include "Cleon.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "Player.h"
#include "Collisions.h"

//channel 1 interacciones
//		  2 bloqueo y melee
//		  3 risa
//		  4 movimiento

bool Cleon::update() {
	//ESTADOS A TENER EN CUENTA ->THRUSTINg(estocada), CHARGING(carga), CHARGING_EMPOWERED(barrido)
	DIR lastDir_ = currDir_;
	updateFrame();
	manageTint();
	updateCooldowns();
	updateDirVisObjective(currEnemy_);

	//si Cleon muere
	if (currState_ == STATE::DYING) {
		app_->getAudioManager()->playChannel(Resources::CleonDie, 0, Resources::CleonChannel1);
		applyRewards();
		CollisionCtrl::instance()->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return false;
	}
	//Si Cle�n encuentra un enemigo
	if ((currState_ == STATE::IDLE || currState_ == STATE::FOLLOWING) && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si estoy en modo ataque
	if (currState_ == STATE::ATTACKING) {
		createBarrel();
		//Si est� a rango de melee
		if (onRange(currStats_.meleeRange_) && !lastThrust_.isCooldownActive()) {
			updateDirVisObjective(currEnemy_);
			initThrust();
			stop();
		}
		else if (onRange(currStats_.meleeRange_) && !lastSweep_.isCooldownActive()) initSwept();
		else if (onRange(CHARGE_RANGE) && !lastCharge_.isCooldownActive()) initCharge();
		else {
			if (lastDir_ != currDir_) {
				cout << "init run atacking \n";
				initRun();
			}
			else selectTarget();
		}
	}
	if (currState_ == STATE::CHARGING) {
		SDL_Rect targetRect = { (int)round(chargePoint_.getX()),(int)round(chargePoint_.getY()),25,25 };
		//Cle�n llego al destino de su carga
		if (SDL_HasIntersection(&getDestiny(), &targetRect) ) {
			cout << "LLEGA A DESTINO \n";
			auto currEnemy = dynamic_cast<Player*>(currEnemy_);
			//Si Cle�n colisiona contra el player
			if (currEnemy != nullptr && SDL_HasIntersection(&getDestiny(), &currEnemy->getDestiny()) && !attacked_) {
				cout << "CHOCA PLAYER \n";
				double realDamage = CHARGE_DMG;
				if (applyCritic()) realDamage *= 1.5;
				currEnemy->receiveDamage(realDamage);
				combo();
				attacked_ = true;
			}
			currState_ = STATE::IDLE;
			currStats_.moveSpeed_ = MOVE_SPEED;
		}

	}
	
	if (currState_ == STATE::THRUSTING)thrustAnim();
	//Si el Cleon está en barrido
	else if (currState_ == STATE::CHARGING_EMPOWERED)sweptAnim();
	//Si Cle�n no está todavía en following y no está en carga o en cualquier otro estado de ataque
	else if (currState_ == STATE::IDLE) initRun();
	//El estado es following
	else {
		if (lastDir_ != currDir_) {
			cout << "init run following \n";
			initRun();
		}
		else selectTarget();
	}

	if (!walkTime_.isCooldownActive() && currState_ == STATE::ATTACKING) {
		walkTime_.initCooldown(WALK_TIME);
		app_->getAudioManager()->playChannel(Resources::CleonWalk, 0, Resources::CleonChannel4);
	}
	else if (currState_ != STATE::ATTACKING) {
		app_->getAudioManager()->haltChannel(Resources::CleonChannel4);
	}

	if (!iteraction_.isCooldownActive()) {
		iteraction_.initCooldown(ITER_TIME);
		auto choice = app_->getRandom()->nextInt(Resources::CleonInter1, Resources::CleonInter7 + 1);
		app_->getAudioManager()->playChannel(choice, 0, Resources::CleonChannel1);
		app_->getAudioManager()->haltChannel(Resources::CleonChannel3);
		app_->getAudioManager()->haltChannel(Resources::CleonChannel5);
	}
	cout << "FIN UPDATE \n";
	return false;
}

void Cleon::onCollider()
{

}

void Cleon::receiveDamage(double damage)
{
	if (!activeBlock()) {
		lastTint_ = SDL_GetTicks();
		feedBackHurtSounds();
		//Reduccion de da�o
		/*auto choice = app_->getRandom()->nextInt(Resources::CleonHurt1, Resources::CleonHurt4 + 1);
		app_->getAudioManager()->playChannel(choice, 0, Resources::CleonChannel1);*/
		double realDamage = damage - (damage * currStats_.armor_ / 100);
		currStats_.health_ -= realDamage;
		if (currStats_.health_ <= 0) {
			this->die();
		}
	}
	else
	{
		app_->getAudioManager()->playChannel(Resources::CleonBlock, 0 , Resources::CleonChannel2);
		if (!laugh_.isCooldownActive()) {
			laugh_.initCooldown(LAUGH_TIME);
			app_->getAudioManager()->setChannelVolume(10, Resources::CleonChannel3);
			app_->getAudioManager()->playChannel(Resources::CleonLaugh, 0, Resources::CleonChannel3);
		}
	}
}

void Cleon::lostAggro()
{
	initIdle();
	if (!laugh_.isCooldownActive()) {
		laugh_.initCooldown(LAUGH_TIME);
		app_->getAudioManager()->setChannelVolume(10, Resources::CleonChannel3);
		app_->getAudioManager()->playChannel(Resources::CleonLaugh, 0, Resources::CleonChannel3);
	}
	auto newEnemy = static_cast<GameObject*>(player_);
	currEnemy_ = newEnemy;
	currStats_.moveSpeed_ = movSpeed_;
}

void Cleon::thrust()
{
	auto meleeSound = app_->getRandom()->nextInt(Resources::CleonSword1, Resources::CleonSword4 + 1);
	app_->getAudioManager()->playChannel(meleeSound, 0, Resources::CleonChannel2);
	lastThrust_.initCooldown(THRUST_TIME);
	if (!attacked_) {
		cout << currAnim_.currFrame_ << endl;
		attacked_ = true;
		auto thrustAttack = dynamic_cast<Player*>(currEnemy_);
		if (thrustAttack) {

			//Critico
			double realDamage = currStats_.meleeDmg_;
			if (applyCritic()) realDamage *= 1.5;

			thrustAttack->receiveDamage(realDamage);
		}
	}
}

void Cleon::combo() {
	initThrust();
	lastSweep_.endCoolDown();
}

void Cleon::pirateCharge()
{
	lastCharge_.initCooldown(CHARGE_TIME);
	chargePoint_ = currEnemy_->getCenter();
	currStats_.moveSpeed_ = CHARGE_SPEED;

	Barrel* currBarrel = new Barrel(app_, pos_, Vector2D(BARREL_W, BARREL_H), this);
	CollisionCtrl::instance()->addBarrel(currBarrel);
	app_->getCurrState()->addRenderUpdateListsAsFirst(currBarrel);
	barrelsInGame++;
}

void Cleon::swept()
{
	lastSweep_.initCooldown(SWEEP_TIME);
	if (!attacked_) {
		auto sweepAttack = dynamic_cast<Player*>(currEnemy_);
		if (sweepAttack) {
			sweepAttack->receiveDamage(currStats_.meleeDmg_);
		}
		attacked_ = true;
	}
}

void Cleon::createBarrel()
{
	if (barrelsInGame < NUM_MAX_BARREL && !lastBarrel_.isCooldownActive()) {
		lastBarrel_.initCooldown(BARREL_CREATOR);
		auto barrilSound = app_->getRandom()->nextInt(0, 7);
		if (barrilSound == 6) {
			app_->getAudioManager()->setChannelVolume(10, Resources::CleonChannel5);
			app_->getAudioManager()->playChannel(Resources::CleonBarril, 0, Resources::CleonChannel5);
		}
		auto chance = app_->getRandom()->nextInt(0, BARREL_CHANCE + 1);
		if (chance == BARREL_CHANCE) {
			Barrel* currBarrel = new Barrel(app_, pos_, Vector2D(BARREL_W, BARREL_H), this);
			CollisionCtrl::instance()->addBarrel(currBarrel);
			app_->getCurrState()->addRenderUpdateListsAsFirst(currBarrel);
			barrelsInGame++;
		}
	}
}

void Cleon::initialStats()
{
	rangeVision_ = 500;
	HEALTH = 4000;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 20;
	DIST_DMG = 300;
	CRIT = 10;
	MELEE_RANGE = 50;
	DIST_RANGE = 350;
	MOVE_SPEED = 50;
	MELEE_RATE = 1;
	DIST_RATE = 2500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Cleon::initObject() {
	CollisionCtrl::instance()->addEnemy(this);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initialStats();
	initRewards();
	initAnims();
	initIdle();
	player_ = GameManager::instance()->getPlayer();
	tag_ = "Cleon";
}

void Cleon::initRewards()
{
	//Poner lo que dropea Cle�n
}

void Cleon::initAnims() {
	//DIR{up right down left}
	//idle
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonIdleUp));
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonIdleRight));
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonIdleDown));
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonIdleLeft));

	//movimiento
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_UD, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_RUN_UD, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMovUp));
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_RUN_RL, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMovRight));
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_UD, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_RUN_UD, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMovDown));
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_RUN_RL, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMovLeft));

	//estocada
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_UD, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_MELEE_UD, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMelUp));
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_MELEE_RL, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMelRight));
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_UD, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_MELEE_UD, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMelDown));
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_MELEE_RL, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonMelLeft));

	//barrido
	sweptAnim_.push_back(Anim(NUM_FRAMES_SWEPT_UP, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_SWEPT_UP, false));
	sweptTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonSweptUp));
	sweptAnim_.push_back(Anim(NUM_FRAMES_SWEPT_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_SWEPT_RL, false));
	sweptTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonSweptRight));
	sweptAnim_.push_back(Anim(NUM_FRAMES_SWEPT_DOWN, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_SWEPT_DOWN, false));
	sweptTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonSweptDown));
	sweptAnim_.push_back(Anim(NUM_FRAMES_SWEPT_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_SWEPT_RL, false));
	sweptTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonSweptLeft));

	//carga
	chargeAnim_.push_back(Anim(NUM_FRAMES_CHARGE_UD, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_CHARGE_UD, false));
	chargeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonChargeUp));
	chargeAnim_.push_back(Anim(NUM_FRAMES_CHARGE_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_CHARGE_RL, false));
	chargeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonChargeRight));
	chargeAnim_.push_back(Anim(NUM_FRAMES_CHARGE_UD, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_CHARGE_UD, false));
	chargeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonChargeDown));
	chargeAnim_.push_back(Anim(NUM_FRAMES_CHARGE_RL, W_FRAME_CLEON, H_FRAME_CLEON, FRAME_RATE_CHARGE_RL, false));
	chargeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CleonChargeLeft));

}

void Cleon::updateCooldowns()
{
	if (lastThrust_.isCooldownActive()) lastThrust_.updateCooldown();
	if (lastCharge_.isCooldownActive()) lastCharge_.updateCooldown();//
	if (lastBarrel_.isCooldownActive()) lastBarrel_.updateCooldown();
	if (lastSweep_.isCooldownActive())lastSweep_.updateCooldown();
	if (walkTime_.isCooldownActive())walkTime_.updateCooldown();
	if (iteraction_.isCooldownActive())iteraction_.updateCooldown();
	if (laugh_.isCooldownActive())laugh_.updateCooldown();
}

void Cleon::move(Point2D target)
{

	dir_.setVec(target_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}

void Cleon::selectTarget()
{
	if (currEnemy_ != nullptr) {

		if (!Physics::PointBall((float)currEnemy_->getCenter().getX(), (float)currEnemy_->getCenter().getY(), 
			(float)getCenter().getX(), (float)getCenter().getY(), currStats_.meleeRange_)) {
			target_ = currEnemy_->getCenter() /*+ offset*/;
			move(currEnemy_->getCenter());
			updateDirVisObjective(currEnemy_);
		}
		else initIdle();
	}
}

void Cleon::initIdle() {
	int dir = (int)currDir_;
	texture_ = idleTxt_[dir];
	currAnim_ = idleAnim_[dir];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
	currState_ = STATE::IDLE;
}

void Cleon::initSwept()
{
	auto meleeSound = app_->getRandom()->nextInt(Resources::CleonSword1, Resources::CleonSword4 + 1);
	app_->getAudioManager()->playChannel(meleeSound, 0, Resources::CleonChannel2);
	lastSweep_.initCooldown(SWEEP_TIME);
	currState_ = STATE::CHARGING_EMPOWERED;
	int dir = (int)currDir_;
	attacked_ = false;
	texture_ = sweptTxt_[dir];
	currAnim_ = sweptAnim_[dir];
	switch (currDir_)
	{
	case DIR::UP:
		frameAction_ = 3;
		break;
	case DIR::RIGHT:
		frameAction_ = 3;
		break;
	case DIR::DOWN:
		frameAction_ = 5;
		break;
	case DIR::LEFT:
		frameAction_ = 3;
		break;
	default:
		break;
	}
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Cleon::initThrust() {
	auto meleeSound = app_->getRandom()->nextInt(Resources::CleonSword1, Resources::CleonSword4 + 1);
	app_->getAudioManager()->playChannel(meleeSound, 0, Resources::CleonChannel2);
	currState_ = STATE::THRUSTING;
	attacked_ = false;
	switch (currDir_)
	{
	case DIR::UP:
		frameAction_ = 5;
		break;
	case DIR::RIGHT:
		frameAction_ = 6;
		break;
	case DIR::DOWN:
		frameAction_ = 5;
		break;
	case DIR::LEFT:
		frameAction_ = 6;
		break;
	default:
		break;
	}
	int dir = (int)currDir_;
	texture_ = meleeTxt_[dir];
	currAnim_ = meleeAnim_[dir];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Cleon::initRun() {
	int dir = (int)currDir_;
	texture_ = runTxt_[dir];
	currAnim_ = runAnim_[dir];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Cleon::initCharge() {
	selectTarget();
	app_->getAudioManager()->playChannel(Resources::CleonCharge, 0, Resources::CleonChannel2);
	currState_ = STATE::CHARGING;
	int dir = (int)currDir_;
	attacked_ = false;
	texture_ = chargeTxt_[dir];
	currAnim_ = chargeAnim_[dir];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	pirateCharge();
}

void Cleon::thrustAnim()
{
	if (currAnim_.currFrame_ == frameAction_) thrust();
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_-1) initIdle();

}

void Cleon::sweptAnim()
{
	if (currAnim_.currFrame_ == frameAction_) swept();
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) initIdle();
}
