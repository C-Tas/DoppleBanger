#include "Clon.h"
#include "PlayState.h"
#include "Player.h"
#include "GameManager.h"
#include "PlayerBullet.h"

bool Clon::update() {
	updateFrame();

	if ((SDL_GetTicks() - spawnTime_) / 1000 < duration_) {
		if (currState_ == STATE::SELFDESTRUCT && currAnim_.currFrame_ == currAnim_.numberFrames_) {
			player_->killClon();
		}
		else if (currState_ == STATE::SHOOTING && currAnim_.currFrame_ == currAnim_.numberFrames_) {
			currState_ = STATE::IDLE;
			///Esto está puesto como temporal por qué no está el idle
			texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
			currAnim_ = { 0,0,0,0,false };
		}
		

		Vector2D clonPos = getVisPos();
		if (meleeDmg_ > 0 && (objective_ == nullptr || objective_->getState() == STATE::DYING ||
			Vector2D(abs(objective_->getVisPos().getX() - clonPos.getX()), abs(objective_->getVisPos().getY() - clonPos.getY())).magnitude() > range_))
			objective_ = static_cast<PlayState*>(app_->getGameStateMachine()->getState())->findClosestEnemy(pos_);

		else if (meleeDmg_ > 0 && ((SDL_GetTicks() - meleeTime_) / 1000) > meleeRate_)
		{
			cout << "\nClon ataque\n";
			objective_->receiveDamage(meleeDmg_);
			if (objective_->getState() == STATE::DYING)
				enemies_.remove(static_cast<Enemy*>(objective_));
			meleeTime_ = SDL_GetTicks();
		}
	}
	else if (alive_) player_->killClon();

	return false;
}

void Clon::initObject() {
	GameManager::instance()->setClon(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	spawnTime_ = SDL_GetTicks();
	duration_ = DURATION_;
	range_ = player_->getStats().meleeRange_ * 2;
	meleeRate_ = (player_->getStats().meleeRate_ / 2) * player_->getLiberation();
	meleeDmg_ = (player_->getStats().meleeDmg_ / 2) * player_->getLiberation();
	distDmg_ = (player_->getStats().distDmg_ / 2) * player_->getLiberation();
	taunt();
}

void Clon::initAnim() {
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
		
		PlayerBullet* bullet = new PlayerBullet(app_, app_->getTextureManager()->getTexture(Resources::Rock),shootPos, shootingDir_, distDmg_);
		
		//Se añade a los bucles del juegos
		app_->getCurrState()->addRenderUpdateLists(bullet);
		CollisionCtrl::instance()->addPlayerBullet(bullet);
		
	}
}

void Clon::die() {
	GameManager* gm = GameManager::instance();
	gm->setClon(nullptr);
	app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->lostAggro();
	alive_ = false;
}

void Clon::taunt() {
	enemies_ = CollisionCtrl::instance()->getEnemiesInArea(getVisPos(), CLON_TAUNT_RANGE);
	for (auto it = enemies_.begin(); it != enemies_.end(); ++it)
		(*it)->newEnemy(this);
}