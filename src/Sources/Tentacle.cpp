#include "Tentacle.h"
#include "CollisionCtrl.h"
#include "Kraken.h"
#include "Collisions.h"

bool Tentacle::update()
{
	/*if (animation) {
		updateFrame();
	}*/

	updateCooldowns();

	//Si el tentaculo esta cayendo
	if (currState_ == STATE::FOLLOWING && !fallingCD_.isCooldownActive()/* && currAnim_.currFrame_ == currAnim_.numberFrames_ - 1*/)
	{

		//termina la animacion 
		//animation = false;
		//Una vez cae se le asigna su hitbox
		collisionArea_ = collArea_;
		//setTexture(app_->getTextureManager()->getTexture(Resources::RedBar));
		currState_ = STATE::ATTACKING;
		//Durante 1 frame se hace daño al jugador
	}
	else
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
	if (turns_ < 4 || !((abs(pos_.getX() - initPos_.getX()) < (kraken_->getScaleX() * 0.05)) && (abs(pos_.getY() - initPos_.getY()) < (kraken_->getScaleY() * 0.05))))
	{
		if (!rotating_)
		{
			pos_.setVec(pos_.getVec() + (sweepDir_ * speed_ * app_->getDeltaTime()));
			double deltaY = (kraken_->getScaleX() - kraken_->getScaleY()) / 2;

			//Comprobaciones de si el tent�culo ha llegado a una de las esquinas en las que gira (dependientes de pos y scale de kraken)
			if (abs(collisionRot_ - 0) <= 1 && pos_.getY() + scale_.getY() / 2 > kraken_->getPosY() + kraken_->getScaleY())
			{
				collisionRot_ = 0;
				centerRot_ = Vector2D(getCenter().getX() - scale_.getX() / 2, getCenter().getY());
				rotating_ = true;
			}
			else if (abs(collisionRot_ - 270) <= 1 && pos_.getX() + scale_.getX() / 2 > kraken_->getPosX() + kraken_->getScaleX())
			{
				collisionRot_ = 270;
				centerRot_ = Vector2D(getCenter().getX(), getCenter().getY() + scale_.getX() / 2);
				rotating_ = true;
			}
			else if (abs(collisionRot_ - 180) <= 1 && pos_.getY() + scale_.getY() / 2 < kraken_->getPosY())
			{
				collisionRot_ = 180;
				centerRot_ = Vector2D(getCenter().getX() + scale_.getX() / 2, getCenter().getY());
				rotating_ = true;
			}
			else if (abs(collisionRot_ - 90) <= 1 && pos_.getX() + scale_.getX() / 2 < kraken_->getPosX())
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
				collisionRot_ = round(collisionRot_);
				if (collisionRot_ == -90) collisionRot_ = 270;
				sweepDir_ = Vector2D(cos(collisionRot_ * (M_PI / 180) + M_PI / 2), sin(collisionRot_ * (M_PI / 180) + M_PI / 2));
				turns_++;
			}
		}

	}
	//Si ha hecho su recorrido y no se est� muriendo se muere
	else if (currState_ != STATE::DYING)
	{
		//primero la animacion de desaparecer el tentaculo
		//initDespawnAnim();
		//cuando acaba la animacion eliminamos el tentaculo
		//if (currAnim_.currFrame_ == currAnim_.numberFrames_ - 1) {
			kraken_->tentDeath(this);
			app_->getCurrState()->removeRenderUpdateLists(this);
		//}
		
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
		//primero la animacion de desaparecer el tentaculo
		//initDespawnAnim();
		//cuando acaba la animacion eliminamos el tentaculo
		//if (currAnim_.currFrame_ == currAnim_.numberFrames_ - 1) {
			kraken_->tentDeath(this);
			app_->getCurrState()->removeRenderUpdateLists(this);
		//}

		
		return true;
	}
}

//void Tentacle::initSpawnAnim()
//{
//	animation = false;
//	//currState_ = STATE::IDLE;
//	texture_ = spawnTX_;
//	currAnim_ = spawnAnim_;
//
//	frame_.x = 1710; frame_.y = 0;
//	frame_.w = currAnim_.widthFrame_;
//	frame_.h = currAnim_.heightFrame_;
//}

