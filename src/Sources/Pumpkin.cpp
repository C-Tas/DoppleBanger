#include "Pumpkin.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "Collisions.h"
#include "PlayState.h"

bool Pumpkin::onDistRange() {
	if (currEnemy_ != nullptr) {
		Point2D center = getCenter();
		Point2D currEnemyCenter = currEnemy_->getCenter();
		if (RectBall((float)round(currEnemyCenter.getX()), (float)round(currEnemyCenter.getY()), (float)round(currEnemy_->getScaleX()), (float)round(currEnemy_->getScaleY()),
			(float)center.getX(), (float)center.getY(), (float)currStats_.distRange_))
		{
			return true;
		}
		else return false;
	}
	else
	{
		return false;
	}
}
bool Pumpkin::onMeleeRange() {
	if (currEnemy_ != nullptr) {
		Point2D center = getCenter();
		Point2D currEnemyCenter = currEnemy_->getCenter();
		if (RectBall((float)currEnemyCenter.getX(), (float)currEnemyCenter.getY(), (float)currEnemy_->getScaleX(), (float)currEnemy_->getScaleY(),
			(float)center.getX(), (float)center.getY(), (float)currStats_.meleeRange_)) {
			return true;
		}
		else return false;
	}
	else
	{
		return false;
	}
}
bool Pumpkin::update() {
#ifdef _DEBUG

#endif // _DEBUG

	updateFrame();
	updateCooldowns();

	//Si la calabaza ha muerto
	if (currState_ == STATE::DYING) {

		if (currAnim_.currFrame_ == 0) {
			initExplosion();
		}
		applyRewards();
		return explosionAnim();
	}
	if (currState_ == STATE::IDLE) {
		if (currAnim_.currFrame_ == LAUGH_FRAME) {
			auto posi = app_->getRandom()->nextInt(0, 18);
			if (posi >= 17) {
				auto laughChoice = app_->getRandom()->nextInt(Resources::LaughPumpkin1, Resources::LaughPumpkin3 + 1);
				app_->getAudioManager()->playChannel(laughChoice, 0, Resources::PumpkinChannel1);
			}
		}
		else if (currAnim_.currFrame_ == IDLE_FRAME) {
			auto posi = app_->getRandom()->nextInt(0, 13);
			if (posi >= 12) {
				auto choice = app_->getRandom()->nextInt(Resources::IdlePumpkin1, Resources::IdlePumpkin2 + 1);
				app_->getAudioManager()->playChannel(choice, 0, Resources::PumpkinChannel2);
			}
		}
	}
	//Si la calabaza no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo m�s cercano
	if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
		app_->getAudioManager()->playChannel(Resources::AgroPumpkin, 0, Resources::PumpkinChannel1);
		initAttack();
	}
	//Si la calabaza tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING) {
		//Si la calabaza tiene un enemigo y lo tiene a rango
		if (onMeleeRange()) {
			initMove();
		}
		else {
			if (onDistRange() && !shootCD_.isCooldownActive()) {
				shootAnim();
			}
			//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
			else if (getEnemy(rangeVision_) && !shootCD_.isCooldownActive())
			{
				shootAnim();
			}
			//Tengo enemigo pero no a rango
			else
			{
				initIdle();
				currEnemy_ = nullptr;
			}
		}
	}
	if (currState_ == STATE::FOLLOWING) {
		follow();
	}
	return false;
}
void Pumpkin::disAttack() {
	app_->getAudioManager()->playChannel(Resources::AttackPumpkin, 0, Resources::PumpkinChannel1); 
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	//Critico
	double realDamage = currStats_.distDmg_;
	if (applyCritic()) realDamage *= 1.5;

	Bullet* seed = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(), dir, realDamage, seedLife, seedVel, Vector2D(wHSeed, wHSeed));
	app_->getCurrState()->addRenderUpdateListsAsFirst(seed);
	CollisionCtrl::instance()->addEnemyBullet(seed);
}
void Pumpkin::follow() {
	if (currEnemy_ != nullptr) {
		move(currEnemy_->getCenter());
		auto dirAux = currDir_;
		updateDirVisEnemy();
		if (currDir_ != dirAux) {
			initMove();
		}
	}
	else {
		initExplosion();
	}
}
void Pumpkin::initObject() {
	Enemy::initObject();
	initRewards();
	target_ = pos_;
	explosionRange_ = getScaleX();
}
void Pumpkin::lostAgro()
{
	currEnemy_ = nullptr;
}
void Pumpkin::initialStats()
{
	rangeVision_ = 350;
	HEALTH = 800;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 0;
	MELEE_DMG = 650;
	DIST_DMG = 120;
	CRIT = 0;
	MELEE_RANGE = 50;
	DIST_RANGE = 1200;
	MOVE_SPEED = 400;
	MELEE_RATE = 0;
	DIST_RATE = 1500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}
void Pumpkin::move(Point2D posToReach) {
	if ((getCenter() - target_).magnitude() <= 0.05)
	{
		pathPos_ = { (int)PosToTile(target_).getX(), (int)PosToTile(target_).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(posToReach).getX(), (int)PosToTile(posToReach).getY() }, pathPos_);
		if (pathing_.size() > 1)
			target_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
	}
	dir_.setVec(target_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}
