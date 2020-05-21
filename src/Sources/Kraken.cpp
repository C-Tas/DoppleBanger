#include "Kraken.h"
#include "CollisionCtrl.h"
#include "PlayState.h"
#include "Ink.h"

Kraken::~Kraken()
{
}

bool Kraken::update() {

	updateFrame();
	updateCooldowns();

	if (currEnemy_ == nullptr)
		currEnemy_ = static_cast<Draw*>(GameManager::instance()->getPlayer());

	if (!attackCD_.isCooldownActive())
	{
		int probSwim, probInk, probSweep, probSlam;
		if ((currEnemy_->getPos() - getCenter()).magnitude() < 1.5 * scale_.getX())
		{
			//Frecuencias acumuladas de los ataques
			//Probabilidad acumulada de slam es siempre 100 por que es el ultimo
			probSwim = 10;
			probInk = 30;
			probSweep = 60;
		}
		else
		{
			probSwim = 50;
			probInk = 80;
			probSweep = 90;
		}

		int attack = rand() % 100;
		if (attack < probSwim)
			swimInit();
		else if (attack < probInk)
			ink();
		else if (attack < probSweep)
			sweep();
		else
			slam();

		attackCD_.initCooldown(currStats_.meleeRate_);
	}

	if (currState_ == STATE::SWIMMING && !swimCD_.isCooldownActive())
		swimEnd();

	//Si ha muerto
	if (currState_ == STATE::DYING) {
		//Tendr�a que hacer la animaci�n de muerte?
		//Cuando acabe la animaci�n, lo mata
		if (!tentacles_.empty()) {
			for (Tentacle* i : tentacles_) {
				if (i != nullptr)
				{
					i->die();
					app_->getCurrState()->removeRenderUpdateLists(i);
				}
			}
			tentacles_.clear();
		}

		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}

	return false;
}

//Inicializa todas las animaciones
void Kraken::initAnims()
{
	idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, false);
	inkAnim_ = Anim(NUM_FRAMES_INK, W_FRAME_INK, H_FRAME_INK, FRAME_RATE_INK, false);
	diveAnim_ = Anim(NUM_FRAMES_DIVE, W_FRAME_DIVE, H_FRAME_DIVE, FRAME_RATE_DIVE, false);
	exitAnim_ = Anim(NUM_FRAMES_EXIT, W_FRAME_EXIT, H_FRAME_EXIT, FRAME_RATE_EXIT, false);
}

//Inicializa el kraken
void Kraken::initObject()
{
	setTexture(app_->getTextureManager()->getTexture(Resources::Kraken));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	initAnims();
	swimInit();
	initRewards();
	app_->getAudioManager()->playChannel(Resources::KrakenIdle, -1, Resources::KrakenChannel1);
}

void Kraken::slam()
{
	double angle = 0;
	Vector2D tentPos;
	//Tama�o relativo al del kraken
	Vector2D tentScale = Vector2D(1.25 * scale_.getX(), scale_.getY() / 5);
	double deltaX = currEnemy_->getCenter().getX() - getCenter().getX(), deltaY = currEnemy_->getCenter().getY() - getCenter().getY();

	//Rotaci�n del tent�culo
	angle = atan2(deltaY, deltaX);

	//Dada la circunferencia y la posici�n del jugador se calcula la posici�n del kraken
	tentPos.setX((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * cos(angle) + getCenter().getX()) - (tentScale.getX() / 2));
	tentPos.setY((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * sin(angle) + getCenter().getY()) - (tentScale.getY() / 2));

	Tentacle* tentacle = new Tentacle(app_, this, tentPos, tentScale, (180 / M_PI) * angle, ATTACKS::SLAM);
	tentacles_.push_back(tentacle);
	static_cast<PlayState*>(app_->getGameStateMachine()->getState())->addEnemy(tentacle);

	switch (rand() % 2)
	{
	case 0:
		app_->getAudioManager()->playChannel(Resources::KrakenSlam1, 0, Resources::KrakenChannel2);
		break;
	case 1:
		app_->getAudioManager()->playChannel(Resources::KrakenSlam2, 0, Resources::KrakenChannel2);
		break;
	}
}

