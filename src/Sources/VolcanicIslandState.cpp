#include "VolcanicIslandState.h"
#include "Enemy.h"

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
#ifdef _DEBUG
	printf("VolcanicIsland");
#endif // _DEBUG
	Enemy* dragon = new Enemy(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), { 0,0 }, { 120,120 }, { 0,0,0,0 }, 0, 0, {0,0,144,133},3);
	addRenderUpdateLists(dragon);
}