void Pumpkin::initAnims()
{
	//Animaci�n de idle
		//Arriba
	idleAnims_.push_back(Anim(IDLE_U_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, IDLE_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinIdleUpAnim));
	//Derecha																						
	idleAnims_.push_back(Anim(IDLE_R_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, IDLE_R_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinIdleRightAnim));
	//Abajo																							
	idleAnims_.push_back(Anim(IDLE_D_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, IDLE_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinIdleDownAnim));
	//Izquierda																						
	idleAnims_.push_back(Anim(IDLE_L_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, IDLE_L_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinIdleLeftAnim));

	//Animaci�n de ataque
		//Arriba
	attackAnims_.push_back(Anim(ATTACK_U_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, ATTACK_U_FRAME_RATE, false));
	attackTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinAttackUpAnim));
	//Derecha																						
	attackAnims_.push_back(Anim(ATTACK_R_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, ATTACK_R_FRAME_RATE, false));
	attackTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinAttackRightAnim));
	//Abajo																							
	attackAnims_.push_back(Anim(ATTACK_D_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, ATTACK_D_FRAME_RATE, false));
	attackTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinAttackDownAnim));
	//Izquierda																						
	attackAnims_.push_back(Anim(ATTACK_L_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, ATTACK_L_FRAME_RATE, false));
	attackTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinAttackLeftAnim));

	//Animaci�n de explosi�n
		//Arriba
	explosionAnims_.push_back(Anim(EXPLOSION_U_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, EXPLOSION_U_FRAME_RATE, false));
	explosionTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinExpUpAnim));
	//Derecha																						
	explosionAnims_.push_back(Anim(EXPLOSION_R_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, EXPLOSION_R_FRAME_RATE, false));
	explosionTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinExpRightAnim));
	//Abajo																							
	explosionAnims_.push_back(Anim(EXPLOSION_D_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, EXPLOSION_D_FRAME_RATE, false));
	explosionTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinExpDownAnim));
	//Izquierda																						
	explosionAnims_.push_back(Anim(EXPLOSION_L_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, EXPLOSION_L_FRAME_RATE, false));
	explosionTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinExpLeftAnim));

	//Animaci�n de movimiento
		//Arriba
	moveAnims_.push_back(Anim(MOVE_U_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, MOVE_U_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinMoveUpAnim));
	//Derecha																						
	moveAnims_.push_back(Anim(MOVE_R_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, MOVE_R_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinMoveRightAnim));
	//Abajo																							
	moveAnims_.push_back(Anim(MOVE_D_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, MOVE_D_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinMoveDownAnim));
	//Izquierda																						
	moveAnims_.push_back(Anim(MOVE_L_FRAMES, W_PUMPKIN_FRAME, H_PUMPKIN_FRAME, MOVE_L_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PumpkinMoveLeftAnim));

	initIdle();
}
void Pumpkin::initRewards()
{
	minGold = 20;
	maxGold = 50;
	minArchievementPoints = 70;
	maxArchievementPoints = 110;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void Pumpkin::updateCooldowns()
{
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}

void Pumpkin::initIdle()
{
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
void Pumpkin::initAttack()
{
	shooted_ = false;
	updateDirVisEnemy();
	currState_ = STATE::ATTACKING;
	texture_ = attackTx_[(int)currDir_];
	currAnim_ = attackAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
void Pumpkin::initExplosion()
{
	texture_ = explosionTx_[(int)currDir_];
	currAnim_ = explosionAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
	currState_ = STATE::DYING;
	CollisionCtrl::instance()->removeEnemy(this);

}
bool Pumpkin::explosionAnim()
{
	if (currEnemy_ == nullptr) {
		static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	if (!explosion_ && currAnim_.currFrame_ == FRAME_ACTION_EXPLOSION) {
		explosion_ = true;
		app_->getAudioManager()->playChannel(Resources::ExplosionPumpkin, 0, Resources::PumpkinChannel2);
		auto s = app_->getRandom()->nextInt(0,101);
		if (s >= 75) {
		app_->getAudioManager()->playChannel(Resources::TauntPumpkin1, 0, Resources::PumpkinChannel1);
		}
		auto dmg = dynamic_cast<Player*>(currEnemy_);
		Point2D center = getCenter();
		Point2D currEnemyCenter = currEnemy_->getCenter();
		if (dmg != nullptr && RectBall((float)currEnemyCenter.getX(), (float)currEnemyCenter.getY(), (float)currEnemy_->getScaleX(), (float)currEnemy_->getScaleY(),
			(float)center.getX(), (float)center.getY(), (float)explosionRange_)) {

			dmg->receiveDamage(currStats_.meleeDmg_);
		}
		return false;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_)
	{
		static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	else
	{
		return false;
	}
}
void Pumpkin::initMove()
{
	app_->getAudioManager()->playChannel(Resources::MovePumpkin, -1, Resources::PumpkinChannel1);
	currState_ = STATE::FOLLOWING;
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
//Testeo
void Pumpkin::updateDirVisEnemy() {
	if (currEnemy_ != nullptr) {
		Vector2D center = getCenter();		//Punto de referencia
		Vector2D enemyCenter = currEnemy_->getCenter();
		Vector2D dir = enemyCenter - center;		//Vector direcci�n
		dir.normalize();
		double angle = atan2(dir.getY(), dir.getX()) * 180 / M_PI;
		if (angle >= 0) {
			if (angle <= 45.0) currDir_ = DIR::RIGHT;
			else if (angle < 135.0) currDir_ = DIR::DOWN;
			else currDir_ = DIR::LEFT;
		}
		else {
			if (angle >= -45.0) currDir_ = DIR::RIGHT;
			else if (angle >= -135.0) currDir_ = DIR::UP;
			else currDir_ = DIR::LEFT;
		}
	}
}
//testeo
void Pumpkin::shootAnim()
{
	if (!shooted_ && currAnim_.currFrame_ == FRAME_ACTION_SHOOT) {
		disAttack();
		shootCD_.initCooldown(currStats_.distRange_);
		shooted_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();	//Activa el idle
	}
}
