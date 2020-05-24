#include "Cleon.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "Player.h"


bool Cleon::update() {
	//string state;
	//switch (currState_)
	//{
	//case STATE::ATTACKING:
	//	state = "atacando";
	//	break;
	//case STATE::CHARGING:
	//	state = "cargando";
	//	break;
	//case STATE::DYING:
	//	state = "muriendo";
	//	break;
	//case STATE::FOLLOWING:
	//	state = "siguiendo";
	//	break;
	//case STATE::IDLE:
	//	state = "parado";
	//	break;
	//case STATE::PATROLLING:
	//	state = "patrullando";
	//	break;
	//default:
	//	break;
	//}
	//cout << state << endl;
	updateFrame();
	manageTint();
	updateCooldowns();
	STATE atStart = currState_;
	DIR dirStart = currDir_;
	//si Cleón palma
	if (currState_ == STATE::DYING) {
		applyRewards();
		CollisionCtrl::instance()->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return false;
	}
	//Si Cleón encuentra un enemigo
	if ((currState_ == STATE::IDLE||currState_==STATE::FOLLOWING) && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si estoy en modo ataque
	if (currState_ == STATE::ATTACKING ) {
		//Si está a rango de melee
		if (onRange(currStats_.meleeRange_) && !lastThrust_.isCooldownActive()) {
			//Estocada
			thrust();
			stop();
			updateDirVisObjective(currEnemy_);
			if (atStart != currState_ || dirStart != currDir_)  initMelee();
		}
		//Sí está a rango de carga
		else if (onRange(CHARGE_RANGE) && !lastCharge_.isCooldownActive()) {
			//Carga
			pirateCharge();
			//if (atStart != currState_ || dirStart != currDir_) inicia carga;
		}
		//Cleón no tiene a nadie a rango
		else
		{
			currState_ = STATE::FOLLOWING;
		}
	}
	if (currState_ == STATE::CHARGING) {
		selectTarget();
		SDL_Rect targetRect = { target_.getX(),target_.getY(),25,25 };
			//Cleón llego al destino de su carga
			if (SDL_HasIntersection(&getDestiny(), &targetRect)) {
				auto currEnemy = dynamic_cast<Player*>(currEnemy_);
				//Si Cleón colisiona contra el player
				if (currEnemy && SDL_HasIntersection(&getDestiny(), &currEnemy->getDestiny())) {
					double realDamage = CHARGE_DMG;
					if (applyCritic()) realDamage *= 1.5;
					currEnemy->receiveDamage(realDamage);
				}
				currState_ = STATE::ATTACKING;
				currStats_.moveSpeed_ = movSpeed_;
			}
	}
	//Si Cleón está siguiendo a un enemigo
	if (currState_ == STATE::FOLLOWING) {
		selectTarget();

		if (atStart != currState_||dirStart!=currDir_) initRun();
		bool x = atStart != currState_,y= dirStart != currDir_;
		cout <<"x" <<x << boolalpha << endl;
		cout <<"y" <<y << boolalpha<<endl;
		if (!getEnemy(rangeVision_) /*|| onRange(currStats_.meleeRange_)*/) {
			//currState_ = STATE::IDLE;
		}
	}
//#pragma region ParaProbarIdle
//#ifdef _DEBUG
//	if (!getEnemy(rangeVision_+200)) {
//		if (atStart != currState_ || dirStart != currDir_) initIdle();
//	}
//#endif // _DEBUG

//#pragma endregion
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
		//Reduccion de daño
		double realDamage = damage - (damage * currStats_.armor_ / 100);
		currStats_.health_ -= realDamage;
		if (currStats_.health_ <= 0) {
			this->die();
		}
	}
	else
	{
		cout << "BLOQUEADO! \n";
		//Poner feedback del bloqueo de Cleón
	}
}

void Cleon::lostAggro()
{
	auto newEnemy = static_cast<GameObject*>(player_);
	currEnemy_ = newEnemy;
}

