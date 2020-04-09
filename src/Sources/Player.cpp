#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBox.h"
#include "GameState.h"
#include "Bullet.h"
#include "GameState.h"
#include "GameManager.h"
#include "CollisionCtrl.h"
#include "PerforateSkill.h"
#include "RicochetSkill.h"

bool Player::update()
{
	updateVisPos();

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
	if (eventHandler_->isKeyDown(SDL_SCANCODE_W)) 
		w_->action();
	if (eventHandler_->isKeyDown(SDL_SCANCODE_E))
		e_->action();

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_)
		shoot(eventHandler_->getMousePos());

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
	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking_ && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_ && objective_->getState() != STATE::DYING)
	{
		cout << "Ataca" << endl;
		objective_->reciveDmg(currStats_.meleeDmg_);
		if (objective_->getState() == STATE::DYING) move(visPos_);
		meleeTime_ = SDL_GetTicks();
	}
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte
		return true;
	}
	return false;
}

void Player::initObject() {
	GameManager::instance()->setPlayer(this);
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	eventHandler_ = HandleEvents::instance();
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	CollisionCtrl::instance()->setPlayer(this);

	#pragma region Testeo
	w_ = new PerforateSkill(this);
	e_ = new RicochetSkill(this);
	#pragma endregion
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
	//Activa perforación en la bala
	if (perforate_) {
		bullet->setPerforate(perforate_);
		perforate_ = false;
	}
	//Activa el rebote en la bala
	if (ricochet_)
		bullet->setRicochet(ricochet_);
	//Cuando se acabe el tiempo de ricochet, se pone a false
	if (ricochet_ && (SDL_GetTicks() - lastTimeRico_) / 1000 > TIME_RICO)
		ricochet_ = false;

	//Se añade a los bucles del juegos
	app_->getCurrState()->addRenderUpdateLists(bullet);
	CollisionCtrl::instance()->addPlayerBullet(bullet);
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