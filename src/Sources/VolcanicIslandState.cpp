#include "VolcanicIslandState.h"
#include "Crab.h"

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
#ifdef _DEBUG
	printf("VolcanicIsland");
#endif // _DEBUG
	Crab* crab = new Crab(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), { 0,0 }, { 120,120 }, { 0,0,0,0 }, {}, { 0,0,144,133 }, 3, { {420,120},{58,360},{0,0} },3);
	addRenderUpdateLists(crab);
}