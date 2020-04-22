#include "Tentacle.h"
#include "CollisionCtrl.h"
#include "Kraken.h"

bool Tentacle::update()
{
	//Mientras dure el tentáculo
	if ((SDL_GetTicks() - spawnTime_) / 1000 < TENTACLE_DURATION)
	{
		switch (currState_)
		{
		case STATE::FOLLOWING:
			if ((SDL_GetTicks() - spawnTime_) / 1000 < ATTACK_DURATION)
				;//Animación tentáculo cayendo
			else {
				collisionArea_ = collArea_;
				setTexture(app_->getTextureManager()->getTexture(Resources::RedBar));
				currState_ = STATE::ATTACKING;
				//Durante 1 frame se hace daño al jugador
			}
			break;
		case STATE::ATTACKING:
			//Después de ese frame hace de pared
			currState_ = STATE::IDLE;
			break;
		}
	}
	//Cuando muere le dice al kraken que lo mate
	else if (currState_ != STATE::DYING)
	{
		kraken_->tentDeath(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	return false;
}

void Tentacle::initObject()
{
	setTexture(app_->getTextureManager()->getTexture(Resources::BlueBar));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collArea_ = SDL_Rect({ (int)pos_.getX(), (int)pos_.getY(), (int)scaleCollision_.getX(), (int)scaleCollision_.getY() });
	collisionArea_ = SDL_Rect({ 0, 0, 0, 0 });
	CollisionCtrl::instance()->addEnemy(this);
	initAnims();
	spawnTime_ = SDL_GetTicks();
	currState_ = STATE::FOLLOWING;
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
	if (currState_ == STATE::ATTACKING)
	{
		cout << collisionRot_ << endl;
		double radians = collisionRot_ * (M_PI / 180);
		Point2D p1, p2;
		Vector2D dir;

		player->receiveDamage(kraken_->getMeleeDmg());

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
		player->displace( dir, margin);

	}
	else if (currState_ == STATE::IDLE)
		player->stop();
}

void Tentacle::receiveDamage(int dmg)
{
	//Daño hecho al tentáculo daña al kraken
	kraken_->receiveDamage(dmg);
}

const void Tentacle::draw()
{
	SDL_Rect dest = getDestiny(); dest.x = dest.x - Camera::instance()->getCamera().getX(); dest.y = dest.y - Camera::instance()->getCamera().getY();
	if (currAnim_.numberFrames_ <= 0) texture_->render(dest, collisionRot_);
	else texture_->render(dest, collisionRot_, frame_);
}