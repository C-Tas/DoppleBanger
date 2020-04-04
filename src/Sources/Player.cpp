#include "Player.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "TextBox.h"
#include "GameState.h"
#include "Bullet.h"
#include "GameState.h"

void Player::init()
{
	//Equipamiento inicial del jugador
	//Balancear los valores del equipamiento cuando sea necesario
	armor_ = new Armor(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pechera", "helloWorld", 10, 10, 10); armor_->writeStats(); //Prueba
	gloves_ = new Gloves(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Guantes", "helloWorld", 10, 10, 10); gloves_->writeStats(); //Prueba
	boots_ = new Boots(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Botas", "helloWorld", 10, 10, 10); boots_->writeStats(); //Prueba
	sword_ = new Sword(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Sable", "helloWorld", 10, 10, 10, Saber_); sword_->writeStats(); //Prueba
	gun_ = new Gun(app_->getTextureManager()->getTexture(Resources::TextureId::Timon), "Pistola", "helloWorld", 10, 10, 10, Pistol_); gun_->writeStats(); //Prueba
}

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
			clon_ = new Clon(app_, getVisPos(eventHandler_->getMousePos()), currStats_.ad_, currStats_.meleeRate_, currStats_.range_, liberation_, explotion_, scale_);
			app_->getStateMachine()->getState()->addRenderUpdateLists(clon_);
			clonTime_ = SDL_GetTicks();
		}
		
	}

	//Si se pulsa el bot�n derecho del rat�n y se ha acabado el cooldown
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::RIGHT) && ((SDL_GetTicks() - shotTime_) / 1000) > currStats_.distRate_)
		shoot(eventHandler_->getMousePos());
	else if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		Vector2D dir = eventHandler_->getMousePos();
		move(getVisPos(dir));
	}

	//Si no est� atacando se mueve a la posici�n indicada con un margen de 2 pixels
	int margin = 2; if (attacking) margin = currStats_.range_;

	if (visPos_.getX() < obj_.getX() - margin ||
		visPos_.getX() > obj_.getX() + margin ||
		visPos_.getY() < obj_.getY() - margin ||
		visPos_.getX() > obj_.getX() + margin)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}
	//Se comprueba que el enemigo esté vivo porque puede dar a errores
	else if (attacking && ((SDL_GetTicks() - meleeTime_) / 1000) > currStats_.meleeRate_ && objective_->isAlive())
	{
		objective_->takeDamage(currStats_.ad_);
		meleeTime_ = SDL_GetTicks();
	}

	return false;
}

void Player::shoot(Vector2D dir)
{
	//Se actualiza el momento del �ltimo disparo
	shotTime_ = SDL_GetTicks();

	//Se calcula la posici�n desde la cual se dispara la bala
	Vector2D shootPos;
	shootPos.setX(pos_.getX() + (scale_.getX() / 2));
	shootPos.setY(pos_.getY() + (scale_.getY() / 2));

	Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), shootPos, dir, currStats_.ad_);
	app_->getCurrState()->addRenderUpdateLists(bullet);
}

void Player::move(Point2D target)
{
	attacking = false;
	//establecemos el objetivo para poder parar al llegar
	obj_.setVec(target);
	//establecemos la direccion
	dir_.setX(target.getX() - visPos_.getX());
	dir_.setY(target.getY() - visPos_.getY());
	dir_.normalize();
}

void Player::attack(Enemy* obj)
{
	objective_ = obj;
	move(obj->getVisPos());
	attacking = true;
}
void Player::equip(Equipment* equip)
{
	//Se distingue el tipo del equipamiento, se desequipa el actual y se equipa el nuevo
	if (dynamic_cast<Armor*>(equip) != nullptr) {
		armor_->remove(this);
		delete armor_; //Para que la prueba no deje basura
		armor_ = static_cast<Armor*>(equip);
		armor_->equip(this);
		armor_->writeStats(); //Prueba
	}
	else if (dynamic_cast<Gloves*>(equip) != nullptr) {
		gloves_->remove(this);
		delete gloves_; //Para que la prueba no deje basura
		gloves_ = static_cast<Gloves*>(equip);
		gloves_->equip(this);
		gloves_->writeStats(); //Prueba
	}
	else if (dynamic_cast<Boots*>(equip) != nullptr) {
		boots_->remove(this);
		delete boots_; //Para que la prueba no deje basura
		boots_ = static_cast<Boots*>(equip);
		boots_->equip(this);
		boots_->writeStats(); //Prueba
	}
	else if (dynamic_cast<Sword*>(equip) != nullptr) {
		sword_->remove(this);
		delete sword_; //Para que la prueba no deje basura
		sword_ = static_cast<Sword*>(equip);
		sword_->equip(this);
		sword_->writeStats(); //Prueba
	}
	else {
		gun_->remove(this);
		delete gun_; //Para que la prueba no deje basura
		gun_ = static_cast<Gun*>(equip);
		gun_->equip(this);
		gun_->writeStats(); //Prueba
	}
}

Player::~Player()
{
	delete armor_;
	delete gloves_;
	delete boots_;
	delete sword_;
	delete gun_;
}