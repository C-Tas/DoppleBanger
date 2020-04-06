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

	//Si se pulsa la Q y se ha acabado el cooldown y se está a rango
	//Hago un if dentro de otro if ya que como el de dentro tiene que hacer cálculos, estos solo se hagan
	//cuando ya se han cumplido previamente las dos condiciones anteriores.
	if (eventHandler_->isKeyDown(SDL_SCANCODE_Q) && ((SDL_GetTicks() - clonTime_) / 1000) > clonCooldown_)
	{
		Vector2D dist = Vector2D(eventHandler_->getMousePos().getX() - pos_.getX(), eventHandler_->getMousePos().getY() - pos_.getY());
		if (dist.magnitude() <= CLON_SPAWN_RANGE)
		{
			clon_ = new Clon(app_, getVisPos(eventHandler_->getMousePos()), scale_, this);
			app_->getGameStateMachine()->getState()->addRenderUpdateLists(clon_);
			clonTime_ = SDL_GetTicks();
			//Restamos el maná de la creación del clon
			decreaseMana(clon_->getCost());
			GameManager::instance()->setSkillCooldown(true, SkillKey::Q);
		}
	}else if(((SDL_GetTicks() - clonTime_) / 1000) > clonCooldown_) GameManager::instance()->setSkillCooldown(false, SkillKey::Q);

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_)
		shoot(eventHandler_->getMousePos());
	else if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		Vector2D dir = eventHandler_->getMousePos();
		move(getVisPos(dir));
	}

	//Si no est� atacando se mueve a la posici�n indicada con un margen de 2 pixels
	int margin = 2; if (attacking) margin = currStats_.meleeRange_;

	if (visPos_.getX() < target_.getX() - margin ||
		visPos_.getX() > target_.getX() + margin ||
		visPos_.getY() < target_.getY() - margin ||
		visPos_.getX() > target_.getX() + margin)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}
	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_ && objective_->getState() != STATE::DIYING)
	{
		objective_->reciveDmg(currStats_.meleeDmg_);
		meleeTime_ = SDL_GetTicks();
	}
	if (currState_ == STATE::DIYING) {
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
}

void Player::shoot(Vector2D dir)
{
	//Se actualiza el momento del �ltimo disparo
	shotTime_ = SDL_GetTicks();

	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Rock), shootPos, dir, currStats_.distDmg_, false);
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
	attacking = false;
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
	move(obj->getVisPos(objective_->getPos()));
	attacking = true;
}