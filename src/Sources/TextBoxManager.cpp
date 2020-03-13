#include "TextBoxManager.h"
#include "Resources.h"
#include "SDL_macros.h"

void TextBoxManager::DialogChef(bool unlock) {
	if (unlock) {
		Texture text(app_->getRenderer(), "Diálogo del chef", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0xffffffff) });
		text.render(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2);
		text.loadFromText(app_->getRenderer(), "cuando no se ha", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0xffffffff) });
		text.render(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2 + 50);
		text.loadFromText(app_->getRenderer(), "desbloqueado", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0xffffffff) });
		text.render(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2 + 100);
	}
	else {
		Texture text(app_->getRenderer(), "Diálogo del chef", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0xffffffff) });
		text.render(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2);
		text.loadFromText(app_->getRenderer(), "cuando está", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0xffffffff) });
		text.render(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2 + 50);
		text.loadFromText(app_->getRenderer(), "bloqueado", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0xffffffff) });
		text.render(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2 + 100);
	}
}

void TextBoxManager::DialogMorty(bool unlock) {

}