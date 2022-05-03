#include "Actor.h"
#include "HandleEvents.h"
#include "GameState.h"

//Inicialliza los stats
void Actor::initStats(double health, double mana, double manaReg, double armor, double meleeDmg, double distDmg, double crit,
	double meleeRange, double distRange, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, meleeDmg, distDmg, crit, meleeRange, distRange, moveSpeed, meleeRate, distRate);
}

bool Actor::applyCritic()
{
	//Probabilidad de critico
	int crit = app_->getRandom()->nextInt(1, 101);
	if (crit <= currStats_.crit_) return true;
	else return false;
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
	mousePos_ = HandleEvents::instance()->getRelativeMousePos();
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

void Actor::receiveDamage(double damage) {
	lastTint_ = SDL_GetTicks();
	feedBackHurtSounds();
	//Reduccion de daño
	double limitArmor = currStats_.armor_;
	if (limitArmor >= 60) limitArmor = 60;
	double realDamage = damage - (damage * limitArmor / 100);
 	currStats_.health_ -= realDamage;
	if (currStats_.health_ <= 0) {
		initDie();
	}
}

void Actor::manageTint() {
	if (currState_ == STATE::DYING || currState_ == STATE::DIED) {
		SDL_SetTextureColorMod(texture_->getSDLTex(), 255, 255, 255);
	}
	else {
		if (SDL_GetTicks() - lastTint_ <= TINT_TIME) {
			SDL_SetTextureColorMod(texture_->getSDLTex(), 255, 0, 0);
		}
		else
		{
			SDL_SetTextureColorMod(texture_->getSDLTex(), 255, 255, 255);
		}
	}
}

void Actor::initDie() {
	setScale(Vector2D(getScaleX() * 0.75, getScaleY() * 0.75));
	currState_ = STATE::DYING;
	currAnim_ = Anim(DIE_FRAMES, W_DIE_FRAME, H_DIE_FRAME, DIE_FRAME_RATE, false);
	texture_ = app_->getTextureManager()->getTexture(Resources::EntityDie);
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Actor::dieAnim() {
	if (currAnim_.currFrame_ >= currAnim_.numberFrames_ - 1) {
		currState_ = STATE::DIED;
		dieAudio();
		app_->getCurrState()->removeRenderUpdateLists(this);
	}
}