void Kraken::sweep()
{
	double angle = 0;
	double deltaX = currEnemy_->getCenter().getX() - getCenter().getX(), deltaY = currEnemy_->getCenter().getY() - getCenter().getY();

	Vector2D tentScale = Vector2D(1.25 * scale_.getX(), scale_.getY() / 5);
	Vector2D tentPos;
	//Si el jugador est� a la izquierda/derecha del kraken
	if (abs(deltaX) > abs(deltaY))
	{
		//Rotaci�n del tent�culo
		if (deltaX < 0)
			angle = M_PI;
		else
			angle = 0;
	}
	//Si el jugador est� arriba/abajo
	else
	{
		//Rotaci�n del tent�culo
		if (deltaY > 0)
			angle = M_PI / 2;
		else
			angle = 3 * M_PI / 2;
	}


	//Dado el �ngulo se calcula la posici�n en una circunferencia con el mismo radio que Slam()
	tentPos.setX((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * cos(angle) + getCenter().getX()) - (tentScale.getX() / 2));
	tentPos.setY((((scale_.getY() * 1.1 + tentScale.getX()) / 2) * sin(angle) + getCenter().getY()) - (tentScale.getY() / 2));
	Tentacle* tentacle = new Tentacle(app_, this, tentPos, tentScale, (180 / M_PI) * angle, ATTACKS::SWEEP);
	tentacles_.push_back(tentacle);
	static_cast<PlayState*>(app_->getGameStateMachine()->getState())->addEnemy(tentacle);

	switch (rand() % 3)
	{
	case 0:
		app_->getAudioManager()->playChannel(Resources::KrakenSweep1, 0, Resources::KrakenChannel2);
		break;
	case 1:
		app_->getAudioManager()->playChannel(Resources::KrakenSweep2, 0, Resources::KrakenChannel2);
		break;
	case 2:
		app_->getAudioManager()->playChannel(Resources::KrakenSweep3, 0, Resources::KrakenChannel2);
		break;
	}
}

void Kraken::swimInit()
{
	currState_ = STATE::SWIMMING;
	//Empieza animación (cambiar el valor de swimTime)

	swimCD_.initCooldown(SWIM_DURATION); //Esto se tendría que hacer al acabar la animación
	app_->getAudioManager()->playChannel(Resources::KrakenDive, 0, Resources::KrakenChannel2);
}

void Kraken::swimEnd()
{
	//Empieza animación
	currState_ = STATE::IDLE;

	//Se encuentra y guarda el índice de la posición más cercana al jugador y su distancia
	Vector2D closest = Vector2D(-1, -1);
	Player* player = static_cast<Player*>(GameManager::instance()->getPlayer());
	for (int i = 0; i < NUM_KRAKEN_SPOTS; i++)
	{
		double dist = Vector2D(player->getCenter().getX() - krakenSpots_[i].getX(), player->getCenter().getY() - krakenSpots_[i].getY()).magnitude();
		if (closest.getX() < 0 || dist < closest.getY())
			closest.setVec(Vector2D(i, dist));
	}
	pos_.setX(krakenSpots_[(int)closest.getX()].getX() - (scale_.getX() / 2));
	pos_.setY(krakenSpots_[(int)closest.getX()].getY() - (scale_.getY() / 2));
	app_->getAudioManager()->playChannel(Resources::KrakenSurface, 0, Resources::KrakenChannel2);
}

void Kraken::ink()
{
	app_->getAudioManager()->playChannel(Resources::KrakenInk, 0, Resources::KrakenChannel2);
	Vector2D pos;
	Vector2D scale = Vector2D(scale_.getX() / 5, scale_.getY() / 5);
	int numShots = AVERAGE_INK_SHOTS + ((rand() % NORMAL_DESVIATION * 2 + 1) - NORMAL_DESVIATION);
	for (int i = 0; i < numShots; i++)
	{
		//El punto sale aleatoriamente entre dos radios, scaleX y 2 scaleX
		int radius = rand() % (int)(scale_.getX()) + scale_.getX();
		int angle = rand();
		pos.setX(radius * cos(angle) + getCenter().getX());
		pos.setY(radius * sin(angle) + getCenter().getY());

		Ink* ink = new Ink(app_, this, pos, scale);
		app_->getGameStateMachine()->getState()->addRenderUpdateLists(ink);
	}

	Ink* ink = new Ink(app_, this, { 1148, 1800 }, scale);
	app_->getGameStateMachine()->getState()->addRenderUpdateLists(ink);
}

void Kraken::updateCooldowns()
{
	if (attackCD_.isCooldownActive()) attackCD_.updateCooldown();
	if (swimCD_.isCooldownActive()) swimCD_.updateCooldown();
}

void Kraken::tentDeath(Tentacle* obj)
{
	tentacles_.remove(obj);
	obj->die();
}

void Kraken::lostAggro()
{
	currEnemy_ = nullptr;
}

void Kraken::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}