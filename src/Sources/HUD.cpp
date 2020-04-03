#include "HUD.h"

HUD::~HUD()
{
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		delete(*it);
	}
	elementsHUD_.clear();
}

const void HUD::draw()
{
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		(*it)->draw();
	}
}

void HUD::initObject()
{
	//Creacion del fondo del HUD
	SDL_Rect destRect;

	//Timon
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (app_->getWindowWidth() / 10) - W_WHEEL / 2;
	destRect.y = app_->getWindowHeight() * 5 / 7;
	wheel_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::WheelHUD), destRect);
	elementsHUD_.push_back(wheel_);

	//Cuerda
	destRect.w = W_ROPE; destRect.h = H_ROPE;
	destRect.x = app_->getWindowWidth() / 10;
	destRect.y = app_->getWindowHeight() * 3 / 4;
	rope_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::RopeHUD), destRect);
	elementsHUD_.push_back(rope_);

	//Skills y objetos
	destRect.w = W_SKILLS; destRect.h = H_SKILLS;
	destRect.x = (app_->getWindowWidth() / 2) - W_SKILLS / 2;
	destRect.y = app_->getWindowHeight() * 6 / 7;
	skills_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::SkillsHUD), destRect);
	elementsHUD_.push_back(skills_);
}
