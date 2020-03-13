#include "TextBoxManager.h"
#include "HandleEvents.h"
#include "Resources.h"
#include "SDL_macros.h"

//Cada l�nea de los di�logos se tiene que renderizar por separado para poder generar los saltos de l�nea.
//Todo lo relacionado con textos aparece aqu� y no en Resources para no sobrecargar dicha clase.
//Los NPCs y los bosses se encargan de llamar en su update a su respectivo textBox cuando corresponda,
//y se renderiza hasta que se presione cualquier tecla y se elimine el textBox.

void TextBoxManager::init() {
	//Generamos la caja donde ir� el texto
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

void TextBoxManager::dialogElderMan(int isle) {
	//Viaje a la isla caribe�a
	if (isle == 0) {
		Texture text(app_->getRenderer(), "Frase 1...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);

		text.loadFromText(app_->getRenderer(), "Frase 2...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 2));
	}
	//Viaje a la isla fantasmal
	else if (isle == 1) {
	
	}
	//Viaje a la isla volc�nica
	else if (isle == 2) {
	
	}
	//Di�logo en el barco
	else {
	
	}
}

void TextBoxManager::dialogMerchant() {

}

void TextBoxManager::dialogChef(bool unlock) {
	//Di�logo del chef cuando lo hemos desbloqueado
	if (unlock) {

	}
	//Di�logo del chef cuando a�n est� bloqueado
	else {

	}
}

void TextBoxManager::dialogMorty(bool unlock) {
	//Di�logo de Morty cuando lo hemos desbloqueado
	if (unlock) {

	}
	//Di�logo de Morty cuando a�n est� bloqueado
	else {

	}
}

void TextBoxManager::dialogParrot() {
	//El loro gerera una frase aleatoria cada vez que se habla con �l
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
	//Al derrotar a Cle�n
	else {

	}
}