void Cleon::thrust()
{
	cout << "ESTOCADA! \n";
	lastThrust_.initCooldown(THRUST_TIME);
	auto thrustAttack = dynamic_cast<Player*>(currEnemy_);
	if (thrustAttack) {
		//Critico
		double realDamage = currStats_.meleeDmg_;
		if (applyCritic()) realDamage *= 1.5;

		thrustAttack->receiveDamage(realDamage);
	}
	//Para probar animacion estocada desmutear lo de abajo
	//currState_=STATE::PATROLLING;
}

void Cleon::pirateCharge()
{
	cout << "CARGA! \n";
	lastCharge_.initCooldown(CHARGE_TIME);
	target_ = player_->getCenter();
	movSpeed_ = currStats_.moveSpeed_;
	currStats_.moveSpeed_ = CHARGE_SPEED;
	currState_ = STATE::CHARGING;

}

void Cleon::initialStats()
{
	rangeVision_ = 300;
	HEALTH = 4000;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 20;
	DIST_DMG = 300;
	CRIT = 0;
	MELEE_RANGE = 50;
	DIST_RANGE = 350;
	MOVE_SPEED = 100;
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
	//Poner lo que dropea Cleón
}

void Cleon::initAnims() {
	//DIR{up right down left}
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonIdleUp)) ;
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonIdleRight));
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonIdleDown));
	idleAnim_.push_back(Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true));
	idleTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonIdleLeft));

	runAnim_.push_back(Anim(NUM_FRAMES_RUN_UD, W_FRAME_RUN_UD, H_FRAME_RUN_UD, FRAME_RATE_RUN_UD, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMovUp));
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_RL, W_FRAME_RUN_RL, H_FRAME_RUN_RL, FRAME_RATE_RUN_RL, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMovRight));
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_UD, W_FRAME_RUN_UD, H_FRAME_RUN_UD, FRAME_RATE_RUN_UD, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMovDown));
	runAnim_.push_back(Anim(NUM_FRAMES_RUN_RL, W_FRAME_RUN_RL, H_FRAME_RUN_RL, FRAME_RATE_RUN_RL, true));
	runTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMovLeft));

	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_UD, W_FRAME_MELEE_UD, H_FRAME_MELEE_UD, FRAME_RATE_MELEE_UD, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMelUp));
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_RL, W_FRAME_MELEE_RL, H_FRAME_MELEE_RL, FRAME_RATE_MELEE_RL, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMelRight));
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_UD, W_FRAME_MELEE_UD, H_FRAME_MELEE_UD, FRAME_RATE_MELEE_UD, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMelDown));
	meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE_RL, W_FRAME_MELEE_RL, H_FRAME_MELEE_RL, FRAME_RATE_MELEE_RL, false));
	meleeTxt_.push_back(app_->getTextureManager()->getTexture(Resources::CLeonMelLeft));
	//runAnim_.push_back(Anim(NUM_FRAMES_RUN, W_FRAME_RUN, H_FRAME_RUN, FRAME_RATE_RUN, true));
	//assaultAnim_.push_back( Anim(NUM_FRAMES_ASSAULT, W_FRAME_ASSAULT, H_FRAME_ASSAULT, FRAME_RATE_ASSAULT, false));
	//meleeAnim_.push_back(Anim(NUM_FRAMES_MELEE, W_FRAME_MELEE, H_FRAME_MELEE, FRAME_RATE_MELEE, false));
	//barrelAnim_.push_back( Anim(NUM_FRAMES_BARREL, W_FRAME_BARREL, H_FRAME_BARREL, FRAME_RATE_BARREL, false));
}

void Cleon::updateCooldowns()
{
	if (lastThrust_.isCooldownActive()) lastThrust_.updateCooldown();
	if (lastCharge_.isCooldownActive()) lastCharge_.updateCooldown();
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
		target_ = currEnemy_->getCenter();
		move(currEnemy_->getCenter());
		updateDirVisObjective(currEnemy_);
	}
}

void Cleon::initIdle() {
	int dir = (int)currDir_;
	texture_ = idleTxt_[dir];
	currAnim_ = idleAnim_[dir];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
void Cleon:: initMelee(){
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
void Cleon::initBarrel() {}

void Cleon::initCharge() {}