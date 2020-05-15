#include "Clon.h"
#include "PlayState.h"
#include "Player.h"
#include "GameManager.h"
#include "PlayerBullet.h"

bool Clon::update() {
	updateFrame();

	if (lifeTimeCD_.isCooldownActive()) {
		lifeTimeCD_.updateCooldown();

		if (currState_ == STATE::SELFDESTRUCT && currAnim_.currFrame_ == currAnim_.numberFrames_ - 1) {
			player_->killClon();
		}
		else if (currState_ == STATE::ATTACKING) {
			meleeAnim();
		}
		else if (currState_ == STATE::SHOOTING && currAnim_.currFrame_ == currAnim_.numberFrames_) {
			currState_ = STATE::IDLE;
			initIdle();
		}
		

		Vector2D clonPos = getVisPos();
		if (meleeDmg_ > 0 && (objective_ == nullptr || objective_->getState() == STATE::DYING ||
			Vector2D(abs(objective_->getVisPos().getX() - clonPos.getX()), abs(objective_->getVisPos().getY() - clonPos.getY())).magnitude() > range_))
			objective_ = static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_);

		else if (meleeDmg_ > 0 && !meleeCD_.isCooldownActive())
		{
			initMelee();
		}
	}

	else {
		cout << "MORISION" << endl;
		if (currState_ != STATE::VANISH){
			initVanish();
		}
		if (currAnim_.currFrame_ == currAnim_.numberFrames_ -1 ) {
			cout << "KILL" << endl;
			player_->killClon();
		}
	}
	return false;
}

void Clon::initObject() {
	GameManager::instance()->setClon(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	lifeTimeCD_.initCooldown(DURATION_);
	range_ = player_->getStats().meleeRange_ * 2;
	meleeRate_ = (player_->getStats().meleeRate_ / 2) * player_->getLiberation();
	meleeDmg_ = (player_->getStats().meleeDmg_ / 2) * player_->getLiberation();
	distDmg_ = (player_->getStats().distDmg_ / 2) * player_->getLiberation();
	distRange_ = (player_->getStats().distRange_ / 2) * player_->getLiberation();
	//buletSpeed_ = player_->getInfoEquip().fireGun_->getSpeed(); //Si no la bala del clon no se mueve
	taunt();
	initAnim();
}

void Clon::initAnim() {

	//Animación de idle  --> Cambiar los Resource mas tarde
	//Arriba
	idleAnims_.push_back(Anim(IDLE_U_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, IDLE_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonIdleUpAnim));
	//Derecha																						
	idleAnims_.push_back(Anim(IDLE_R_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, IDLE_R_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonIdleRightAnim));
	//Abajo																							
	idleAnims_.push_back(Anim(IDLE_D_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, IDLE_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonIdleDownAnim));
	//Izquierda																						
	idleAnims_.push_back(Anim(IDLE_L_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, IDLE_L_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonIdleLeftAnim));

	//Animación de melee
	//Arriba
	meleeAnims_.push_back(Anim(MELEE_U_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, MELEE_U_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonMeleeUpAnim));
	//Derecha
	meleeAnims_.push_back(Anim(MELEE_R_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, MELEE_R_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonMeleeRightAnim));
	//Abajo
	meleeAnims_.push_back(Anim(MELEE_D_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, MELEE_D_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonMeleeDownAnim));
	//Izquierda
	meleeAnims_.push_back(Anim(MELEE_L_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, MELEE_L_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonMeleeLeftAnim));

	//Animación de autodestrucción
	//Arriba
	selfDestructAnims_.push_back(Anim(SELFDESTRUCT_U_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SELFDESTRUCT_U_FRAME_RATE, false));
	selfDestructTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonSelfDestructionUpAnim));
	//Derecha																					
	selfDestructAnims_.push_back(Anim(SELFDESTRUCT_R_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SELFDESTRUCT_R_FRAME_RATE, false));
	selfDestructTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonSelfDestructionRightAnim));
	//Abajo
	selfDestructAnims_.push_back(Anim(SELFDESTRUCT_D_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SELFDESTRUCT_D_FRAME_RATE, false));
	selfDestructTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonSelfDestructionDownAnim));
	//Izquierda
	selfDestructAnims_.push_back(Anim(SELFDESTRUCT_L_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SELFDESTRUCT_L_FRAME_RATE, false));
	selfDestructTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonSelfDestructionLeftAnim));

 	//Animacion de disparo
	//Arriba
	shootAnims_.push_back(Anim(SHOOT_U_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SHOOT_U_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonShootUpAnim));
	shootingFrame_.push_back(SHOOT_U_SHOOTINGFRAME);
	//Derecha
	shootAnims_.push_back(Anim(SHOOT_R_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SHOOT_R_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonShootRightAnim));
	shootingFrame_.push_back(SHOOT_R_SHOOTINGFRAME);
	//Abajo
	shootAnims_.push_back(Anim(SHOOT_D_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SHOOT_D_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonShootDownAnim));
	shootingFrame_.push_back(SHOOT_D_SHOOTINGFRAME);
	//izquierda
	shootAnims_.push_back(Anim(SHOOT_L_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, SHOOT_L_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonShootLeftAnim));
	shootingFrame_.push_back(SHOOT_L_SHOOTINGFRAME);

	//Animación de desaparecer
	//Arriba
	vanishAnims_.push_back(Anim(VANISH_U_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, VANISH_U_FRAME_RATE, false));
	vanishTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonVanishUpAnim));
	//Derecha																					
	vanishAnims_.push_back(Anim(VANISH_R_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, VANISH_R_FRAME_RATE, false));
	vanishTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonVanishRightAnim));
	//Abajo
	vanishAnims_.push_back(Anim(VANISH_D_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, VANISH_D_FRAME_RATE, false));
	vanishTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonVanishDownAnim));
	//Izquierda
	vanishAnims_.push_back(Anim(VANISH_L_FRAMES, W_H_CLON_FRAME, W_H_CLON_FRAME, VANISH_L_FRAME_RATE, false));
	vanishTx_.push_back(app_->getTextureManager()->getTexture(Resources::ClonVanishLeftAnim));

	//currDir_ = DIR::LEFT;
	initIdle();
}

