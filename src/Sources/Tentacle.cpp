#include "Tentacle.h"
#include "CollisionCtrl.h"
#include "Kraken.h"
#include "Collisions.h"

bool Tentacle::update()
{
	updateFrame();
	updateCooldowns();

	//Si el tentaculo esta cayendo
	if (currState_ == STATE::FOLLOWING && !fallingCD_.isCooldownActive())
	{
		//Una vez cae se le asigna su hitbox
		collisionArea_ = collArea_;
		posCollision_ = Point2D(0,0);
		scaleCollision_ = scale_;
		setTexture(app_->getTextureManager()->getTexture(Resources::RedBar));
		currState_ = STATE::ATTACKING;
		//Durante 1 frame se hace daño al jugador
	}
	else if (currState_ != STATE::FOLLOWING)
	{
		//Dependiendo del ataque para el que se ha invocado
		switch (attack_)
		{
		case ATTACKS::SLAM:
			return slamUpdate();
			break;
		case ATTACKS::SWEEP:
			return sweepUpdate();
			break;
		}
	}
	return false;
}

bool Tentacle::sweepUpdate()
{
	//Mientras no haya llegado a la posici�n inicial con un margen de error (y no haya hecho ning�n giro para que funcione la primera vez)
	if (turns_ < 4 || !((abs(pos_.getX() - initPos_.getX()) < (kraken_->getScaleX() * 0.05)) && (abs(pos_.getY() - initPos_.getY()) < (kraken_->getScaleY() * 0.1))))
	{
		if (!rotating_)
		{
			pos_.setVec(pos_.getVec() + (sweepDir_ * speed_ * app_->getDeltaTime()));
			double deltaY = (kraken_->getScaleX() - kraken_->getScaleY()) / 2;

			//Comprobaciones de si el tent�culo ha llegado a una de las esquinas en las que gira (dependientes de pos y scale de kraken)
			if (abs(abs(collisionRot_) - 0) <= 1 && pos_.getY() + scale_.getY() / 2 > kraken_->getPosY() + kraken_->getScaleY())
			{
				collisionRot_ = 0;
				centerRot_ = Vector2D(getCenter().getX() - scale_.getX() / 2, getCenter().getY());
				rotating_ = true;
			}
			else if (abs(abs(collisionRot_) - 270) <= 1 && pos_.getX() + scale_.getX() / 2 > kraken_->getPosX() + kraken_->getScaleX())
			{
				collisionRot_ = 270;
				centerRot_ = Vector2D(getCenter().getX(), getCenter().getY() + scale_.getX() / 2);
				rotating_ = true;
			}
			else if (abs(abs(collisionRot_) - 180) <= 1 && pos_.getY() + scale_.getY() / 2 < kraken_->getPosY())
			{
				collisionRot_ = 180;
				centerRot_ = Vector2D(getCenter().getX() + scale_.getX() / 2, getCenter().getY());
				rotating_ = true;
			}
			else if (abs(abs(collisionRot_) - 90) <= 1 && pos_.getX() + scale_.getX() / 2 < kraken_->getPosX())
			{
				collisionRot_ = 90;
				centerRot_ = Vector2D(getCenter().getX(), getCenter().getY() - scale_.getX() / 2);
				rotating_ = true;
			}
		}
		else
		{
			//Cuando llega a una esquina rota cada frame en base a un movimiento circular uniforme con velocidad angular
			double angle = collisionRot_ * (M_PI / 180);
			deltaAngle_ += (speed_ * app_->getDeltaTime() / (scale_.getX() / 2));
			angle += (speed_ * app_->getDeltaTime() / (scale_.getX() / 2));
			pos_.setX((centerRot_.getX() + (scale_.getX() / 2) * cos(angle)) - scale_.getX() / 2);
			pos_.setY((centerRot_.getY() + (scale_.getX() / 2) * sin(angle)) - scale_.getY() / 2);
			collisionRot_ = (180 / M_PI) * atan2(getCenter().getY() - centerRot_.getY(), getCenter().getX() - centerRot_.getX());

			//Si ha completado el giro
			if (deltaAngle_ >= M_PI / 2)
			{
				rotating_ = false;
				deltaAngle_ = 0;
				collisionRot_ = floor(collisionRot_);
				if (collisionRot_ == -90) collisionRot_ = 270;
				sweepDir_ = Vector2D(cos(collisionRot_ * (M_PI / 180) + M_PI / 2), sin(collisionRot_ * (M_PI / 180) + M_PI / 2));
				turns_++;
			}
		}

	}
	//Si ha hecho su recorrido y no se est� muriendo se muere
	else if (currState_ != STATE::DYING)
	{
		kraken_->tentDeath(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	return false;

}

void Tentacle::updateCooldowns()
{
	if (lifeCD_.isCooldownActive()) lifeCD_.updateCooldown();
	if (fallingCD_.isCooldownActive()) fallingCD_.updateCooldown();
}

bool Tentacle::slamUpdate()
{
	//Mientras dure el tent�culo
	if (lifeCD_.isCooldownActive())
	{
		if (currState_ == STATE::ATTACKING)
		{
			//Despu�s de ese frame hace de pared
			currState_ = STATE::IDLE;
		}
		return false;
	}
	//Cuando muere le dice al kraken que lo mate
	else if (currState_ != STATE::DYING)
	{
		kraken_->tentDeath(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
}

void Tentacle::initObject()
{
	setTexture(app_->getTextureManager()->getTexture(Resources::BlueBar));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	//Empieza sin hitbox as� que se guarda en una variable a parte
	collArea_ = SDL_Rect({ (int)pos_.getX(), (int)pos_.getY(), (int)scaleCollision_.getX(), (int)scaleCollision_.getY() });
	collisionArea_ = SDL_Rect({ 0, 0, 0, 0 });
	CollisionCtrl::instance()->addEnemy(this);
	initAnims();
	lifeCD_.initCooldown(TENTACLE_DURATION);
	fallingCD_.initCooldown(FALL_DURATION);
	//El tent�culo empieza cayendo
	currState_ = STATE::FOLLOWING;
	double angle = collisionRot_ * (M_PI / 180) + M_PI / 2;
	sweepDir_ = Vector2D(cos(angle), sin(angle));
	initPos_ = pos_;
}

//Inicializa todas las animaciones
void Tentacle::initAnims()
{
	Anim spawnAnim_ = Anim(NUM_FRAMES_SPAWN, W_FRAME_SPAWN, H_FRAME_SPAWN, FRAME_RATE_SPAWN, false);
	Anim idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, false);
	Anim despawnAnim_ = Anim(NUM_FRAMES_DESPAWN, W_FRAME_DESPAWN, H_FRAME_DESPAWN, FRAME_RATE_DESPAWN, false);
}

void Tentacle::onCollider()
{
	Player* player = static_cast<Player*>(GameManager::instance()->getPlayer());
	if (Collisions::collidesWithRotation(player->getPos(), player->getScaleX(), player->getScaleY(), player->getCollisionRot(), pos_, scale_.getX(), scale_.getY(), collisionRot_))
	{
		if (currState_ == STATE::IDLE) {
			player->stop();
		}
		else if (currState_ == STATE::ATTACKING) {
			player->receiveDamage(currStats_.meleeDmg_);
		}
	}
}

void Tentacle::receiveDamage(int dmg)
{
	//Da�o hecho al tent�culo da�a al kraken
	kraken_->receiveDamage(dmg);
}

const void Tentacle::draw()
{
	SDL_Rect dest = getDestiny(); dest.x = dest.x - Camera::instance()->getCamera().getX(); dest.y = dest.y - Camera::instance()->getCamera().getY();
	if (currAnim_.numberFrames_ <= 0) texture_->render(dest, collisionRot_);
	else texture_->render(dest, collisionRot_, frame_);

	app_->getTextureManager()->getTexture(Resources::GreenBar)->render({ (int)(getColliderPos().getX() - Camera::instance()->getCamera().getX()), (int)(getColliderPos().getY() - Camera::instance()->getCamera().getY()),(int)(scaleCollision_.getX()), (int)(scaleCollision_.getY()) }, collisionRot_);
}