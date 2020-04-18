#include "Kraken.h"
#include "CollisionCtrl.h"
#include "PlayState.h"

Kraken::~Kraken()
{
}

bool Kraken::update() {

	if ((SDL_GetTicks() - lastAttack_) / 1000 > 3)
	{
		slam();
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
	slamAnim_ = Anim(NUM_FRAMES_SLAM, NUM_FRAMES_ROW_SLAM, W_FRAME_SLAM, H_FRAME_SLAM, FRAME_RATE_SLAM, NAME_SLAM);
	sweepAnim_ = Anim(NUM_FRAMES_SWEEP, NUM_FRAMES_ROW_SWEEP, W_FRAME_SWEEP, H_FRAME_SWEEP, FRAME_RATE_SWEEP, NAME_SWEEP);
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
	if (deltaX != 0) angle = atan2(deltaY, deltaX);
	else if (deltaY > 0) angle = M_PI / 2;
	else angle = 3 * M_PI / 2;

	//Dada la circunferencia y la posición del jugador se calcula la posición del kraken
	tentPos.setX((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * cos(angle) + getCenter().getX()) - (tentScale.getX() / 2));
	tentPos.setY((((scale_.getX() * 1.1 + tentScale.getX()) / 2) * sin(angle) + getCenter().getY()) - (tentScale.getY() / 2));

	Tentacle* tentacle = new Tentacle(app_, this, tentPos, tentScale, (180 / M_PI) * angle);
	tentacles_.push_back(tentacle);
	static_cast<PlayState*>(app_->getGameStateMachine()->getState())->addEnemy(tentacle);
}

void Kraken::tentDeath(Tentacle* obj)
{
	tentacles_.remove(obj);
	obj->die();
}