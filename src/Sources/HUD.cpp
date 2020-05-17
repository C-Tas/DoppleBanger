#include "HUD.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_macros.h"
#include "GameManager.h"
#include <array>
#include "Player.h"
#include "SDL_macros.h"

HUD::~HUD() {
	gm_->setHUD(nullptr);
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		delete(*it);
	}
	elementsHUD_.clear();
	for (int i = 0; i < POTIONS_AMOUNT; i++)
	{
		if (potionsHUD_[i].potionBackground_ != nullptr) delete potionsHUD_[i].potionBackground_;
		if (potionsHUD_[i].potionHUD_ != nullptr) delete potionsHUD_[i].potionHUD_;
		if (potionsHUD_[i].potionTimeHUD_ != nullptr) delete potionsHUD_[i].potionTimeHUD_;
	}
}

const void HUD::draw() {
	//Esto deja basura, pero Carlitos nos deja
	filledPieRGBA(app_->getRenderer(), xMana_, yMana_, W_WHEEL / 2, START_MANA, endMana_, 36, 113, 163, 255);

	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		(*it)->draw();
	}

	int aux = 0;

	//Muestra la duracion de las pociones
	for (int i = 0; i < POTIONS_AMOUNT; i++) {
		if (potionsHUD_[i].active_) {
			potionsHUD_[i].potionBackground_->setDestiny({ 0, (int)(aux * app_->getWindowHeight() * 0.1111), (int)(app_->getWindowWidth() * 0.125), (int)(app_->getWindowHeight() * 0.1111)});	//Fondo
			potionsHUD_[i].potionHUD_->setDestiny({ (int)(app_->getWindowWidth() * 0.0063), (int)(app_->getWindowHeight() * 0.0167 + aux * app_->getWindowHeight() * 0.1111), (int)(app_->getWindowWidth() * 0.0438), (int)(app_->getWindowHeight() * 0.0778)});	//Pocion
			potionsHUD_[i].potionBackground_->draw();
			potionsHUD_[i].potionHUD_->draw();
			potionsHUD_[i].potionTimeHUD_->render({ (int)(app_->getWindowWidth() * 0.0625), (int)(app_->getWindowHeight() * 0.0167 + aux * app_->getWindowHeight() * 0.1111), (int)(app_->getWindowWidth() * 0.0438), (int)(app_->getWindowHeight() * 0.0778)});	//Tiempo
			aux++;
		}
	}

	SDL_Rect iconRect;
	//Tama�o est�ndar de los iconos
	iconRect.w = iconRect.h = W_H_ICON;
	//Posici�n inicial de los primeros iconos
	iconRect.x = app_->getWindowWidth() * 8 / 25; 
	iconRect.y = app_->getWindowHeight() * 15 / 17;
	cdRect_.x = (app_->getWindowWidth() / 2) - W_SKILLS / 2;

	//Se reccorre el vector de las teclas para renderizarlas encima del HUD en caso de que hubiera textura
 	int i = 0;
	for (i = 0; i < ICON_AMOUNT; i++) {
		if (icons[i] != nullptr) {
 			if (i < 4 && cdKeys[i]) cdBg_->render(cdRect_);
			icons[i]->render(iconRect);
		}
		//Actualiza el rect
		if (i != 3) {
			iconRect.x += DISTANCE_BTW_ICON;
			cdRect_.x += DISTANCE_BTW_ICON;
		}
		else iconRect.x += app_->getWindowWidth() / 10.4;
	}

	//Para los puntos de haza�a
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
	//Actualiza el tiempo de las pociones y las desactiva al llegar a 0
	for (int i = 0; i < POTIONS_AMOUNT; i++) {
		if (potionsHUD_[i].active_) {

			potionsHUD_[i].currentTick_ = SDL_GetTicks();

			//Si se abre el inventario, los skills o la pausa no reducimos la duración (el valor suele estar entre 0 y 10, así que 200 que son 0,2 segundos es más que suficiente para determinar pausa)
			if ((potionsHUD_[i].currentTick_ - potionsHUD_[i].lastTick_) <= gm_->getDelayTime()) {
				potionsHUD_[i].duration_ -= (potionsHUD_[i].currentTick_ - potionsHUD_[i].lastTick_);
			}

			potionsHUD_[i].lastTick_ = potionsHUD_[i].currentTick_;

			//Sustituimos el número por el actual
			if (potionsHUD_[i].potionTimeHUD_ != nullptr) delete potionsHUD_[i].potionTimeHUD_;
			potionsHUD_[i].potionTimeHUD_ = new Texture(app_->getRenderer(), to_string((int)(potionsHUD_[i].duration_ / 1000.0) + 1),
				app_->getFontManager()->getFont(Resources::RETRO), SDL_Color{ (0,0,0,1) });

			//Si se agota la duración, se desactiva
			if ((potionsHUD_[i].active_) && (potionsHUD_[i].duration_ <= 0)) {
				potionsHUD_[i].active_ = false;
			}
		}
	}

 	currentLife_ = player_->getHealth();
	maxLife_ = player_->getMaxHealth();
	currentLife_ = gm_->getPlayer()->getHealth();
	propLife_ = currentLife_ / maxLife_;
	clipLife_.h = life_->getHeight() * propLife_;	//vidaAct * AltTotal / VidaMax
	clipLife_.y = life_->getHeight() - clipLife_.h;

	currentMana_ = player_->getMana();
	maxMana_ = player_->getMaxMana();
	propMana_ = currentMana_ / maxMana_;
	endMana_ = (MAX_DEGREES_MANA * propMana_) + START_MANA;	//Proporci�n de vida para el arco del man�
	if (endMana_ <= 90) endMana_ = 90;
	return false;
}

