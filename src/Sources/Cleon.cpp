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

	//si Cleón palma
	if (currState_ == STATE::DYING) {
		applyRewards();
		CollisionCtrl::instance()->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return false;
	}
	//Si Cleón encuentra un enemigo
	if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si estoy en modo ataque
	if (currState_ == STATE::ATTACKING) {
		//Si está a rango de melee
		if (onRange(currStats_.meleeRange_) && !lastThrust_.isCooldownActive()) {
			//Estocada
			thrust();
		}
		//Sí está a rango de carga
		else if (onRange(CHARGE_RANGE) && !lastCharge_.isCooldownActive()) {
			//Carga
			pirateCharge();
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
					currEnemy->receiveDamage(CHARGE_DMG);
				}
				currState_ = STATE::ATTACKING;
				currStats_.moveSpeed_ = movSpeed_;
			}
	}
	//Si Cleón está siguiendo a un enemigo
	if (currState_ == STATE::FOLLOWING) {
		selectTarget();
		if (onRange(CHARGE_RANGE) || onRange(currStats_.meleeRange_)) {
			currState_ = STATE::ATTACKING;
		}
	}

	return false;
}

void Cleon::onCollider()
{
	
}


void Cleon::receiveDamage(int damage)
{
	if (!activeBlock()) {
		lastTint_ = SDL_GetTicks();
		feedBackHurtSounds();
		currStats_.health_ -= damage;
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
		thrustAttack->receiveDamage(currStats_.meleeDmg_);
	}
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
	texture_ = app_->getTextureManager()->getTexture(Resources::Cleon);
	CollisionCtrl::instance()->addEnemy(this);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initialStats();
	initRewards();
	initAnims();
	player_ = GameManager::instance()->getPlayer();
	tag_ = "Cleon";
}

void Cleon::initRewards()
{
	//Poner lo que dropea Cleón
}

void Cleon::initAnims() {
	idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true);
	runAnim_ = Anim(NUM_FRAMES_RUN, W_FRAME_RUN, H_FRAME_RUN, FRAME_RATE_RUN, true);
	assaultAnim_ = Anim(NUM_FRAMES_ASSAULT, W_FRAME_ASSAULT, H_FRAME_ASSAULT, FRAME_RATE_ASSAULT, false);
	meleeAnim_ = Anim(NUM_FRAMES_MELEE, W_FRAME_MELEE, H_FRAME_MELEE, FRAME_RATE_MELEE, false);
	barrelAnim_ = Anim(NUM_FRAMES_BARREL, W_FRAME_BARREL, H_FRAME_BARREL, FRAME_RATE_BARREL, false);
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
	}
}

