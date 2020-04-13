#include "Chest.h"
#include "HandleEvents.h"
#include "CollisionCtrl.h"

void Chest::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Chest));
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	CollisionCtrl::instance()->addChest(this);

	initAnim();
}

void Chest::initAnim() {
	//Para la animación de abrir
	openAnim_ = Anim(NUM_FRAMES_OPEN, NUM_FRAMES_ROW_OPEN, W_FRAME_OPEN, H_FRAME_OPEN, FRAME_RATE_OPEN, NAME_OPEN);
}

void Chest::onCollider() {
	//Método que va a añadirse proximamente por Aurora
	//GameManager::instance()->addToInventory(rN.genEquip());
	
	//initAnim(); cuando este la animación

	//Cuando acabe la animación los destruye -- faltaría añadir la textura
	app_->getCurrState()->removeRenderUpdateLists(this);
}