void Clon::initIdle() {
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Clon::initMelee()
{
	currState_ = STATE::ATTACKING;	//Cambio de estado
	attacked_ = false;	//Aún no se ha atacado
	updateDirVisObjective(static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_));	//Hacia dónde está el enemigo
	texture_ = meleeTx_[(int)currDir_];
	currAnim_ = meleeAnims_[(int)currDir_];
	//Frame exacto del ataque
	switch (currDir_)
	{
	case DIR::UP:
		frameAction_ = 2;
		break;
	case DIR::RIGHT:
		frameAction_ = 3;
		break;
	case DIR::DOWN:
		frameAction_ = 3;
		break;
	case DIR::LEFT:
		frameAction_ = 3;
		break;
	}

	//Se inicia el frame
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Clon::meleeAnim() {

	if (!attacked_ && currAnim_.currFrame_ == frameAction_) {
		objective_->receiveDamage(meleeDmg_);
		if (objective_->getState() == STATE::DYING)
			enemies_.remove(static_cast<Enemy*>(objective_));
		meleeCD_.initCooldown(currStats_.meleeRate_);
		attacked_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();
	}
}

void Clon::initSelfDestruction() {
	currState_ = STATE::SELFDESTRUCT;
	//updateDirVisObjective(static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_));	//Hacia dónde está el enemigo --> Para el resto de animaciones
	//Aquí no hace falta actualizar la dirección porque se autodestruirá en la dirección que estuviese previamente
	texture_ = selfDestructTx_[(int)currDir_];
	currAnim_ = selfDestructAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
void Clon::initVanish() {
	currState_ = STATE::VANISH;
	//Aquí no hace falta actualizar la dirección porque desaparecerá en la dirección que estuviese previamente
	texture_ = vanishTx_[(int)currDir_];
	currAnim_ = vanishAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Clon::initShoot(Vector2D dir)
{
	currState_ = STATE::SHOOTING;
	//Actualizamos hacia donde está mirando
	updateDirVisMouse();
	texture_ = shootTx_[(int)currDir_];
	currAnim_ = shootAnims_[(int)currDir_];

	//Inicializamos la animación
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	shootingDir_ = dir;
}

void Clon::shoot() {
	if (distDmg_ > 0)
	{
		//Se calcula la posici�n desde la cual se dispara la bala
		Vector2D shootPos;
		shootPos.setX(pos_.getX() + (scale_.getX() / 2));
		shootPos.setY(pos_.getY() + (scale_.getY() / 2));


		PlayerBullet* bullet = new PlayerBullet(app_, app_->getTextureManager()->getTexture(Resources::Bullet), shootPos, shootingDir_, distDmg_, distRange_, buletSpeed_);

		//Se añade a los bucles del juegos
		app_->getCurrState()->addRenderUpdateLists(bullet);
		CollisionCtrl::instance()->addPlayerBullet(bullet);
		
	}
}

void Clon::die() {
	GameManager* gm = GameManager::instance();
	gm->setClon(nullptr);
	app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
	taunt();
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		if ((*it) != nullptr) {
			(*it)->lostAggro();
		}
}

void Clon::taunt() {
	enemies_ = CollisionCtrl::instance()->getEnemiesInArea(getVisPos(), CLON_TAUNT_RANGE);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->newEnemy(this);
}