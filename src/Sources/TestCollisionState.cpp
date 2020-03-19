#include "TestCollisionState.h"

void TestCollisionState::initState()
{
	SDL_Rect colliderRect;
	colliderRect.x = app_->getWindowWidth() / 2; 
	colliderRect.y = app_->getWindowHeight() / 2;
	colliderRect.w = 300;
	colliderRect.h = 100;
	objectCollider_ = new TestObjectCollider(app_, colliderRect, app_->getTextureManager()->getTexture(Resources::Roca),
		Vector2D(colliderRect.x, colliderRect.y), Vector2D(colliderRect.w, colliderRect.h));
	addRenderUpdateLists(objectCollider_);

	colliderRect.x = app_->getWindowWidth() / 4;
	colliderRect.y = app_->getWindowHeight() / 4;
	colliderRect.w = 300;
	colliderRect.h = 100;
	objectCollider2_ = new TestObjectCollider(app_, colliderRect, app_->getTextureManager()->getTexture(Resources::Roca),
		Vector2D(colliderRect.x, colliderRect.y), Vector2D(colliderRect.w, colliderRect.h));
	addRenderUpdateLists(objectCollider2_);

	SDL_Rect playerCollision; playerCollision.x = 0; playerCollision.y = 0; playerCollision.w = 0; playerCollision.h = 0;
	player_ = new Player(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(50, 50), 
		Vector2D(100, 100), playerCollision);
	addRenderUpdateLists(player_);
}

void TestCollisionState::update()
{
	GameState::update();

	//Objeto 1 y player
	if (Collisions::collides(objectCollider_->getPos(), objectCollider_->getScaleX(), objectCollider_->getScaleY(),
		player_->getPos(), player_->getScaleX(), player_->getScaleY())) {
		player_->stop();
		objectCollider_->onCollider();
		cout << "Colisión del método collides" << endl;
	}

	//Objeto 2 y player. Colisión rectángulo rectángulo. Hay que pasarle el centro de cada objeto en la posición (los dos primeros parámetros)
	//En el resto de métodos de Physics supongo que hay que pasar el centro del objeto también, no lo he probado con todos
	if (RectRect(objectCollider2_->getPosX() + objectCollider2_->getScaleX() / 2, objectCollider2_->getPosY() + objectCollider2_->getScaleY()/2,
		objectCollider2_->getScaleX(), objectCollider2_->getScaleY(),
		player_->getPosX() + player_->getScaleX()/2, player_->getPosY() + player_->getScaleY() / 2, 
		player_->getScaleX(), player_->getScaleY())) {
		player_->stop();
		objectCollider2_->onCollider();
		cout << "Colisión RectRect de Physics" << endl;
	} 

	//Testear con las demás colisiones disponibles en Physics y en Collisions
}
