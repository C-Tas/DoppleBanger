#include "HUD.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_macros.h"
#include "GameManager.h"
#include <array>

HUD::~HUD() {
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		delete(*it);
	}
	elementsHUD_.clear();
}

const void HUD::draw() {
	filledPieRGBA(app_->getRenderer(), xMana_, yMana_, W_WHEEL / 2, START_MANA, endMana_, 36, 113, 163, 255);

	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		(*it)->draw();
	}
	SDL_Rect iconRect;
	//Tamaño estándar de los iconos
	iconRect.w = iconRect.h = W_H_ICON;
	//Posición inicial de los primeros iconos
	iconRect.x = app_->getWindowWidth() * 8 / 25; 
	iconRect.y = app_->getWindowHeight() * 15 / 17;
	cdRect_.x = (app_->getWindowWidth() / 2) - W_SKILLS / 2;

	//Se reccorre el vector de las teclas para renderizarlas encima del HUD en caso de que hubiera textura
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (icons[i] != nullptr) {
			if (cdKeys[i]) cdBg_->render(cdRect_);
			icons[i]->render(iconRect);
		}
		//Actualiza el rect
		if (i < 3) {
			iconRect.x += DISTANCE_BTW_ICON;
			cdRect_.x += DISTANCE_BTW_ICON;
		}
	}
	//Resposicionamiento de los iconos
	iconRect.x += app_->getWindowWidth() / 10.4;
	for (int j = i; j < ICON_AMOUNT; j++) {
		if (icons[j] != nullptr) {
			icons[j]->render(iconRect);
		}
		//Actualiza el rect
		iconRect.x += DISTANCE_BTW_ICON;
	}

	//Para los puntos de hazaña
	iconRect.x = app_->getWindowWidth() * 9 / 10;
	iconRect.y = app_->getWindowHeight() * 15 / 18;
	Texture points(app_->getRenderer(), to_string(gm_->getAchievementPoints()), app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	points.render(iconRect.x - points.getWidth()/2, iconRect.y);

	//Contenedor de vida
	iconRect.x = app_->getWindowWidth() * 2 / 31;
	iconRect.y = (app_->getWindowHeight() * 7 / 9) + (W_H_LIFE * (1 - propLife_));
	iconRect.w = W_H_LIFE;
	iconRect.h = W_H_LIFE * propLife_;
	life_->render(iconRect, clipLife_);
}

bool HUD::update() {
	currentLife_ = dynamic_cast<Player*>(gm_->getPlayer())->getStats().health_;
	propLife_ = currentLife_ / maxLife_;
	clipLife_.h = life_->getHeight() * propLife_; //vidaAct * AltTotal / VidaMax
	clipLife_.y = life_->getHeight() - clipLife_.h;

	currentMana_ = dynamic_cast<Player*>(gm_->getPlayer())->getStats().mana_;
	propMana_ = currentMana_ / maxMana_;
	endMana_ = (MAX_DEGREES_MANA * propMana_) + START_MANA;	//Proporción de vida para el arco del maná
	if (endMana_ <= 90) endMana_ = 90;

	//Para eliminar un objeto cuando se usa
	HandleEvents* event = HandleEvents::instance();
	if (event->isKeyDown(SDL_SCANCODE_1) && icons[4] != nullptr) icons[4] = nullptr;
	if (event->isKeyDown(SDL_SCANCODE_2) && icons[5] != nullptr) icons[5] = nullptr;
	return false;
}

void HUD::updateSkillKey(int key) {
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

void HUD::updateObjectKey(int key) {
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

void HUD::setSkillCooldown(bool cooldown, int key) {
	switch (key) {
	case (int)SkillKey::Q:
		cdKeys[key] = cooldown;
		break;
	case (int)SkillKey::W:
		cdKeys[key] = cooldown;
		break;
	case (int)SkillKey::E:
		cdKeys[key] = cooldown;
		break;
	case (int)SkillKey::R:
		cdKeys[key] = cooldown;
		break;
	}
}

void HUD::initObject() {
	//Inicialización del GameManager
	gm_ = GameManager::instance();
	gm_->setHUD(this);
	SDL_Rect destRect;

	//Creacion del fondo del HUD
	#pragma region Background
	//Timon
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (app_->getWindowWidth() / 10) - W_WHEEL / 2;
	destRect.y = (app_->getWindowHeight() * 11 / 13) - H_WHEEL / 2;
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
	#pragma endregion

	#pragma region Skills&Objects
	//Aisgna la textura a la tecla correspondiente y se añaden al vector
	q_ = createSkillIcon((int)SkillKey::Q); icons.push_back(q_);
	w_ = createSkillIcon((int)SkillKey::W);	icons.push_back(w_);
	e_ = createSkillIcon((int)SkillKey::E);	icons.push_back(e_);
			//Todavía no se ha hecho el icono del clon para las habilidades, así que se usa el mono provisionalmente
			//r_ = app_->getTextureManager()->getTexture(Resources::ClonIcon);
	r_ = app_->getTextureManager()->getTexture(Resources::MonkeyFront); icons.push_back(r_);
 	one_ = createObjectIcon((int)ObjectKey::One); icons.push_back(one_);
	two_ = createObjectIcon((int)ObjectKey::Two); icons.push_back(two_);

	cdBg_ = app_->getTextureManager()->getTexture(Resources::CooldownHUD);
	for (int i = 0; i < 4; i++) {
		cdKeys.push_back(false);
	}
	#pragma endregion

	#pragma region Life&Mana
	//Inicializamos la vida al máximo
	life_ = app_->getTextureManager()->getTexture(Resources::LifeHUD);
	clipLife_.x = 0;
	clipLife_.y = 0;
	clipLife_.w = life_->getWidth();
	clipLife_.h = life_->getHeight();
	maxLife_ = dynamic_cast<Player*>(gm_->getPlayer())->getMaxHealth();

	xMana_ = app_->getWindowWidth() / 10;
	yMana_ = app_->getWindowHeight() * 11 / 13;
	maxMana_ = dynamic_cast<Player*>(gm_->getPlayer())->getMaxMana();

	//Tamaño del cooldown
	cdRect_.w = cdRect_.h = app_->getWindowWidth() * 2 / 35;
	cdRect_.y = app_->getWindowHeight() * 6 / 7;
	#pragma endregion
}

void HUD::createBg(Texture* tx, const SDL_Rect& destRect) {
	Draw* background = new Draw(app_, tx, destRect);
	elementsHUD_.push_back(background);
}

Texture* HUD::createSkillIcon(int key) {
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

Texture* HUD::createObjectIcon(int key) {
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