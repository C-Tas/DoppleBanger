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
	manageTint();

	if (currEnemy_ == nullptr)
		currEnemy_ = static_cast<Draw*>(GameManager::instance()->getPlayer());

	if (currState_ == STATE::STOPSWIMMING && currAnim_.currFrame_ == currAnim_.numberFrames_ - 1) {
		idle();
	}
	else if (currState_ == STATE::SWIMMING && currAnim_.currFrame_ == currAnim_.numberFrames_ - 1) {
		swimCD_.initCooldown(SWIM_DURATION); //Esto se tendría que hacer al acabar la animación
	}
	else if ((currState_ == STATE::SHOOTING && currAnim_.currFrame_ == currAnim_.numberFrames_ - 1)) {
		InkAction();
		idle();
	}

	if (!attackCD_.isCooldownActive())
	{
		int probSwim, probInk;
		if ((currEnemy_->getPos() - getCenter()).magnitude() < 1.5 * scale_.getX())
		{
			//Frecuencias acumuladas de los ataques
			//Probabilidad acumulada de slam es siempre 100 por que es el ultimo
			probSwim = 20;
			probInk = 30;
		}
		else
		{
			probSwim = 70;
			probInk = 20;
		}

		int attack = rand() % 100;
		if (attack < probSwim)
			swimInit();
		else if (attack < probInk)
			ink();
		else
			slam();

		attackCD_.initCooldown(currStats_.meleeRate_);
	}

	if (currState_ == STATE::SWIMMING/* && !swimCD_.isCooldownActive()*/ && currAnim_.currFrame_ == currAnim_.numberFrames_ - 1)
		swimEnd();

	//Si ha muerto
	if (currState_ == STATE::DYING) {
		
		dieAnim();
	}

	return false;
}

void Kraken::initDie() {
	Enemy::initDie();
	app_->resetMusicChannels();
	app_->resetSoundsChannels();

	//Se restaura el volumen default del canal de música
	app_->getAudioManager()->playChannel(Resources::KrakenDeath, 0, Resources::KrakenChannel1);
	app_->getAudioManager()->playChannel(Resources::Isle1Zone3, -1, Resources::MainMusicChannel);
	GameManager::instance()->setCurrIsland(Island::Spooky);
	//Cuando acabe la animaci�n, lo mata
	if (!tentacles_.empty()) {
		for (Tentacle* i : tentacles_) {
			if (i != nullptr)
			{
				i->die();
				app_->getCurrState()->removeRenderUpdateLists(i);
				static_cast<PlayState*>(app_->getCurrState())->removeEnemy(i);
			}
		}
		tentacles_.clear();
	}
}
//Inicializa todas las animaciones
void Kraken::initAnims()
{
	idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, false);
	IdleTx_ = app_->getTextureManager()->getTexture(Resources::KrakenIdleAnim);
	inkAnim_ = Anim(NUM_FRAMES_INK, W_FRAME_INK, H_FRAME_INK, FRAME_RATE_INK, false);
	InkTx_ = app_->getTextureManager()->getTexture(Resources::KrakenInkAnim);
	diveAnim_ = Anim(NUM_FRAMES_DIVE, W_FRAME_DIVE, H_FRAME_DIVE, FRAME_RATE_DIVE, false);
	DiveTx_ = app_->getTextureManager()->getTexture(Resources::KrakenDiveAnim);
	exitAnim_ = Anim(NUM_FRAMES_EXIT, W_FRAME_EXIT, H_FRAME_EXIT, FRAME_RATE_EXIT, false);
	ExitTx_ = app_->getTextureManager()->getTexture(Resources::KrakenExitAnim);

	//comenzamos idle
	idle();
}

void Kraken::initialStats() {
	initHealth_ = 2000;
	initMana_ = 0;
	initManaReg_ = 0;
	initArmor_ = 0;
	initMeleeDmg = 300; 
	initDistDmg = 225;
	initCrit_ = 0; 
	initMeleeRange = 0;
	initDistRange_ = 0;
	initMoveSpeed = 0;
	initMeleeRate_ = 4000;
	initDistRate_ = 5000;
	initStats(initHealth_, initMana_, initManaReg_, initArmor_, initMeleeDmg, initDistDmg, initCrit_, initMeleeRange, initDistRange_, initMoveSpeed, initMeleeRate_, initDistRate_);
}

//Inicializa el kraken
void Kraken::initObject()
{
	setTexture(app_->getTextureManager()->getTexture(Resources::Kraken));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addEnemy(this);
	initAnims();
	//swimInit();
	initRewards();
	tag_ = "Kraken";
	app_->resetMusicChannels();
	app_->getAudioManager()->playChannel(Resources::KrakenIdle, -1, Resources::KrakenChannel1);
	initialStats();
	attackCD_.initCooldown(currStats_.meleeRate_);
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
	texture_ = DiveTx_;
	currAnim_ = diveAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	app_->getAudioManager()->playChannel(Resources::KrakenDive, 0, Resources::KrakenChannel2);

	if (!tentacles_.empty()) {
		for (Tentacle* i : tentacles_) {
			if (i != nullptr)
			{
				i->die();
				i->setState(STATE::DYING);
				app_->getCurrState()->removeRenderUpdateLists(i);
			}
		}
		tentacles_.clear();
	}
}

void Kraken::swimEnd()
{
	//Empieza animación
	currState_ = STATE::STOPSWIMMING;
	texture_ = ExitTx_;
	currAnim_ = exitAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	//Se encuentra y guarda el índice de la posición más cercana al jugador y su distancia
	Vector2D closest = Vector2D(-1, -1);
	Player* player = static_cast<Player*>(GameManager::instance()->getPlayer());
	for (int i = 0; i < krakenSpots_.size(); i++)
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
	currState_ = STATE::SHOOTING;
	texture_ = InkTx_;
	currAnim_ = inkAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	app_->getAudioManager()->playChannel(Resources::KrakenInk, 0, Resources::KrakenChannel2);

}

void Kraken:: InkAction() {
	Vector2D pos;
	Vector2D scale = Vector2D(scale_.getX() / 5, scale_.getY() / 5);
	int numShots = AVERAGE_INK_SHOTS + ((rand() % NORMAL_DESVIATION * 2 + 1) - NORMAL_DESVIATION);
	for (int i = 0; i < numShots; i++)
	{
		//El punto sale aleatoriamente entre dos radios, scaleX y 2 scaleX
		int radius = (int)round(rand() % (int)(scale_.getX()) + scale_.getX()/2);
		int angle = rand();
		pos.setX(radius * cos(angle) + getCenter().getX());
		pos.setY(radius * sin(angle) + getCenter().getY());

		Ink* ink = new Ink(app_, this, pos, scale);
		app_->getGameStateMachine()->getState()->addRenderUpdateListsAsFirst(ink);
	}
}

void Kraken::idle()
{
	currState_ = STATE::IDLE;
	texture_ = IdleTx_;
	currAnim_ = idleAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
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
	goldPoints_ = 1000;
	achievementPoints_ = 300;
}