#include "VolcanicIslandState.h"
#include "Crab.h"

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
#ifdef _DEBUG
	printf("VolcanicIsland");
#endif // _DEBUG
	Crab* dragon = new Crab(app_, { app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), app_->getTextureManager()->getTexture(Resources::TextureId::Timon) }, { 0,0 }, { 120,120 }, { 0,0,0,0 }, { 0,0,0,0,0,0,0,100,0,0 }, { 0,0,144,133 }, { 3,1 }, { {450,60},{200,200},{50,60} });
	addRenderUpdateLists(dragon);
}