#include "TextBoxManager.h"
#include "HandleEvents.h"
#include "Resources.h"
#include "SDL_macros.h"

//Cada línea de los diálogos/descripciones se tiene que renderizar por separado para poder generar los saltos de línea.
//Todo lo relacionado con textos aparece aquí y no en Resources para no sobrecargar dicha clase.
//Los NPCs y los bosses se encargan de llamar en su update a su respectivo textBox cuando corresponda,
//y se renderiza hasta que se presione cualquier tecla y se elimine el textBox.
//Cada objeto llama a su correspondiente descripción, cuando el estado abierto se lo indique,
//pasándo la posición en la que se sitúa la descripción de dicho estado.

void TextBoxManager::initDialog() {
	//Generamos la caja donde irá el texto
	dest.w = app_->getWindowWidth();
	dest.h = app_->getWindowHeight() / 4;
	dest.x = 0;
	dest.y = app_->getWindowHeight() - dest.h;
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render(dest);

	//Comentario al final de la caja de texto
	Texture pressAnyKey(app_->getRenderer(), "Pulse cualquier tecla >>", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x99999999) });
	pressAnyKey.render(app_->getWindowWidth() - pressAnyKey.getWidth() - lineSpacing, app_->getWindowHeight() - pressAnyKey.getHeight() - lineSpacing);
}

void TextBoxManager::initDescription(Point2D pos) {
	//Caja donde se representa el texto de las descripciones
	dest.w = app_->getWindowWidth() / 4;
	dest.h = app_->getWindowHeight() / 7;
	dest.x = pos.getX();
	dest.y = pos.getY();
}

#pragma region Diálogos
void TextBoxManager::dialogElderMan(int isle) {
	//Viaje a la isla caribeña
	if (isle == 0) {
		Texture text(app_->getRenderer(), "Frase 1...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);

		text.loadFromText(app_->getRenderer(), "Frase 2...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 2));
	}
	//Viaje a la isla fantasmal
	else if (isle == 1) {
	
	}
	//Viaje a la isla volcánica
	else if (isle == 2) {
	
	}
	//Diálogo en el barco
	else {
	
	}
}

void TextBoxManager::dialogMerchant() {
}

void TextBoxManager::dialogChef(bool unlock) {
	//Diálogo del chef cuando lo hemos desbloqueado
	if (unlock) {

	}
	//Diálogo del chef cuando aún está bloqueado
	else {

	}
}

void TextBoxManager::dialogMorty(bool unlock) {
	//Diálogo de Morty cuando lo hemos desbloqueado
	if (unlock) {

	}
	//Diálogo de Morty cuando aún está bloqueado
	else {

	}
}

void TextBoxManager::dialogParrot() {
	//El loro gerera una frase aleatoria cada vez que se habla con él
	int rnd = rand() % 5;
	if (rnd == 0) {

	}
	else if (rnd == 1) {

	}
	else if (rnd == 2) {

	}
	else if (rnd == 3) {

	}
	else if (rnd == 4) {

	}
}

void TextBoxManager::dialogKraken(bool defeated) {
	//Al comenzar la batalla
	if (!defeated) {

	}
	//Al derrotar al Kraken
	else {

	}
}

void TextBoxManager::dialogMagordito(bool defeated) {
	//Al comenzar la batalla
	if (!defeated) {

	}
	//Al derrotar a Magordito
	else {

	}
}

void TextBoxManager::dialogCleon(bool defeated) {
	//Al comenzar la batalla
	if (!defeated) {

	}
	//Al derrotar a Cleón
	else {

	}
}
#pragma endregion

#pragma region Descripciones
void TextBoxManager::armorCaribbean() {
}

void TextBoxManager::armorSpooky() {
}

void TextBoxManager::glovesCaribbean() {
}

void TextBoxManager::glovesSpooky() {
}

void TextBoxManager::bootsCaribbean() {
}

void TextBoxManager::bootsSpooky() {
}

void TextBoxManager::swordCaribbean() {
}

void TextBoxManager::swordSpooky() {
}

void TextBoxManager::saberCaribbean() {
}

void TextBoxManager::saberSpooky() {
}

void TextBoxManager::pistolCaribbean() {
}

void TextBoxManager::pistolSpooky() {
}

void TextBoxManager::blunderbussCaribbean() {
}

void TextBoxManager::blunderbussSpooky() {
}

void TextBoxManager::lifePotion() {
	Texture text(app_->getRenderer(), "Poción de vida:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Medicina de hierbas divinas que curan las", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "heridas regenerando una cantidad de vida.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "Puede contener trazas de frutos secos.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBoxManager::manaPotion() {
	Texture text(app_->getRenderer(), "Poción de maná:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Agua de mar tratada con magia que regenera", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "una cantidad de maná.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBoxManager::velocityPotion() {
	Texture text(app_->getRenderer(), "Poción de velocidad:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Ron mezclado con aceite de trucha que", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "producen hiperactividad, aumentando la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "velocidad de movimiento.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBoxManager::damagePotion() {
	Texture text(app_->getRenderer(), "Poción de daño:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Fluidos de demonio que fortalecen la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "musculatura haciendo que el que la bebe", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "inflija más daño con sus golpes.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBoxManager::defensePotion() {
	Texture text(app_->getRenderer(), "Poción de defensa:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de gorila tratada con alquimia", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "avanzada que aumenta la resistencia.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBoxManager::criticPotion() {
	Texture text(app_->getRenderer(), "Poción de crítico:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de águila virgen que aumenta la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "precisión otorgando mayor probabilidad", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "de crítico.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}
#pragma endregion