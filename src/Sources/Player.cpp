#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBox.h"
#include "GameState.h"
#include "Bullet.h"
#include "GameState.h"
#include "GameManager.h"
#include "CollisionCtrl.h"

bool Player::update()
{
	updateVisPos();

#pragma region Player Inputs
	//Si se pulsa la Q y se ha acabado el cooldown y se está a rango
	//Hago un if dentro de otro if ya que como el de dentro tiene que hacer cálculos, estos solo se hagan
	//cuando ya se han cumplido previamente las dos condiciones anteriores.
	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q) && ((SDL_GetTicks() - clonTime_) / 1000) > clonCooldown_)
	{
		Vector2D dist = Vector2D(eventHandler_->getMousePos().getX() - pos_.getX(), eventHandler_->getMousePos().getY() - pos_.getY());
		if (dist.magnitude() <= CLON_SPAWN_RANGE)
		{
			Vector2D posClon;
			posClon = Vector2D(eventHandler_->getMousePos().getX() - (scale_.getX() / 2), eventHandler_->getMousePos().getY() - (scale_.getY() / 2));
			clon_ = new Clon(app_, posClon, scale_, this);
			app_->getGameStateMachine()->getState()->addRenderUpdateLists(clon_);
			clonTime_ = SDL_GetTicks();
		}
	}
	//Si se pulsa la tecla adecuada y el golpe potenciado no está en coodown
	if (empowered_ && eventHandler_->isKeyDown(SDL_SCANCODE_W) && ((SDL_GetTicks() - empoweredTime_) / 1000) > empoweredCooldown_)
	{
#ifdef _DEBUG
		cout << "Ataque potenciado se activa" << endl;
#endif // _DEBUG
		empoweredAct_ = true;
	}
	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_)
		shoot(eventHandler_->getMousePos());
#pragma endregion




#pragma region Update
	//Si no est� atacando se mueve a la posici�n indicada con un margen de 2 pixels
	int margin = 2; if (attacking_) margin = currStats_.meleeRange_;

	if (visPos_.getX() < target_.getX() - margin ||
		visPos_.getX() > target_.getX() + margin ||
		visPos_.getY() < target_.getY() - margin ||
		visPos_.getY() > target_.getY() + margin)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}

	//Si se ha utilizado el ataque fuerte, ataca con un bonus porcentual de daño
	else if (empoweredAct_ && attacking_ && ((SDL_GetTicks() - empoweredTime_) / 1000) > empoweredCooldown_&& objective_->getState() != STATE::DYING)
	{
#ifdef _DEBUG
		cout << "Ataque potenciado" << endl;
#endif // _DEBUG
		empoweredAct_ = false;
		objective_->reciveDmg((int)currStats_.meleeDmg_ * empoweredBonus_);
		if (objective_->getState() == STATE::DYING) move(visPos_);
		empoweredTime_ = SDL_GetTicks();
		meleeTime_ = empoweredTime_;
	}

	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking_ && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_&& objective_->getState() != STATE::DYING)
	{
#ifdef _DEBUG
		cout << "Ataque normal" << endl;
#endif // _DEBUG
		objective_->reciveDmg(currStats_.meleeDmg_);
		if (objective_->getState() == STATE::DYING) move(visPos_);
		meleeTime_ = SDL_GetTicks();
	}

	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte
		return true;
	}
#pragma endregion

	
	return false;
}

void Player::initObject() {
	GameManager::instance()->setPlayer(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	CollisionCtrl::instance()->setPlayer(this);
}

void Player::shoot(Vector2D dir)
{
	//Se actualiza el momento del �ltimo disparo
	shotTime_ = SDL_GetTicks();

	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Rock), shootPos, dir, currStats_.distDmg_, false,
		BULLET_LIFE, BULLET_VEL, Vector2D(W_H_BULLET, W_H_BULLET));
	app_->getCurrState()->addRenderUpdateLists(bullet);
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
	dir_.setX(target.getX() - visPos_.getX());
	dir_.setY(target.getY() - visPos_.getY());
	dir_.normalize();
}

void Player::attack(Enemy* obj)
{
	objective_ = obj;
	move(obj->getVisPos());
	attacking_ = true;
}