void HUD::updateKey(int key) {
	switch (key)
	{
	case (int)Key::Q:
		icons[key] = createSkillIcon(key);
		break;
	case (int)Key::W:
		icons[key] = createSkillIcon(key);
		break;
	case (int)Key::E:
		icons[key] = createSkillIcon(key);
		break;
	case (int)Key::One:
		icons[key] = createObjectIcon(key);
		break;
	case (int)Key::Two:
		icons[key] = createObjectIcon(key);
		break;
	}
}

void HUD::setSkillCooldown(bool cooldown, int key) {
	switch (key) {
	case (int)Key::Q:
		cdKeys[key] = cooldown;
		break;
	case (int)Key::W:
		cdKeys[key] = cooldown;
		break;
	case (int)Key::E:
		cdKeys[key] = cooldown;
		break;
	case (int)Key::R:
		cdKeys[key] = cooldown;
		break;
	}
}

//Le dice a la pocion en que momento se ha activado, y cual es su duraci�n
void HUD::showPotionHUD(int index, double duration, double time)
{
	potionsHUD_[index].active_ = true;
	potionsHUD_[index].duration_ = duration;
	potionsHUD_[index].lastTick_ = time;
}

void HUD::initObject() {
	//Inicializaci�n del GameManager
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
	//Aisgna la textura a la tecla correspondiente y se a�aden al vector
	icons.push_back(createSkillIcon((int)Key::Q));
	icons.push_back(createSkillIcon((int)Key::W));
	icons.push_back(createSkillIcon((int)Key::E));
	icons.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	icons.push_back(createObjectIcon((int)Key::One));
	icons.push_back(createObjectIcon((int)Key::Two));

	cdBg_ = app_->getTextureManager()->getTexture(Resources::CooldownHUD);
	for (int i = 0; i < 4; i++) {
		cdKeys.push_back(false);
	}
	#pragma endregion

	#pragma region Life&Mana
	//Inicializamos la vida al m�ximo
	player_ = gm_->getPlayer();
	life_ = app_->getTextureManager()->getTexture(Resources::LifeHUD);
	clipLife_.x = 0;
	clipLife_.y = 0;
	clipLife_.w = life_->getWidth();
	clipLife_.h = life_->getHeight();
 	maxLife_ = player_->getMaxHealth();

	xMana_ = app_->getWindowWidth() / 10;
	yMana_ = app_->getWindowHeight() * 11 / 13;
	maxMana_ = player_->getMaxMana();

	//Tama�o del cooldown
	cdRect_.w = cdRect_.h = app_->getWindowWidth() * 2 / 35;
	cdRect_.y = app_->getWindowHeight() * 6 / 7;
	#pragma endregion

	//Crea el HUD de las pociones
	for (int i = 0; i < POTIONS_AMOUNT; i++) potionsHUD_.push_back(createPotionHUD(i));
}

void HUD::createBg(Texture* tx, const SDL_Rect& destRect) {
	VisualElement* background = new VisualElement(app_, tx, destRect);
	elementsHUD_.push_back(background);
}

Texture* HUD::createSkillIcon(int key) {
	switch (gm_->getEquippedSkill((Key)key))
	{
	case SkillName::Unequipped:
		return nullptr;
		break;
	case SkillName::Explosion:
		return app_->getTextureManager()->getTexture(Resources::ExplosionIcon);
		break;
	case SkillName::GolpeFuerte:
		return app_->getTextureManager()->getTexture(Resources::GolpeFuerteIcon);
		break;
	case SkillName::DisparoPerforante:
		return app_->getTextureManager()->getTexture(Resources::PerforanteIcon);
		break;
	case SkillName::Rebote:
		return app_->getTextureManager()->getTexture(Resources::ReboteIcon);
		break;
	case SkillName::Torbellino:
		return app_->getTextureManager()->getTexture(Resources::TorbellinoIcon);
		break;
	}

	return nullptr;
}

potionHUD HUD::createPotionHUD(int key)
{
	potionHUD newPotion;
	newPotion.active_ = false;
	newPotion.duration_ = 0;
	newPotion.potionBackground_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::PotionBG));
	newPotion.potionTimeHUD_ = new Texture(app_->getRenderer(), to_string(newPotion.duration_),
		app_->getFontManager()->getFont(Resources::RETRO), SDL_Color{ (0,0,0,1) });
	switch (key)
	{
	case 0:
		newPotion.potionHUD_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::SpeedPot));	//Velocidad
		break;
	case 1:
		newPotion.potionHUD_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::ArmorPot));	//Defensa
		break;
	case 2:
		newPotion.potionHUD_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::DmgPot));	//Da�o
		break;
	case 3:
		newPotion.potionHUD_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::CritPot));	//Cr�tico
		break;
	default:
		break;
	}
	return newPotion;
}

Texture* HUD::createObjectIcon(int key) {
	switch (gm_->getObjectEquipped((Key)key))
	{
	case ObjectName::Unequipped:
		return nullptr;
		break;
	case ObjectName::Health:
		return app_->getTextureManager()->getTexture(Resources::HealthPot);
		break;
	case ObjectName::Mana:
		return app_->getTextureManager()->getTexture(Resources::ManaPot);
		break;
	case ObjectName::Speed:
		return app_->getTextureManager()->getTexture(Resources::SpeedPot);
		break;
	case ObjectName::Armor:
		return app_->getTextureManager()->getTexture(Resources::ArmorPot);
		break;
	case ObjectName::Damage:
		return app_->getTextureManager()->getTexture(Resources::DmgPot);
		break;
	case ObjectName::Crit:
		return app_->getTextureManager()->getTexture(Resources::CritPot);
		break;
	}

	return nullptr;
}