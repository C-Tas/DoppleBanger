#include "Font.h"
#include <iostream>
using namespace std;

bool Font::load(const string& fileName, int size) {
	font_ = TTF_OpenFont(fileName.c_str(), size);
	if (font_ == nullptr) {
		throw "No se puede cargar el archivo: " + fileName;
	}
	return font_;
}

void Font::close() {
	if (font_) {
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}

SDL_Surface* Font::renderText(const string& text, SDL_Color color) const {
	if (font_) {
		return TTF_RenderText_Solid(font_, text.c_str(), color);
	}
	else {
		return nullptr;
	}
}