//void Tentacle::initDespawnAnim()
//{
//	animation = true;
//	texture_ = despawnTX_;
//	currAnim_ = despawnAnim_;
//
//	frame_.x = 0; frame_.y = 0;
//	frame_.w = currAnim_.widthFrame_;
//	frame_.h = currAnim_.heightFrame_;
//}



void Tentacle::initObject()
{
	//initAnims();
	/*texture_ = spawnTX_;
	currAnim_ = spawnAnim_;*/
	setTexture(app_->getTextureManager()->getTexture(Resources::tentaculo));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	//Empieza sin hitbox as� que se guarda en una variable a parte
	collArea_ = SDL_Rect({ (int)pos_.getX(), (int)pos_.getY(), (int)scaleCollision_.getX(), (int)scaleCollision_.getY() });
	collisionArea_ = SDL_Rect({ 0, 0, 0, 0 });
	CollisionCtrl::instance()->addEnemy(this);

	lifeCD_.initCooldown(TENTACLE_DURATION);
	fallingCD_.initCooldown(FALL_DURATION);
	//El tent�culo empieza cayendo
	currState_ = STATE::FOLLOWING;
	double angle = collisionRot_ * (M_PI / 180) + M_PI / 2;
	sweepDir_ = Vector2D(cos(angle), sin(angle));
	initPos_ = pos_;
}

//Inicializa todas las animaciones
//void Tentacle::initAnims()
//{
//	 spawnAnim_ = Anim(NUM_FRAMES_SPAWN, W_FRAME_SPAWN, H_FRAME_SPAWN, FRAME_RATE_SPAWN, false);
//	spawnTX_ = app_->getTextureManager()->getTexture(Resources::KrakenAzoteAnim);
//	//Anim idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, false);
//	 despawnAnim_ = Anim(NUM_FRAMES_DESPAWN, W_FRAME_DESPAWN, H_FRAME_DESPAWN, FRAME_RATE_DESPAWN, false);
//	despawnTX_ = app_->getTextureManager()->getTexture(Resources::KrakenAzoteAtrasAnim);
//	initSpawnAnim();
//}

void Tentacle::onCollider()
{
	Player* player = static_cast<Player*>(GameManager::instance()->getPlayer());
	if (Collisions::collidesWithRotation(player->getPos(), player->getScaleX(), player->getScaleY(),player->getCollisionRot(), pos_, scale_.getX(), scale_.getY(), collisionRot_))
	{
		if (currState_ == STATE::ATTACKING)
		{

			double radians = collisionRot_ * (M_PI / 180);
			Point2D p1, p2;
			Vector2D dir;

			double realDamage = kraken_->getMeleeDmg();
			if (kraken_->applyCritic()) realDamage *= 1.5;
			player->receiveDamage(realDamage);

			double a, b, c, d;

			// y = mx + b 
			// a = m; c = a* (-x0) + y0 
			// y - y0 = a * (x-x0)
			// ax + c = y = bx + d 
			// P((d-c)/ (a - b), (a*d -b*c)/(a-b))

			a = tan(radians + M_PI / 2);
			b = tan(radians);
			c = tan(radians + M_PI / 2) * -(player->getCenter().getX()) + player->getCenter().getY();
			d = tan(radians) * -(pos_.getX()) + pos_.getY();

			p1.setX((d - c) / (a - b));
			p1.setY((a * d - b * c) / (a - b));

			d = tan(radians) * -(pos_.getX() + scale_.getX()) + pos_.getY() + scale_.getY();

			p2.setX((d - c) / (a - b));
			p2.setY((a * d - b * c) / (a - b));

			if ((p2 - player->getCenter()).magnitude() < (p1 - player->getCenter()).magnitude())
				dir = (p2 - player->getCenter());
			else
				dir = (p1 - player->getCenter());

			dir.normalize();

			int margin = scale_.getY() * 0.6 + (player->getScaleX() / 2 + player->getScaleY() / 2);
			player->displace(dir, margin);

		}
		else if (currState_ == STATE::IDLE)
			player->stop();
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
}