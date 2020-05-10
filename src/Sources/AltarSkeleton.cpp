#include "AltarSkeleton.h"
#include "CollisionCtrl.h"	//Para agregar y quitar los esqueletos de la lista de enemigos
#include "PlayState.h"		//Para eliminar mobs de la lista de enemigos

bool AltarSkeleton::update()
{
	updateFrame();
	//muerte definitiva del esqueleto
	if (mobState_ == MOBSTATE::DIE) {
		static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
		static_cast<PlayState*>(app_->getCurrState())->removeRenderUpdateLists(this);
		return true;
	}
	//Si el mob se puede resucitar y el altar lo permite -> resucita
	else if ( mobState_ == MOBSTATE::RISEABLE && altarOwner_->canResurrect()) {
		texture_ = app_->getTextureManager()->getTexture(Resources::Skeleton);
		mobState_ = MOBSTATE::ALIVE;
		currState_ = STATE::IDLE;
		CollisionCtrl::instance()->addEnemy(this);
	}
	//Si el mob no puede resucitar se mata definitivamente
	else if (mobState_ == MOBSTATE::UNRISEABLE && currState_ == STATE::DYING) {
		mobState_ = MOBSTATE::DIE;
	}
	//Si el esqueleto está vivo
	else if (mobState_ == MOBSTATE::ALIVE) {
		//Si el esqueleto no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo más cercano
		if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
			currState_ = STATE::ATTACKING;
		}
		//Si el esqueleto tiene enemigo y puede atacar
		if (currState_ == STATE::ATTACKING) {
			//Si el esqueleto tiene un enemigo y lo tiene a rango
			if (onRange()) {
				attack();
			}
			//Tiene enemigo pero no a rango
			else if(currEnemy_ != nullptr)
			{
				currState_ = STATE::FOLLOWING;
				selectTarget();
			}
		}
		//Tengo enemigo pero no a rango -> lo sigo
		if (currState_ == STATE::FOLLOWING) {
			//Siguiendo a un enemigo vuelve a rango -> ataco
			if (onRange()) {
				currState_ = STATE::ATTACKING;
				stop();
				attack();
			}
			//Sigue sin estar a rango -> lo sigo
			else
			{
				selectTarget();
			}
		}
	}
	return false;
}

void AltarSkeleton::die()
{
	altarOwner_->deactivateResurrect();
	texture_ = app_->getTextureManager()->getTexture(Resources::PlayerFront);
	CollisionCtrl::instance()->removeEnemy(this);
	currState_ = STATE::DYING;
	if (altarOwner_->outRange(getDestiny())) {
		mobState_ = MOBSTATE::UNRISEABLE;
	}
	else
	{
		mobState_ = MOBSTATE::RISEABLE;
	}
}

void AltarSkeleton::initObject()
{
	setTexture(app_->getTextureManager()->getTexture(Resources::PlayerFront));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	rangeVision_ = 270;
	initAnims();
}

void AltarSkeleton::selectTarget()
{
	Point2D centerPos = { getPosX() + getScaleX() / 2, getPosY() + getScaleY() / 2 };
	Point2D enemycenterPos = { currEnemy_->getPosX() + currEnemy_->getScaleX() / 2, currEnemy_->getPosY() + currEnemy_->getScaleY() / 2 };
	Vector2D posToReach;
	posToReach.setX((enemycenterPos.getX() + currStats_.distRange_) - centerPos.getX());
	posToReach.setY((enemycenterPos.getY() + currStats_.distRange_) - centerPos.getY());
	target_ = posToReach;
	move(enemycenterPos);
}

void AltarSkeleton::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(posToReach);
	dir_.setX(posToReach.getX() - getCenter().getX());
	dir_.setY(posToReach.getY() - getCenter().getY());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}


