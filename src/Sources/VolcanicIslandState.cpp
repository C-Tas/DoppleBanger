#include "VolcanicIslandState.h"
#include "Crab.h"

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
#ifdef _DEBUG
	printf("VolcanicIsland");
#endif // _DEBUG
	SDL_Rect playerCollision; playerCollision.x = 0; playerCollision.y = 0; playerCollision.w = 0; playerCollision.h = 0;
	player_ = new Player(app_, { app_->getTextureManager()->getTexture(Resources::TextureId::Timon) }, Vector2D(500, 500), Vector2D(100, 100), playerCollision);
	addRenderUpdateLists(player_);

	Crab* dragon = new Crab(app_, { app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), app_->getTextureManager()->getTexture(Resources::TextureId::Timon) }, { 0,0 }, { 120,120 }, { 0,0,120,120 }, { 1,0,0,0,0,0,0,0,100,0,0 }, { 0,0,144,133 }, { 3,1 }, { {450,60},{200,200},{50,60} });
	addEnemy(dragon);
}