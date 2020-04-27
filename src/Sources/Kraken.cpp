#include "Kraken.h"
#include "CollisionCtrl.h"
#include "PlayState.h"

Kraken::~Kraken()
{
}

bool Kraken::update() {

	if (currEnemy_ == nullptr)
		currEnemy_ = static_cast<Draw*>(GameManager::instance()->getPlayer());



	if ((SDL_GetTicks() - lastAttack_) / 1000 > 3)
	{
		swimInit();
		lastAttack_ = SDL_GetTicks();
	}
	if (currState_ == STATE::SWIMMING && (SDL_GetTicks() - swimTime_) / 1000 > SWIM_DURATION)
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
	lastAttack_ = SDL_GetTicks();
	initAnims();
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
}

void Kraken::swimInit()
{
	currState_ = STATE::SWIMMING;
	//Empieza animación (cambiar el valor de swimTime)

	//Se encuentra y guarda el índice de la posición más cercana al jugador y su distancia
	Vector2D closest = Vector2D(-1, -1);
	Player* player = static_cast<Player*>(GameManager::instance()->getPlayer());
	for (int i = 0; i < NUM_KRAKEN_SPOTS; i++)
	{
		double dist = Vector2D(player->getCenter().getX() - krakenSpots_[i].getX(), player->getCenter().getY() - krakenSpots_[i].getY()).magnitude();
		if (closest.getX() < 0 || dist < closest.getY())
			closest.setVec(Vector2D(i, dist));
	}
	swimPos_.setVec(krakenSpots_[(int)closest.getX()]);

	swimTime_ = SDL_GetTicks(); //Esto se tendría que hacer al acabar la animación
}

void Kraken::swimEnd()
{
	currState_ = STATE::IDLE;
	//Empieza animación

	pos_.setX(swimPos_.getX() - (scale_.getX() / 2));
	pos_.setY(swimPos_.getY() - (scale_.getY() / 2));
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