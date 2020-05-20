#include "Actor.h"
#include "HandleEvents.h"

//Inicialliza los stats
void Actor::initStats(double health, double mana, double manaReg, double armor, double meleeDmg, double distDmg, double crit,
	double meleeRange, double distRange, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, meleeDmg, distDmg, crit, meleeRange, distRange, moveSpeed, meleeRate, distRate);
}
 
void Actor::updateDirVisObjective(GameObject* objective) {
	if (objective != nullptr) {
		Vector2D center = getCenter();		//Punto de referencia
		Vector2D objectiveCenter = objective->getCenter();
		Vector2D dir = objectiveCenter - center;		//Vector dirección
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

void Actor::updateDirVisObjective(Point2D objective) {
	Vector2D center = getCenter();		//Punto de referencia
	Vector2D dir = objective - center;	//Vector dirección
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

void Actor::updateDirVisMouse()
{
	Vector2D mousePos_ = HandleEvents::instance()->getRelativeMousePos();
	Vector2D center = getCenter();		//Punto de referencia
	Vector2D dir = mousePos_ - center;	//Vector dirección
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

//A falta de definir la gesti�n del da�o en funci�n de la armadura
void Actor::receiveDamage(int damage) {
	lastTint_ = SDL_GetTicks();
	feedBackHurtSounds();
	/*double finalDamage = (currStats_.armor_ * damage) / 100;
	currStats_.health_ -= finalDamage;*/
 	currStats_.health_ -= damage;
	if (currStats_.health_ <= 0) {
		this->die();
	}
}

void Actor::manageTint() {
	if (SDL_GetTicks() - lastTint_ <= TINT_TIME) {
		SDL_SetTextureColorMod(texture_->getSDLTex(), 255, 0, 0);
	}
	else
	{
		SDL_SetTextureColorMod(texture_->getSDLTex(), 255, 255, 255);
	}
}