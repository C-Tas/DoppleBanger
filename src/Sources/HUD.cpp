#include "HUD.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL2_rotozoom.h"
#include <array>
#include "GameManager.h"

HUD::~HUD()
{
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		delete(*it);
	}
	elementsHUD_.clear();
}

const void HUD::draw()
{
	//270 * currMana / maxMana;
	//
	/*filledPieRGBA(app_->getRenderer(), (app_->getWindowWidth() / 10), app_->getWindowHeight() * 6 / 7, W_WHEEL / 2, 90, endLife, 0, 0, 255, 255);
	filledPieRGBA(app_->getRenderer(), (app_->getWindowWidth() / 10), app_->getWindowHeight() * 6 / 7, W_WHEEL / 2, 270, endLife, 255, 80, 15, 255);*/
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		(*it)->draw();
	}
	SDL_Rect iconRect;
	//Tamaño estándar de los iconos
	iconRect.w = iconRect.h = W_H_ICON;
	//Posición inicial de los primeros iconos
	iconRect.x = app_->getWindowWidth() * 8 / 25; 
	iconRect.y = app_->getWindowHeight() * 15 / 17;
	//Se reccorre el vector de las teclas para renderizarlas encima del HUD en caso de que hubiera textura
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (icons[i] != nullptr) {
			icons[i]->render(iconRect);
		}
		//Actualiza el rect
		if(i < 3) iconRect.x += DISTANCE_BTW_ICON;
	}
	//Resposicionamiento de los iconos
	iconRect.x += app_->getWindowWidth() / 10.4;
	for (int j = i; j < ICON_AMOUNT; j++) {
		if (icons[i] != nullptr) {
			icons[i]->render(iconRect);
		}
		//Actualiza el rect
		iconRect.x += DISTANCE_BTW_ICON;
	}
	//filledCircleRGBA(app_->getRenderer(),  400, 100, 0, 87, 255);
	//filledCircleRGBA(app_->getRenderer(), app_->getWindowWidth() / 2, app_->getWindowHeight(), 200, 207, 0, 15, 255);
	//roundedRectangleRGBA(app_->getRenderer(), 200, 400, 600, 500, 7, 207, 0, 15, 255);
	//arcRGBA(app_->getRenderer(), app_->getWindowWidth() / 2, app_->getWindowHeight() / 2, 400, 90, 270, 255, 0, 15, 255);
	//arcRGBA(app_->getRenderer(), app_->getWindowWidth() / 2, app_->getWindowHeight() / 2, 200, 90, 270, 255, 0, 15, 255);
}

bool HUD::update()
{
	/*if (endLife >= 360) endLife = 1;
	else if (endLife >= 90) endLife = 270;
	endLife += 0.25 * app_->getDeltaTime();*/
	return false;
}

void HUD::updateSkillKey(int key)
{
	switch (key)
	{
	case (int)SkillKey::Q:
		q_ = createSkillIcon((int)key);
		break;
	case (int)SkillKey::W:
		w_ = createSkillIcon((int)key);
		break;
	case (int)SkillKey::E:
		e_ = createSkillIcon((int)key);
		break;
	}
}

void HUD::updateObjectKey(int key)
{
	switch (key)
	{
	case (int)ObjectKey::One:
		one_ = createObjectIcon((int)key);
		break;
	case (int)ObjectKey::Two:
		two_ = createObjectIcon((int)key);
		break;
	}
}

void HUD::initObject()
{
	//Inicialización del GameManager
	gm_ = GameManager::instance();

	//Creacion del fondo del HUD
	SDL_Rect destRect;

	//Timon
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (app_->getWindowWidth() / 10) - W_WHEEL / 2;
	destRect.y = app_->getWindowHeight() * 5 / 7;
	createBg(app_->getTextureManager()->getTexture(Resources::WheelHUD), destRect);

	//Cuerda
	destRect.w = W_ROPE; destRect.h = H_ROPE;
	destRect.x = app_->getWindowWidth() / 10;
	destRect.y = app_->getWindowHeight() * 3 / 4;
	createBg(app_->getTextureManager()->getTexture(Resources::RopeHUD), destRect);

	//Skills y objetos
	destRect.w = W_SKILLS; destRect.h = H_SKILLS;
	destRect.x = (app_->getWindowWidth() / 2) - W_SKILLS / 2;
	destRect.y = app_->getWindowHeight() * 6 / 7;
	createBg(app_->getTextureManager()->getTexture(Resources::SkillsHUD), destRect);
	//Aisgna la textura a la tecla correspondiente y se añaden al vector
	q_ = createSkillIcon((int)SkillKey::Q); icons.push_back(q_);
	w_ = createSkillIcon((int)SkillKey::W);	icons.push_back(w_);
	e_ = createSkillIcon((int)SkillKey::E);	icons.push_back(e_);
			//Todavía no se ha hecho el icono del clon para las habilidades, así que se usa el timón provisionalmente
			//r_ = app_->getTextureManager()->getTexture(Resources::ClonIcon);
	r_ = app_->getTextureManager()->getTexture(Resources::MonkeyFront); icons.push_back(r_);
 	one_ = createObjectIcon((int)ObjectKey::One); icons.push_back(one_);
	two_ = createObjectIcon((int)ObjectKey::Two); icons.push_back(two_);
}

void HUD::createBg(Texture* tx, const SDL_Rect& destRect)
{
	Draw* background = new Draw(app_, tx, destRect);
	elementsHUD_.push_back(background);
}

Texture* HUD::createSkillIcon(int key)
{
	switch ((int)gm_->getSkillEquipped(key))
	{
	case (int)SkillName::Unequipped:
		return nullptr;
		break;
	case (int)SkillName::Explosion:
		return app_->getTextureManager()->getTexture(Resources::ExplosionIcon);
		break;
	case (int)SkillName::GolpeFuerte:
		return app_->getTextureManager()->getTexture(Resources::GolpeFuerteIcon);
		break;
	case (int)SkillName::DisparoPerforante:
		return app_->getTextureManager()->getTexture(Resources::PerforanteIcon);
		break;
	case (int)SkillName::Rebote:
		return app_->getTextureManager()->getTexture(Resources::ReboteIcon);
		break;
	case (int)SkillName::Torbellino:
		return app_->getTextureManager()->getTexture(Resources::TorbellinoIcon);
		break;
	}

	return nullptr;
}

Texture* HUD::createObjectIcon(int key)
{
	switch ((int)gm_->getObjectEquipped(key))
	{
	case (int)ObjectName::Unequipped:
		return nullptr;
		break;
	case (int)ObjectName::Health:
		return app_->getTextureManager()->getTexture(Resources::HealthPot);
		break;
	case (int)ObjectName::Mana:
		return app_->getTextureManager()->getTexture(Resources::ManaPot);
		break;
	case (int)ObjectName::Speed:
		return app_->getTextureManager()->getTexture(Resources::SpeedPot);
		break;
	case (int)ObjectName::Armor:
		return app_->getTextureManager()->getTexture(Resources::ArmorPot);
		break;
	case (int)ObjectName::Dmg:
		return app_->getTextureManager()->getTexture(Resources::DmgPot);
		break;
	case (int)ObjectName::Crit:
		return app_->getTextureManager()->getTexture(Resources::CritPot);
		break;
	}

	return nullptr;
}
