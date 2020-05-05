#include "VolcanicIslandState.h"
#include "Crab.h"

void VolcanicIslandState::initState()
{
	gm_->setOnShip(false);
	//background_ = app_->getTextureManager()->getTexture(Resources::Caribbean);

	//Button* backButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::BackButton),
	//	Vector2D(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2), Vector2D(300, 300), backShipVolcanic);
	//addRenderUpdateLists(backButton);

	//Enemy* dragon = new Enemy(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), { 0,0 }, { 120,120 }, { 0,0,0,0 }, {}, { 0,0,144,133 }, 3);
	//addRenderUpdateLists(dragon);

	////Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
	//addRenderUpdateLists(player_);
}

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
#ifdef _DEBUG
	printf("VolcanicIsland");
#endif // _DEBUG
	//Crab* dragon = new Crab(app_, { app_->getTextureManager()->getTexture(Resources::TextureId::Dragon), app_->getTextureManager()->getTexture(Resources::TextureId::Timon) }, { 0,0 }, { 120,120 }, { 0,0,120,120 }, { 1,0,0,0,0,0,0,0,100,0,0 }, { 0,0,144,133 }, { 3,1 }, { {450,60},{200,200},{50,60} });
	//addEnemy(dragon);
	//Player* p = new Player(app_, { 0,0 }, {100,100});
	Crab* crab = new Crab(app_, { 120,120 }, { 100,100 }, { {0,0},{120,120},{0,120}});
}