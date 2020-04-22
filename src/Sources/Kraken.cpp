#include "Kraken.h"
#include "CollisionCtrl.h"
#include "PlayState.h"

Kraken::~Kraken()
{
}

bool Kraken::update() {

	if ((SDL_GetTicks() - lastAttack_) / 1000 > 5)
	{
		//slam();
		sweep();
		lastAttack_ = SDL_GetTicks();
	}
	//Si ha muerto
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte?
		//Cuando acabe la animación, lo mata
		if (!tentacles_.empty()) {
			for (Tentacle* i : tentacles_) {
				if (i != nullptr)
				{
					i->die();
					app_->getCurrState()->removeRenderUpdateLists(this);
				}
			}
			tentacles_.clear();
		}

		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}

	updateAnim();
	return false;
}

//Inicializa todas las animaciones
void Kraken::initAnims()
{
	idleAnim_ = Anim(NUM_FRAMES_IDLE, NUM_FRAMES_ROW_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, NAME_IDLE);
	inkAnim_ = Anim(NUM_FRAMES_INK, NUM_FRAMES_ROW_INK, W_FRAME_INK, H_FRAME_INK, FRAME_RATE_INK, NAME_INK);
	diveAnim_ = Anim(NUM_FRAMES_DIVE, NUM_FRAMES_ROW_DIVE, W_FRAME_DIVE, H_FRAME_DIVE, FRAME_RATE_DIVE, NAME_DIVE);
	exitAnim_ = Anim(NUM_FRAMES_EXIT, NUM_FRAMES_ROW_EXIT, W_FRAME_EXIT, H_FRAME_EXIT, FRAME_RATE_EXIT, NAME_EXIT);
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
	initAnim();
}

void Kraken::slam()
{
	double angle = 0;
	Vector2D tentPos;
	//Tamaño relativo al del kraken
	Vector2D tentScale = Vector2D(1.25 * scale_.getX(), scale_.getY() / 5);
	Draw* player = static_cast<Draw*>(GameManager::instance()->getPlayer());
	double deltaX = player->getCenter().getX() - getCenter().getX(), deltaY = player->getCenter().getY() - getCenter().getY();

	//Rotación del tentáculo
	angle = atan2(deltaY, deltaX);

	//Dada la circunferencia y la posición del jugador se calcula la posición del kraken
	tentPos.setX((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * cos(angle) + getCenter().getX()) - (tentScale.getX() / 2));
	tentPos.setY((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * sin(angle) + getCenter().getY()) - (tentScale.getY() / 2));

	Tentacle* tentacle = new Tentacle(app_, this, tentPos, tentScale, (180 / M_PI) * angle, ATTACKS::SLAM);
	tentacles_.push_back(tentacle);
	static_cast<PlayState*>(app_->getGameStateMachine()->getState())->addEnemy(tentacle);
}

void Kraken::sweep()
{
	double angle = 0;
	Draw* player = static_cast<Draw*>(GameManager::instance()->getPlayer());
	double deltaX = player->getCenter().getX() - getCenter().getX(), deltaY = player->getCenter().getY() - getCenter().getY();

	Vector2D tentScale = Vector2D(1.25 * scale_.getX(), scale_.getY() / 5);
	Vector2D tentPos;
	//Si el jugador está a la izquierda/derecha del kraken
	if (abs(deltaX) > abs(deltaY))
	{
		//Rotación del tentáculo
		if (deltaX < 0)
			angle = M_PI;
		else
			angle = 0;
	}
	//Si el jugador está arriba/abajo
	else
	{
		//Rotación del tentáculo
		if (deltaY > 0)
			angle = M_PI / 2;
		else
			angle = 3 * M_PI / 2;
	}


	//Dado el ángulo se calcula la posición en una circunferencia con el mismo radio que Slam()
	tentPos.setX((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * cos(angle) + getCenter().getX()) - (tentScale.getX() / 2));
	tentPos.setY((((scale_.getY() * 1.1 + tentScale.getX()) / 2) * sin(angle) + getCenter().getY()) - (tentScale.getY() / 2));
	Tentacle* tentacle = new Tentacle(app_, this, tentPos, tentScale, (180 / M_PI) * angle, ATTACKS::SWEEP);
	tentacles_.push_back(tentacle);
	static_cast<PlayState*>(app_->getGameStateMachine()->getState())->addEnemy(tentacle);
}

void Kraken::tentDeath(Tentacle* obj)
{
	tentacles_.remove(obj);
	obj->die();
}